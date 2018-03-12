#include "AbstractFigure.h"



AbstractFigure::AbstractFigure()
{
	this->meshList = new vector<Mesh*>();
}

void AbstractFigure::initMesh()
{
	for (Mesh* &mesh : *this->meshList)
	{
		mesh->init();
	}
}

void AbstractFigure::finishMesh()
{
	for (Mesh* &mesh : *this->meshList)
	{
		mesh->finish();
	}
}

vector<Mesh*>* AbstractFigure::getMeshList()
{
	return this->meshList;
}

AbstractFigure::~AbstractFigure()
{
}
