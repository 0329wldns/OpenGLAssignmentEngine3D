#pragma once
#include "pch.h"
#include "Object.h"

class RobotPart
{
	friend class Robot;

public:
	RobotPart() = default;
	RobotPart(Vector3 _scale, Vector3 _offset, Vector3 _color, RotateData _rotation, RobotPart* child = nullptr);
	~RobotPart() = default;

	void update(glm::mat4 parentTransform);
	void render(glm::mat4 parentTransform) const;

	void addChild(RobotPart* child) { this->children.push_back(child); }

private:
	Vector3 pos{};
	Vector3 scale{};
	Vector3 offset{};
	Color color{};
	RotateData rotation;
	vector<RobotPart*> children;
};

class Robot : public Object
{
public:
	Robot();
	~Robot();

	void update() override;
	void render() const override;

private:
	Vector3 moveDir{};
	float moveSpeed{ 300.0f };

	RobotPart* core;
	RobotPart* body;
	RobotPart* head;
	RobotPart* leftArm;
	RobotPart* rightArm;
	RobotPart* leftLeg;
	RobotPart* rightLeg;

};