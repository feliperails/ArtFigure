#include "Mesh.h"

Mesh::Mesh(vector<GLfloat>* vertices)
{
	this->vertices = vertices;
	this->verticesSize = this->vertices->size();
}

void Mesh::init()
{
	vector<GLfloat> verticesData = *this->vertices;

	glGenBuffers(1, &this->vertexBufferObject);
	// Bind our Vertex Array Object first, then bind and set our buffers and pointers.
	glGenVertexArrays(1, &this->vertexArrayObject);
	glBindVertexArray(this->vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, this->verticesSize * sizeof(GLfloat), &verticesData[0], GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}

void Mesh::bind()
{
	glBindVertexArray(this->vertexArrayObject);
}

void Mesh::draw()
{
	glDrawArrays(GL_TRIANGLES, 0, this->verticesSize);
}

void Mesh::endDraw()
{
	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	
}

void Mesh::finish()
{
	glDeleteVertexArrays(1, &this->vertexArrayObject);
	glDeleteBuffers(1, &this->vertexBufferObject);
}
