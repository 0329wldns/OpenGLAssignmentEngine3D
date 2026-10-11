#pragma once
#include "pch.h"
#include "Object.h"

class Cube15 : public Object
{
public:
	Cube15();
	~Cube15();
	void update() override;
	void render() const override;

private:
	void randomizeColor();

private:
	FaceData faceData[6];	// 앞뒤좌우상하 순
};