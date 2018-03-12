#include "ArtPicture.h"

ArtPicture::ArtPicture()
{
	this->pointMeshList = new vector<Mesh*>();
}

void ArtPicture::build()
{
	this->buildParts();
	this->buildTarget();
}

void ArtPicture::buildParts()
{
	vector<ArmPart*> parts = *this->arm->getParts();

	for (ArmPart* &part : parts)
	{
		GLfloat* color = part->getColor();

		GLfloat verticesData[] =
		{
			0.0f,			 -0.2f, 0.0f, color[0], color[1], color[2], color[3],
			part->getSize(), -0.2f, 0.0f, color[0], color[1], color[2], color[3],
			part->getSize(),  0.2f, 0.0f, color[0], color[1], color[2], color[3],
			part->getSize(),  0.2f, 0.0f, color[0], color[1], color[2], color[3],
			0.0f,			  0.2f, 0.0f, color[0], color[1], color[2], color[3],
			0.0f,			 -0.2f, 0.0f, color[0], color[1], color[2], color[3]
		};

		vector<GLfloat>* vertices = new vector<GLfloat>();

		for each(GLfloat value in verticesData)
		{
			vertices->push_back(value);
		}

		this->meshList->push_back(new Mesh(vertices));
	}
}

void ArtPicture::buildTarget()
{
	glm::vec3 point = this->arm->getTarget();
	glm::vec4 color = this->arm->getTargetColor();

	GLfloat verticesData[] =
	{
		-0.5f, -0.5f, -0.5f, color.r, color.g, color.b, color.a,
		+0.5f, -0.5f, -0.5f, color.r, color.g, color.b, color.a,
		+0.5f, +0.5f, -0.5f, color.r, color.g, color.b, color.a,
		+0.5f, +0.5f, -0.5f, color.r, color.g, color.b, color.a,
		-0.5f, +0.5f, -0.5f, color.r, color.g, color.b, color.a,
		-0.5f, -0.5f, -0.5f, color.r, color.g, color.b, color.a
	};

	vector<GLfloat>* vertices = new vector<GLfloat>();

	for each(GLfloat value in verticesData)
	{
		vertices->push_back(value);
	}

	this->pointMeshList->push_back(new Mesh(vertices));
}

void ArtPicture::setArm(Arm* arm)
{
	this->arm = arm;
}

void ArtPicture::initPointMesh()
{
	for (Mesh* &mesh : *this->pointMeshList)
		mesh->init();
}

vector<Mesh*>* ArtPicture::getPointMeshList()
{
	return this->pointMeshList;
}

void ArtPicture::finishPointMesh()
{
	for (Mesh* &mesh : *this->pointMeshList)
		mesh->finish();
}

ArtPicture::~ArtPicture()
{
}
