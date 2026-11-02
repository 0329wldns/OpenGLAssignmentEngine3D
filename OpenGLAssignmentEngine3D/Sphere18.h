#pragma once
#include "pch.h"
#include "Object.h"

class Sphere18 : public Object
{
public:
	Sphere18(Color _color, Vector3 _scale, float _orbitRadius = 0.0f, float _orbitTiltDeg = 0.0f, bool _useOrbitRotate = false);
	~Sphere18();

	void update() override;
	void render() const override;

	static void setCenter(Sphere18* _center) { center = _center; }

	void addMoon(Sphere18* child);

private:
	inline static Vector3 moveDir{};
	inline static float orbitRadiusDelta{ -1.0f };
	inline static float moveSpeed{ 300.0f };
	inline static Sphere18* center{ nullptr };	// 중심 행성

	Color color;
	vector<Sphere18*> moon;	// 위성들
	float orbitRadius;	// 공전 반경
	float orgOrbitRadius;	// 공전 반경 원래 값
	float orbitTiltDeg;	// 공전 축의 기울기, + -> 반시계 방향
	RotateData orbit;	// 공전
	RotateData orbitRotate;	// 공전궤도 자전
	bool useOrbitRotate;	// 공전궤도 자전 사용여부 플래그
};