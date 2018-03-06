#include "Arm.h"

#include <iostream>

#define _USE_MATH_DEFINES
#include <math.h>

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

void Arm::setTarget(double x, double y, double z)
{
	this->target[0] = x;
	this->target[1] = y;
	this->target[2] = z;
}

bool Arm::inCircle(double centerX, double centerY, double centerZ, double radius, double pointX, double pointY, double pointZ)
{
	return pow(radius, 2) >= pow(centerX - pointX, 2) + pow(centerY - pointY, 2) + pow(centerZ - pointZ, 2);
}

double Arm::getDistance(double point1X, double point1Y, double point1Z, double point2X, double point2Y, double point2Z)
{

}
double Arm::getSquareDistance(double point1X, double point1Y, double point1Z, double point2X, double point2Y, double point2Z)
{
	return pow(point2X - point1X, 2) + pow(point2Y - point1Y, 2) + pow(point2Z - point1Z, 2);
}

double Arm::getDistance(double point1X, double point1Y, double point1Z, double point2X, double point2Y, double point2Z)
{
	return sqrt(this->getSquareDistance(point1X, point1Y, point1Z, point2X, point2Y, point2Z));
}

vector<double>* Arm::getMovements()
{
	const int partsLength = this->parts->size();
	
	vector<double>* movements = new vector<double>();
	vector<double> radiusList(partsLength);
	vector<double> positionCenterList(partsLength);

	double sumRadius = 0.0f;
	double sumCenter = 0.0f;

	for (int i = 0, j = partsLength - 1; j >= 0; i++, j--)
	{
		positionCenterList[i] = sumCenter;
		sumCenter += this->parts->at(i)->getSize();

		sumRadius += this->parts->at(j)->getSize();
		radiusList[j] = sumRadius;
	}

	for (int i = 0; i < partsLength; i++)
	{
		cout << positionCenterList[i] << ", 0, 0 - " << radiusList[i] << "\n";
	}

	int positionCenterDetect;
	bool radiusDetect = false;
	for (int i = partsLength - 1; i >= 0; i--)
	{
		if (this->inCircle(positionCenterList[i], 0, 0, radiusList[i], this->target[0], this->target[1], this->target[2]))
		{
			positionCenterDetect = i;
			radiusDetect = true;
		}
	}

	if (!radiusDetect)
		throw new ArmUnreachableException();



	return movements;
}

