#include "ArmPart.h"



ArmPart::ArmPart()
{
}

ArmPart::ArmPart(int size, float red, float green, float blue, float alpha)
{
	this->setSize(size);
	this->setColor(red, green, blue, alpha);
}

void ArmPart::setSize(int size)
{
	this->size = size;
}

int ArmPart::getSize()
{
	return this->size;
}

void ArmPart::setColor(float red, float green, float blue, float alpha)
{
	this->color[0] = red;
	this->color[1] = green;
	this->color[2] = blue;
	this->color[3] = alpha;
}

float* ArmPart::getColor()
{
	return this->color;
}

void ArmPart::setPoint(float x, float y, float z)
{
	this->point.x = x;
	this->point.y = y;
	this->point.z = z;
}

glm::vec3 ArmPart::getPoint()
{
	return this->point;
}

ArmPart::~ArmPart()
{
}
