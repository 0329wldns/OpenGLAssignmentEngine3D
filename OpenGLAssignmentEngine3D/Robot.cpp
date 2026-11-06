#include "pch.h"
#include "Robot.h"
#include "ShaderManager.h"
#include "MeshManager.h"
#include "TimeManager.h"
#include "KeyManager.h"

Robot::Robot()
{
	core = new RobotPart();

	body = new RobotPart(
		Vector3(100.0f, 130.0f, 50.0f)
		, Vector3(0.0f, 195.0f, 0.0f)
		, COLOR_BLUE
		, RotateData());

	head = new RobotPart(
		Vector3(body->scale.z)
		, Vector3(0.0f, body->scale.y / 2.0f + body->scale.z / 2.0f, 0.0f)
		, COLOR_WHITE
		, RotateData());

	leftArm = new RobotPart(
		Vector3(20.0f, body->scale.y, 20.0f)
		, Vector3(-body->scale.x / 2.0f - 10.0f, 0.0f, 0.0f)
		, COLOR_RED
		, RotateData());

	RotateData armRot;
	armRot.axis = Vector3(1.0f, 0.0f, 0.0f);
	armRot.offset = Vector3(0.0f, leftArm->scale.y / 2.0f, 0.0f);
	armRot.targetDegree = 30.0f;
	armRot.isReverse = true;
	armRot.isActive = true;

	leftArm->rotation = armRot;
	rightArm = new RobotPart(*leftArm);
	rightArm->offset.x *= -1.0f;
	rightArm->rotation.speed *= -1.0f;
	rightArm->rotation.targetDegree *= -1.0f;

	leftLeg = new RobotPart(
		Vector3(30.0f, body->scale.y, 30.0f)
		, Vector3(-25.0f, -body->scale.y, 0.0f)
		, COLOR_GREEN
		, RotateData());

	rightLeg = new RobotPart(*leftLeg);
	rightLeg->offset.x *= -1.0f;
	rightLeg->rotation = leftArm->rotation;
	leftLeg->rotation = rightArm->rotation;

	core->addChild(body);
	body->addChild(head);
	body->addChild(leftArm);
	body->addChild(rightArm);
	body->addChild(leftLeg);
	body->addChild(rightLeg);
}

Robot::~Robot()
{
}

void Robot::update()
{
	float  dt{ TimeManager::getInstance().getDeltaTime() };

	if (KeyManager::getInstance().getKeyState(KEY::W) == KEY_STATE::TAP) moveDir.z -= 1.0f;
	else if (KeyManager::getInstance().getKeyState(KEY::W) == KEY_STATE::AWAY) moveDir.z += 1.0f;
	if (KeyManager::getInstance().getKeyState(KEY::A) == KEY_STATE::TAP) moveDir.x -= 1.0f;
	else if (KeyManager::getInstance().getKeyState(KEY::A) == KEY_STATE::AWAY) moveDir.x += 1.0f;
	if (KeyManager::getInstance().getKeyState(KEY::S) == KEY_STATE::TAP) moveDir.z += 1.0f;
	else if (KeyManager::getInstance().getKeyState(KEY::S) == KEY_STATE::AWAY) moveDir.z -= 1.0f;
	if (KeyManager::getInstance().getKeyState(KEY::D) == KEY_STATE::TAP) moveDir.x += 1.0f;
	else if (KeyManager::getInstance().getKeyState(KEY::D) == KEY_STATE::AWAY) moveDir.x -= 1.0f;

	if (KeyManager::getInstance().getKeyState(KEY::T) == KEY_STATE::TAP)
	{
		body->rotation.isActive = !body->rotation.isActive;
	}

	core->pos += moveDir * moveSpeed * dt;
	glm::mat4 myMatrix{ 1.0f };
	myMatrix = glm::translate(myMatrix, core->pos);
	core->update(myMatrix);
}

void Robot::render() const
{
	ShaderManager::getInstance().useProgram("default");

	core->render(glm::mat4(1.0f));
}

RobotPart::RobotPart(Vector3 _scale, Vector3 _offset, Vector3 _color, RotateData _rotation, RobotPart* child)
	: scale(_scale)
	, offset(_offset)
	, color(_color)
	, rotation(_rotation)
{
	if (child)
	{
		this->children.push_back(child);
	}
}

void RobotPart::update(glm::mat4 parentTransform)
{
	rotation.update();

	glm::mat4 myMatrix{ 1.0f };
	myMatrix = glm::translate(myMatrix, offset);
	myMatrix = myMatrix * rotation.getRotationMatrix();

	pos = parentTransform * myMatrix * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	for (auto& child : children)
	{
		child->update(parentTransform * myMatrix);
	}
}

void RobotPart::render(glm::mat4 parentTransform) const
{
	glm::mat4 model{ 1.0f };
	glm::mat4 rotateMatrix{ glm::rotate(parentTransform, glm::radians(rotation.degree), rotation.axis) };

	model = glm::translate(model, pos);
	model = model * rotateMatrix;
	model = glm::scale(model, scale);

	ShaderManager::getInstance().setMat4("default", "model", model);
	ShaderManager::getInstance().setVec3("default", "color", color);

	MeshManager::getInstance().drawMesh("cube");
	// MeshManager::getInstance().drawDot();

	for (auto& child : children)
	{
		child->render(rotateMatrix);
	}
}