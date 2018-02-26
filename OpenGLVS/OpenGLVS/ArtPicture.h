#pragma once

#include <vector>
#include <GL/glew.h>

#include "Arm.h";
#include "ArmPart.h";
#include "Mesh.h";

using namespace std;

class ArtPicture
{
public:
	ArtPicture();
	~ArtPicture();

	void build();
	void setArm(Arm* arm);
	void initMesh();
	vector<Mesh*>* getMeshList();
	void finishMesh();
private:
	vector<Mesh*>* meshList;

	Arm* arm;
};

