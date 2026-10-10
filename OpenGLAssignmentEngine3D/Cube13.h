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

	static inline void setInvisibleAllFace()
	{
		for (int i = 0; i < 6; ++i)
			face[i].isVisible = false;
	}

private:
	inline static faceData face[6];	// 앞뒤좌우상하 순
};