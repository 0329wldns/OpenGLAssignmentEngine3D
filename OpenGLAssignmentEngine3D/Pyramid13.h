#pragma once
#include "pch.h"
#include "Object.h"

class Pyramid13 : public Object
{
public:
	Pyramid13();
	~Pyramid13() = default;

	void update() override;
	void render() const override;

	static void setInvisibleAllFace()
	{
		for (int i = 0; i < 5; ++i)
			face[i].isVisible = false;
	}

private:
	// 밑앞뒤좌우 순
	inline static FaceData face[5];
};