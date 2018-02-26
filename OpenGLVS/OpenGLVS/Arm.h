#pragma once

#include "GL\glew.h";
#include <vector>

#include "ArmPart.h";

using namespace std;

class Arm
{
public:
	Arm();
	~Arm();
	void Arm::add(ArmPart* part);
	vector<ArmPart*>* getParts();
	
private:
	vector<ArmPart*>* parts;
};

