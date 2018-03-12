#pragma once

#include <GL/glew.h>
#include <vector>

#include "AbstractFigure.h";
#include "Mesh.h";

using namespace std;

class CartesianSpace : public AbstractFigure
{
public:
	CartesianSpace();
	~CartesianSpace();

	void build();
};

