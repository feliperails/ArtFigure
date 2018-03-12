#pragma once

#include <vector>
#include <GL/glew.h>

#include "Arm.h";
#include "ArmPart.h";
#include "Mesh.h";
#include "AbstractFigure.h";

using namespace std;

class ArtPicture : public AbstractFigure
{
public:
	ArtPicture();
	~ArtPicture();

	void build();
	void setArm(Arm* arm);
	void initPointMesh();
	vector<Mesh*>* getPointMeshList();
	void finishPointMesh();
private:
	Arm* arm;
	vector<Mesh*>* pointMeshList;

	void buildParts();
	void buildTarget();
};

