#pragma once

// GLM Mathemtics
#include <glm/glm.hpp>

class ArmPart
{
public:
	ArmPart();
	ArmPart(int size, float red, float green, float blue, float alpha);
	~ArmPart();

	void setSize(int size);
	void setColor(float red, float green, float blue, float alpha);
	int getSize();
	glm::vec4 getColor();
	void setPoint(float x, float y, float z);
	glm::vec3 getPoint();
private:
	int size;
	glm::vec4 color;
	glm::vec3 point;
};

