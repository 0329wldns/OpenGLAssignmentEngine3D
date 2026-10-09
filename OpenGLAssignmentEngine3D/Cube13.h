#pragma once
#include "pch.h"
#include "Object.h"

class Cube13 : public Object
{
public:
	Cube13();
	~Cube13() = default;

	void update() override;
	void render() const override;

private:
	Color color;
};