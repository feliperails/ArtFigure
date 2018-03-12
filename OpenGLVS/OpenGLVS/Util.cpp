#include "Util.h"

#define SQUARED(x)	(x)*(x)

Util::Util()
{
}

double* Util::getUnitVector(glm::vec3 point1, glm::vec3 point2)
{
	double x = point2.x - point1.x;
	double y = point2.y - point1.y;
	double z = point2.z - point1.z;

	double size = sqrt(SQUARED(x) + SQUARED(y) + SQUARED(z));

	double unitVector[3] = { x / size, y / size, z / size };

	return unitVector;
}

double Util::toDegrees(double angleRadians)
{
	return angleRadians * 180 / M_PI;
}