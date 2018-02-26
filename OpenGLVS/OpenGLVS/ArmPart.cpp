#include "ArmPart.h"



ArmPart::ArmPart()
{
}

ArmPart::ArmPart(GLuint size, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	this->setSize(size);
	this->setColor(red, green, blue, alpha);
}

void ArmPart::setSize(GLuint size)
{
	this->size = size;
}

GLuint ArmPart::getSize()
{
	return this->size;
}

void ArmPart::setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	this->color[0] = red;
	this->color[1] = green;
	this->color[2] = blue;
	this->color[3] = alpha;
}

GLfloat* ArmPart::getColor()
{
	return this->color;
}

ArmPart::~ArmPart()
{
}
