#pragma once

#include <vector>
#include "GL\glew.h"

using namespace std;

class Mesh
{
public:
	Mesh(vector<GLfloat>* vertices);
	~Mesh();
	void init();
	void bind();
	void draw();
	void endDraw();
	void finish();

private:
	GLuint vertexArrayObject;
	GLuint vertexBufferObject;
	vector<GLfloat>* vertices;
	GLuint verticesSize;
};

