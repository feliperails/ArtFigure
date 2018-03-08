#pragma once

#include <vector>

// GLM Mathemtics
#include <glm/glm.hpp>

using namespace std;

class ArmMovement
{
public:
	ArmMovement();
	~ArmMovement();

	double armAngle;
	double triangleAngle;
	float startAngle;
	float endAngle;
	float angled;
	glm::vec3 pointAngle;
	unsigned int startPoint;
	unsigned int endPoint;

	vector<glm::vec3> points;
};

