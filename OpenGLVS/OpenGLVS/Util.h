#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

// GLM Mathemtics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Util
{
public:
	static double* getUnitVector(glm::vec3 point1, glm::vec3 point2);
	static double toDegrees(double angleRadians);
private:
	Util();
};

