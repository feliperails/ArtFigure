#pragma once

#include <vector>
#include <exception>
// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

#include "Util.h";
#include "ArmPart.h";
#include "ArmMovement.h";

using namespace std;

class ArmUnreachableException : public exception
{
	virtual const char* what() const throw()
	{
		return "Can not reach destination point.";
	}
};

class Arm
{
public:
	Arm();
	~Arm();
	void Arm::add(ArmPart* part);
	vector<ArmMovement*>* getMovements();
	vector<ArmPart*>* getParts();
	void setTarget(double x, double y, double z, float r, float g, float b, float a);
	glm::vec3 getTarget();
	glm::vec4 getTargetColor();
private:
	vector<ArmPart*>* parts;
	glm::vec3 target;
	glm::vec4 targetColor;

	bool Arm::inCircle(double centerX, double centerY, double centerZ, double radius, double pointX, double pointY, double pointZ);
	double Arm::getDistance(double point1X, double point1Y, double point1Z, double point2X, double point2Y, double point2Z);
	double Arm::getSquareDistance(double point1X, double point1Y, double point1Z, double point2X, double point2Y, double point2Z);
	void applyAngleOnPoints(vector<double*>* points, int startPoint, double* unitVector);
};

