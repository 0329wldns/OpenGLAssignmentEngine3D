#pragma once
#include "pch.h"
#include "Object.h"

class Tank;

class TankPart
{
	friend class Tank;

public:
	TankPart() = default;
	~TankPart() = default;

	void update(glm::mat4 parentTransform);
	void render(glm::mat4 parentTransform) const;

	void addChild(TankPart* child) { this->children.push_back(child); }

private:
	Vector3 pos{};
	Vector3 scale{};
	Vector3 offset{};
	Color color{};
	vector<TankPart*> children;
	RotateData rotation;
};

class Tank : public Object
{
public:
	Tank();
	~Tank();

	void update() override;
	void render() const override;

private:
	Vector3 moveDir{};
	float moveSpeed{ 300.0f };

	TankPart core;
	TankPart* lowerBody[2];
	TankPart* centerBody;
	TankPart* upperBody[2];
	TankPart* gun[2];
	TankPart* flag[2];
};