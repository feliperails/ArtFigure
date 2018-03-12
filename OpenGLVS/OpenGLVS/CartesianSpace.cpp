#include "CartesianSpace.h"



CartesianSpace::CartesianSpace()
{
	
}

void CartesianSpace::build()
{
	double z = 0.0f;

	for (GLfloat i = -30.0f; i <= 30.0f; i++)
	{
		GLfloat verticesData[] =
		{
			i,			-0.3f, z,	0.0f, 0.0f, 0.0f, 1.0f,
			i + 0.1f,	-0.3f, z,	0.0f, 0.0f, 0.0f, 1.0f,
			i + 0.1f,	 0.3f, z,	0.0f, 0.0f, 0.0f, 1.0f,
			i + 0.1f,	 0.3f, z,	0.0f, 0.0f, 0.0f, 1.0f,
			i,			 0.3f, z,	0.0f, 0.0f, 0.0f, 1.0f,
			i,			-0.3f, z,	0.0f, 0.0f, 0.0f, 1.0f
		};

		vector<GLfloat>* vertices = new vector<GLfloat>();

		for each(GLfloat value in verticesData)
		{
			vertices->push_back(value);
		}

		this->meshList->push_back(new Mesh(vertices));
	}

	{
		GLfloat verticesData[] =
		{
			-30.0f, -0.1f, z,	0.0f, 0.0f, 0.0f, 1.0f,
			+30.0f, -0.1f, z,	0.0f, 0.0f, 0.0f, 1.0f,
			+30.0f,  0.1f, z,	0.0f, 0.0f, 0.0f, 1.0f,
			+30.0f,  0.1f, z,	0.0f, 0.0f, 0.0f, 1.0f,
			-30.0f,  0.1f, z,	0.0f, 0.0f, 0.0f, 1.0f,
			-30.0f, -0.1f, z,	0.0f, 0.0f, 0.0f, 1.0f
		};

		vector<GLfloat>* vertices = new vector<GLfloat>();

		for each(GLfloat value in verticesData)
		{
			vertices->push_back(value);
		}

		this->meshList->push_back(new Mesh(vertices));
	}

	for (GLfloat i = -30.0f; i <= 30.0f; i++)
	{
		GLfloat verticesData[] =
		{
			-0.3f, i,			z,	0.0f, 0.0f, 0.0f, 1.0f,
			-0.3f, i + 0.1f,	z,	0.0f, 0.0f, 0.0f, 1.0f,
			 0.3f, i + 0.1f,	z,	0.0f, 0.0f, 0.0f, 1.0f,
			 0.3f, i + 0.1f,	z,	0.0f, 0.0f, 0.0f, 1.0f,
			 0.3f, i,			z,	0.0f, 0.0f, 0.0f, 1.0f,
			-0.3f, i,			z,	0.0f, 0.0f, 0.0f, 1.0f
		};

		vector<GLfloat>* vertices = new vector<GLfloat>();

		for each(GLfloat value in verticesData)
		{
			vertices->push_back(value);
		}

		this->meshList->push_back(new Mesh(vertices));
	}

	GLfloat verticesData[] =
	{
		-0.1f, -30.0f, z,	0.0f, 0.0f, 0.0f, 1.0f,
		-0.1f,  30.0f, z,	0.0f, 0.0f, 0.0f, 1.0f,
		 0.1f,  30.0f, z,	0.0f, 0.0f, 0.0f, 1.0f,
		 0.1f,  30.0f, z,	0.0f, 0.0f, 0.0f, 1.0f,
		 0.1f, -30.0f, z,	0.0f, 0.0f, 0.0f, 1.0f,
		-0.1f, -30.0f, z,	0.0f, 0.0f, 0.0f, 1.0f
	};

	vector<GLfloat>* vertices = new vector<GLfloat>();

	for each(GLfloat value in verticesData)
	{
		vertices->push_back(value);
	}

	this->meshList->push_back(new Mesh(vertices));
}

CartesianSpace::~CartesianSpace()
{
}
