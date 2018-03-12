#pragma once

#include <vector>

#include "Mesh.h"

using namespace std;

class AbstractFigure
{
public:
	AbstractFigure();
	~AbstractFigure();

	void initMesh();
	vector<Mesh*>* getMeshList();
	void finishMesh();

	void build();
protected:
	vector<Mesh*>* meshList;
};

