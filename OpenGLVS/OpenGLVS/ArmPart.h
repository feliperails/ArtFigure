#pragma once

#include "GL/glew.h"

class ArmPart
{
public:
	ArmPart();
	ArmPart(GLuint size, GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	~ArmPart();

	void setSize(GLuint size);
	void setColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
	GLuint getSize();
	GLfloat* getColor();
private:
	GLuint size;
	GLfloat color[4];
};

