#pragma once
#include "pch.h"
#include "Object.h"

class Sphere18 : public Object
{
public:
	Sphere18(Color _color, Vector3 _scale, float _orbitRadius = 0.0f, float _orbitTiltDeg = 0.0f);
	~Sphere18();

	void update() override;
	void render() const override;

	void addMoon(Sphere18* child);

private:
	Color color;
	vector<Sphere18*> moon;
	float orbitRadius;
	float orbitTiltDeg;	// 공전 축의 기울기, + -> 반시계 방향
	RotateData orbit;	// 공전
};