#include "Arm.h"

Arm::Arm()
{
	this->parts = new vector<ArmPart*>;
}

void Arm::add(ArmPart* part)
{
	this->parts->push_back(part);
}


Arm::~Arm()
{
}

vector<ArmPart*>* Arm::getParts()
{
	return this->parts;
}