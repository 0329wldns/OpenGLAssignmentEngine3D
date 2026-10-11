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
	void processKeyInput();

private:
	FaceData faceData[6];	// 앞뒤좌우상하 순
	bool keyState[9]{ false };	// y, t, f, s, b, 1, 2, 4, 5
};