#include "Arm.h"

#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>
// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define X 0
#define Y 1
#define Z 2
#define SQUARED(x)	(x)*(x)

using namespace std;

Arm::Arm()
{
	this->parts = new vector<ArmPart*>;
}

void Arm::add(ArmPart* part)
{
	this->parts->push_back(part);
}


Arm::~Arm()
{
}

vector<ArmPart*>* Arm::getParts()
{
	return this->parts;
}

void Arm::setTarget(double x, double y, double z, float r, float g, float b, float a)
{
	this->target.x = x;
	this->target.y = y;
	this->target.z = z;
	this->targetColor.r = r;
	this->targetColor.g = g;
	this->targetColor.b = b;
	this->targetColor.a = a;
}

bool Arm::inCircle(double centerX, double centerY, double centerZ, double radius, double pointX, double pointY, double pointZ)
{
	return radius * radius >= SQUARED(centerX - pointX) + SQUARED(centerY - pointY) + SQUARED(centerZ - pointZ);
}

double Arm::getSquareDistance(double point1X, double point1Y, double point1Z, double point2X, double point2Y, double point2Z)
{
	return SQUARED(point2X - point1X) + SQUARED(point2Y - point1Y) + SQUARED(point2Z - point1Z);
}

double Arm::getDistance(double point1X, double point1Y, double point1Z, double point2X, double point2Y, double point2Z)
{
	return sqrt(this->getSquareDistance(point1X, point1Y, point1Z, point2X, point2Y, point2Z));
}

vector<ArmMovement*>* Arm::getMovements()
{
	const int partsLength = this->parts->size();
	
	vector<ArmMovement*>* movements = new vector<ArmMovement*>();
	vector<double> radiusList(partsLength);

	vector<double*>* points = new vector<double*>();

	double sumRadius = 0.0f;
	double sumCenter = 0.0f;

	for (int i = 0, j = partsLength - 1; j >= 0; i++, j--)
	{
		double* point = new double[3];
		point[X] = sumCenter;
		point[Y] = 0.0f;
		point[Z] = 0.0f;
		points->push_back(point);
		this->parts->at(i)->setPoint(sumCenter, 0.0f, 0.0f);

		sumCenter += this->parts->at(i)->getSize();

		sumRadius += this->parts->at(j)->getSize();
		radiusList[j] = sumRadius;
	}

	{
		double* point = new double[3];
		point[X] = sumCenter;
		point[Y] = 0.0f;
		point[Z] = 0.0f;
		points->push_back(point);
	}

	for (int i = 0; i < partsLength; i++)
	{
		std::cout << points->at(i)[X] << ", " << points->at(i)[Y] << ", " << points->at(i)[Z] << " - " << radiusList[i] << "\n";
	}

	int positionCenterDetect;
	bool radiusDetect = false;
	for (int i = partsLength - 1; i >= 0; i--)
	{
		if (this->inCircle(points->at(i)[X], points->at(i)[Y], points->at(i)[Z], radiusList[i], this->target.x, this->target.y, this->target.z))
		{
			positionCenterDetect = i;
			radiusDetect = true;
			break;
		}
	}

	if (!radiusDetect)
		throw new ArmUnreachableException();

	unsigned int endPoint = points->size() - 1;
	{
		ArmMovement* movement = new ArmMovement();
		movement->triangleAngle = 0;
		movement->armAngle = 0;
		movement->startAngle = 0;
		movement->endAngle = 0;
		movement->angled = movement->endAngle - movement->startAngle;
		movement->startPoint = 0;
		movement->endPoint = endPoint;

		for (int i = 0; i < this->parts->size(); i++)
			movement->points.push_back(glm::vec3(this->parts->at(i)->getPoint().x, this->parts->at(i)->getPoint().y, this->parts->at(i)->getPoint().z));

		movements->push_back(movement);
	}

	double termOne, termTwo, triangleAngle, armAngle, finalAngle;
	double startAngle = 0;
	for (int i = positionCenterDetect; i < partsLength; i++) {
		double* point = points->at(i);
		double* pointSecond = points->at(i + 1);
		double* pointLast = points->at(partsLength);
		termOne = this->getSquareDistance(point[X], point[Y], point[Z], this->target.x, this->target.y, this->target.z);
		termTwo = this->getSquareDistance(point[X], point[Y], point[Z], pointSecond[X], pointSecond[Y], pointSecond[Z]);
		triangleAngle = acos((termOne + termTwo - this->getSquareDistance(pointSecond[X], pointSecond[Y], pointSecond[Z], pointLast[X], pointLast[Y], pointLast[Z])) /
			(2 * sqrt(termOne) * sqrt(termTwo)));

		double* v = new double[3];
		v[X] = pointSecond[X] - point[X];
		v[Y] = pointSecond[Y] - point[Y];
		v[Z] = pointSecond[Z] - point[Z];
		double* e = new double[3];
	 	e[X] = this->target.x - point[X];
		e[Y] = this->target.y - point[Y];
		e[Z] = this->target.z - point[Z];
		armAngle = acos((e[X] * v[X] + e[Y] * v[Y] + e[Z] * v[Z]) / (sqrt(SQUARED(e[X]) + SQUARED(e[Y]) + SQUARED(e[Z])) * sqrt(SQUARED(v[X]) + SQUARED(v[Y]) + SQUARED(v[Z]))));

		finalAngle = armAngle - triangleAngle;

		std::cout << "triangleAngle: " << this->toDegrees(triangleAngle) << "\n";
		std::cout << "armAngle: " << this->toDegrees(armAngle) << "\n";
		std::cout << "finalAngle: " << this->toDegrees(finalAngle) << "\n";

		double* unitVector = new double[3];
		unitVector[X] = cos(finalAngle);
		unitVector[Y] = sin(finalAngle);
		unitVector[Z] = 0;

		this->applyAngleOnPoints(points, i + 1, unitVector);

		ArmMovement* movement = new ArmMovement();
		movement->triangleAngle = triangleAngle;
		movement->armAngle = armAngle;
		movement->startAngle = startAngle;
		movement->endAngle = finalAngle;
		movement->angled = movement->endAngle - movement->startAngle;
		movement->startPoint = i;
		movement->pointAngle.x = points->at(movement->startPoint)[X];
		movement->pointAngle.y = points->at(movement->startPoint)[Y];
		movement->pointAngle.z = points->at(movement->startPoint)[Z];
		movement->endPoint = endPoint;

		startAngle = movement->endAngle;

		for (int j = 0; j < i; j++)
			movement->points.push_back(glm::vec3(
				movements->at(i - 1)->points.at(j).x,
				movements->at(i - 1)->points.at(j).y,
				movements->at(i - 1)->points.at(j).z
			));

		for (int j = i; j < this->parts->size(); j++)
			movement->points.push_back(glm::vec3(
				this->parts->at(j)->getPoint().x - this->parts->at(i)->getPoint().x,
				this->parts->at(j)->getPoint().y - this->parts->at(i)->getPoint().y,
				this->parts->at(j)->getPoint().z - this->parts->at(i)->getPoint().z
			));

		movements->push_back(movement);
	}

	return movements;
}

double Arm::toDegrees(double angleRadians)
{
	return angleRadians * 180 / M_PI;
}

double* Arm::getUnitVector(double point1X, double point1Y, double point1Z, double point2X, double point2Y, double point2Z)
{
	double x = point2X - point1X;
	double y = point2Y - point1Y;
	double z = point2Z - point2Z;

	double size = sqrt(SQUARED(x) + SQUARED(y) + SQUARED(z));

	double unitVector[3] = {x / size, y / size, z / size};

	return unitVector;
}

void Arm::applyAngleOnPoints(vector<double*>* points, int startPoint, double* unitVector)
{
	int pointsSize = points->size();

	for (int i = 0; i < points->size(); i++)
	{
		std::cout << points->at(i)[X] << ", " << points->at(i)[Y] << ", " << points->at(i)[Z] << "\n";
	}
	
	for (int i = startPoint; i < pointsSize; i++)
	{
		double* point = points->at(i);
		double* pointPrev = points->at(i - 1);

		point[X] = pointPrev[X] + this->parts->at(i  - 1)->getSize() * unitVector[X];
		point[Y] = pointPrev[Y] + this->parts->at(i - 1)->getSize() * unitVector[Y];
		point[Z] = pointPrev[Z] + this->parts->at(i - 1)->getSize() * unitVector[Z];
	}

	for (int i = 0; i < points->size(); i++)
	{
		std::cout << points->at(i)[X] << ", " << points->at(i)[Y] << ", " << points->at(i)[Z] << "\n";
	}
}

glm::vec3 Arm::getTarget()
{
	return this->target;
}
glm::vec4 Arm::getTargetColor()
{
	return this->targetColor;
}