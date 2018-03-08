#include "ArtPicture.h"

ArtPicture::ArtPicture()
{
	this->meshList = new vector<Mesh*>();
}

void ArtPicture::build()
{
	vector<ArmPart*> parts = *this->arm->getParts();

	for (ArmPart* &part : parts)
	{
		GLfloat* color = part->getColor();
		
		GLfloat verticesData[] =
		{
			0.0f,			 -0.1f, 0.0f, color[0], color[1], color[2], color[3],
			part->getSize(), -0.1f, 0.0f, color[0], color[1], color[2], color[3],
			part->getSize(),  0.1f, 0.0f, color[0], color[1], color[2], color[3],
			part->getSize(),  0.1f, 0.0f, color[0], color[1], color[2], color[3],
			0.0f,			  0.1f, 0.0f, color[0], color[1], color[2], color[3],
			0.0f,			 -0.1f, 0.0f, color[0], color[1], color[2], color[3]
		};

		vector<GLfloat>* vertices = new vector<GLfloat>();

		for each(GLfloat value in verticesData)
		{
			vertices->push_back(value);
		}

		this->meshList->push_back(new Mesh(vertices));
	}
}

void ArtPicture::initMesh()
{
	for (Mesh* &mesh : *this->meshList)
	{
		mesh->init();
	}
}

void ArtPicture::finishMesh()
{
	for (Mesh* &mesh : *this->meshList)
	{
		mesh->finish();
	}
}

vector<Mesh*>* ArtPicture::getMeshList()
{
	return this->meshList;
}

void ArtPicture::setArm(Arm* arm)
{
	this->arm = arm;
}

ArtPicture::~ArtPicture()
{
}
