#pragma once
#include "pch.h"
#include "Object.h"

class Cube14 : public Object
{
public:
	Cube14();
	~Cube14();

	virtual void update() override;
	virtual void render() const override;

private:
	void randomizeColor();
};