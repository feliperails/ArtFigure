#pragma once

class ArmPart
{
public:
	ArmPart();
	ArmPart(int size, float red, float green, float blue, float alpha);
	~ArmPart();

	void setSize(int size);
	void setColor(float red, float green, float blue, float alpha);
	int getSize();
	float* getColor();
private:
	int size;
	float color[4];
};

