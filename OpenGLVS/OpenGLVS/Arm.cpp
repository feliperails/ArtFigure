#include "Arm.h"

#include <iostream>

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

	vector<glm::vec3>* points = new vector<glm::vec3>();

	double sumRadius = 0.0f;
	double sumCenter = 0.0f;

	for (int i = 0, j = partsLength - 1; j >= 0; i++, j--)
	{
		glm::vec3 point = glm::vec3(sumCenter, 0.0f, 0.0f);
		points->push_back(point);
		this->parts->at(i)->setPoint(sumCenter, 0.0f, 0.0f);

		sumCenter += this->parts->at(i)->getSize();

		sumRadius += this->parts->at(j)->getSize();
		radiusList[j] = sumRadius;
	}

	{
		glm::vec3 point = glm::vec3(sumCenter, 0.0f, 0.0f);
		points->push_back(point);
	}

	for (int i = 0; i < partsLength; i++)
	{
		std::cout << points->at(i).x << ", " << points->at(i).y << ", " << points->at(i).z << " - " << radiusList[i] << "\n";
	}

	int positionCenterDetect;
	bool radiusDetect = false;
	for (int i = partsLength - 1; i >= 0; i--)
	{
		if (this->inCircle(points->at(i).x, points->at(i).y, points->at(i).z, radiusList[i], this->target.x, this->target.y, this->target.z))
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
		glm::vec3 point = points->at(i);
		glm::vec3 pointSecond = points->at(i + 1);
		glm::vec3 pointLast = points->at(partsLength);
		termOne = this->getSquareDistance(point.x, point.y, point.z, this->target.x, this->target.y, this->target.z);
		termTwo = this->getSquareDistance(point.x, point.y, point.z, pointSecond.x, pointSecond.y, pointSecond.z);
		triangleAngle = acos((termOne + termTwo - this->getSquareDistance(pointSecond.x, pointSecond.y, pointSecond.z, pointLast.x, pointLast.y, pointLast.z)) /
			(2 * sqrt(termOne) * sqrt(termTwo)));

		glm::vec3 v = glm::vec3(pointSecond.x - point.x, pointSecond.y - point.y, pointSecond.z - point.z);
		glm::vec3 e = glm::vec3(this->target.x - point.x, this->target.y - point.y, this->target.z - point.z);
		armAngle = acos((e.x * v.x + e.y * v.y + e.z * v.z) / (sqrt(SQUARED(e.x) + SQUARED(e.y) + SQUARED(e.z)) * sqrt(SQUARED(v.x) + SQUARED(v.y) + SQUARED(v.z))));

		finalAngle = armAngle - triangleAngle;

		std::cout << "triangleAngle: " << Util::toDegrees(triangleAngle) << "\n";
		std::cout << "armAngle: " << Util::toDegrees(armAngle) << "\n";
		std::cout << "finalAngle: " << Util::toDegrees(finalAngle) << "\n";

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

void Arm::applyAngleOnPoints(vector<double*>* points, int startPoint, double* unitVector)
{
	int pointsSize = points->size();

	for (int i = 0; i < points->size(); i++)
	{
		std::cout << points->at(i)[X] << ", " << points->at(i)[Y] << ", " << points->at(i)[Z] << "\n";
	}
	
	for (int i = startPoint; i < pointsSize; i++)
	{
		glm::vec3 point = points->at(i);
		double* pointPrev = points->at(i - 1);

		point.x = pointPrev[X] + this->parts->at(i  - 1)->getSize() * unitVector[X];
		point.y = pointPrev[Y] + this->parts->at(i - 1)->getSize() * unitVector[Y];
		point.z = pointPrev[Z] + this->parts->at(i - 1)->getSize() * unitVector[Z];
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