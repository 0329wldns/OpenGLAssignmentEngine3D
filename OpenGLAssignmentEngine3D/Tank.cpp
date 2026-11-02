#include "pch.h"
#include "Tank.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "ShaderManager.h"
#include "MeshManager.h"

Tank::Tank()
{
	lowerBody[0] = new TankPart();
	lowerBody[1] = new TankPart();
	centerBody = new TankPart();
	upperBody[0] = new TankPart();
	upperBody[1] = new TankPart();
	gun[0] = new TankPart();
	gun[1] = new TankPart();
	flag[0] = new TankPart();
	flag[1] = new TankPart();

	lowerBody[0]->scale = Vector3(100.0f, 50.0f, 50.0f);
	lowerBody[1]->scale = Vector3(100.0f, 50.0f, 50.0f);
	lowerBody[0]->offset = Vector3(-60.0f, lowerBody[0]->scale.y / 2.0f, 0.0f);
	lowerBody[1]->offset = Vector3(60.0f, lowerBody[1]->scale.y / 2.0f, 0.0f);
	lowerBody[0]->color = COLOR_BLACK;
	lowerBody[1]->color = COLOR_BLACK;

	centerBody->scale = Vector3(120.0f, 30.0f, 30.0f);
	centerBody->offset = Vector3(0.0f, lowerBody[0]->scale.y + centerBody->scale.y / 2.0f, 0.0f);
	centerBody->color = COLOR_GRAY;

	upperBody[0]->scale = Vector3(60.0f, 30.0f, 40.0f);
	upperBody[1]->scale = Vector3(60.0f, 30.0f, 40.0f);
	upperBody[0]->offset = Vector3(-60.0f, centerBody->scale.y / 2.0f + upperBody[0]->scale.y / 2.0f, 0.0f);
	upperBody[1]->offset = Vector3(60.0f, centerBody->scale.y / 2.0f + upperBody[1]->scale.y / 2.0f, 0.0f);
	upperBody[0]->color = COLOR_RED;
	upperBody[1]->color = COLOR_RED;

	gun[0]->scale = Vector3(5.0f, 5.0f, 50.0f);
	gun[1]->scale = Vector3(5.0f, 5.0f, 50.0f);
	gun[0]->offset = Vector3(0.0f, 0.0f, upperBody[0]->scale.z / 2.0f + gun[0]->scale.z / 2.0f);
	gun[1]->offset = Vector3(0.0f, 0.0f, upperBody[1]->scale.z / 2.0f + gun[1]->scale.z / 2.0f);
	gun[0]->color = COLOR_YELLOW;
	gun[1]->color = COLOR_YELLOW;
	gun[0]->rotation.offset = Vector3(0.0f, 0.0f, -gun[0]->scale.z / 2.0f);
	gun[1]->rotation.offset = Vector3(0.0f, 0.0f, -gun[1]->scale.z / 2.0f);
	gun[0]->rotation.isReverse = true;
	gun[1]->rotation.isReverse = true;
	gun[0]->rotation.targetDegree = 30.0f;
	gun[1]->rotation.targetDegree = -30.0f;
	gun[0]->rotation.speed = 60.0f;
	gun[1]->rotation.speed = -60.0f;

	flag[0]->scale = Vector3(10.0f, 40.0f, 10.0f);
	flag[1]->scale = Vector3(10.0f, 40.0f, 10.0f);
	flag[0]->offset = Vector3(0.0f, upperBody[0]->scale.y / 2.0f + flag[0]->scale.y / 2.0f, 0.0f);
	flag[1]->offset = Vector3(0.0f, upperBody[1]->scale.y / 2.0f + flag[1]->scale.y / 2.0f, 0.0f);
	flag[0]->color = COLOR_BLUE;
	flag[1]->color = COLOR_BLUE;
	flag[0]->rotation.axis = Vector3(1.0f, 0.0f, 0.0f);
	flag[1]->rotation.axis = Vector3(1.0f, 0.0f, 0.0f);
	flag[0]->rotation.offset = Vector3(0.0f, -flag[0]->scale.y / 2.0f, 0.0f);
	flag[1]->rotation.offset = Vector3(0.0f, -flag[1]->scale.y / 2.0f, 0.0f);
	flag[0]->rotation.isReverse = true;
	flag[1]->rotation.isReverse = true;
	flag[0]->rotation.targetDegree = 30.0f;
	flag[1]->rotation.targetDegree = -30.0f;
	flag[0]->rotation.speed = 60.0f;
	flag[1]->rotation.speed = -60.0f;

	core.addChild(lowerBody[0]);
	core.addChild(lowerBody[1]);
	core.addChild(centerBody);
	centerBody->addChild(upperBody[0]);
	centerBody->addChild(upperBody[1]);
	upperBody[0]->addChild(gun[0]);
	upperBody[1]->addChild(gun[1]);
	upperBody[0]->addChild(flag[0]);
	upperBody[1]->addChild(flag[1]);
}

Tank::~Tank()
{
	delete lowerBody[0];
	delete lowerBody[1];
	delete centerBody;
	delete  upperBody[0];
	delete upperBody[1];
	delete gun[0];
	delete gun[1];
	delete flag[0];
	delete flag[1];
}

void Tank::update()
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
	if (KeyManager::getInstance().getKeyState(KEY::T) == KEY_STATE::TAP) centerBody->rotation.isActive = !centerBody->rotation.isActive;
	if (KeyManager::getInstance().getKeyState(KEY::G) == KEY_STATE::TAP)
	{
		gun[0]->rotation.isActive = !gun[0]->rotation.isActive;
		gun[1]->rotation.isActive = !gun[1]->rotation.isActive;
	}
	if (KeyManager::getInstance().getKeyState(KEY::P) == KEY_STATE::TAP)
	{
		flag[0]->rotation.isActive = !flag[0]->rotation.isActive;
		flag[1]->rotation.isActive = !flag[1]->rotation.isActive;
	}
	if (KeyManager::getInstance().getKeyState(KEY::NUM1) == KEY_STATE::TAP) upperBody[0]->rotation.isActive = !upperBody[0]->rotation.isActive;
	if (KeyManager::getInstance().getKeyState(KEY::NUM2) == KEY_STATE::TAP) upperBody[1]->rotation.isActive = !upperBody[1]->rotation.isActive;
	
	core.pos += moveDir * moveSpeed * dt;
	glm::mat4 myMatrix{ 1.0f };
	myMatrix = glm::translate(myMatrix, core.pos);
	core.update(myMatrix);
}

void Tank::render() const
{
	ShaderManager::getInstance().useProgram("default");

	core.render(glm::mat4(1.0f));
}

void TankPart::update(glm::mat4 parentTransform)
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

void TankPart::render(glm::mat4 parentTransform) const
{
	glm::mat4 model{ 1.0f };
	glm::mat4 rotateMatrix{ parentTransform * rotation.getRotationMatrix() };

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
