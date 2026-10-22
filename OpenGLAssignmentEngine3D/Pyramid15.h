#pragma once
#include "pch.h"
#include "Object.h"

class Pyramid15 : public Object
{
public:
	Pyramid15();
	~Pyramid15();

	virtual void update() override;
	virtual void render() const override;

private:
	void randomizeColor() {};
	void initRotateData();
	void processKeyInput();

private:
	FaceData faceData[5];	// 밑앞뒤좌우 순
};