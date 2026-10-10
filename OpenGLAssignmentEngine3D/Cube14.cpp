#include "pch.h"
#include "Cube14.h"
#include "ShaderManager.h"
#include "MeshManager.h"
#include "KeyManager.h"
#include "TimeManager.h"
#include "SceneManager.h"
#include "Scene_Assignment14.h"

Cube14::Cube14()
{
	setPos(0.0f, 0.0f, 0.0f);
	setScale(0.3f, 0.3f, 0.3f);
	randomizeColor();
}

Cube14::~Cube14()
{
	MeshManager::getInstance().resetMeshColors("cube");
}

void Cube14::update()
{
	float dt{ TimeManager::getInstance().getDeltaTime() };
	const Vector2& rotateDir{ static_cast<Scene_Assignment14*>(SceneManager::getInstance().getCurScene())->getRotateDir() };
	const Vector2& moveDir{ static_cast<Scene_Assignment14*>(SceneManager::getInstance().getCurScene())->getMoveDir() };

	rotateDegree.x += rotateDir.x * 90.0f * dt;
	rotateDegree.y += rotateDir.y * 90.0f * dt;
	if (rotateDegree.x > 360.0f) rotateDegree.x -= 360.0f;
	else if (rotateDegree.x < 0.0f) rotateDegree.x += 360.0f;
	if (rotateDegree.y > 360.0f) rotateDegree.y -= 360.0f;
	else if (rotateDegree.y < 0.0f) rotateDegree.y += 360.0f;

	Vector3 myPos{ getPos() };
	Vector3 myScale{ getScale() };
	myPos.x += moveDir.x * 0.3f * dt;
	myPos.y += moveDir.y * 0.3f * dt;
	if (myPos.x + myScale.x > 1.0f) myPos.x = 1.0f - myScale.x;
	else if (myPos.x - myScale.x < -1.0f) myPos.x = -1.0f + myScale.x;
	if (myPos.y + myScale.y > 1.0f) myPos.y = 1.0f - myScale.y;
	else if (myPos.y - myScale.y < -1.0f) myPos.y = -1.0f + myScale.y;
	setPos(myPos);

	if (KeyManager::getInstance().getKeyState(KEY::S) == KEY_STATE::TAP)
	{
		setPos(0.0f, 0.0f, 0.0f);
		rotateDegree.x = 0.0f;
		rotateDegree.y = 0.0f;
	}
}

void Cube14::render() const
{
	bool drawLine{ static_cast<Scene_Assignment14*>(SceneManager::getInstance().getCurScene())->getDrawLine() };
	ShaderManager::getInstance().useProgram("default");

	Vector3 myPos{ getPos() };
	Vector3 myScale{ getScale() };

	glm::mat4 model{ 1.0f };
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, myPos);
	model = glm::rotate(model, glm::radians(rotateDegree.x), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotateDegree.y), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, myScale * 2.0f);
	ShaderManager::getInstance().setMat4("default", "model", model);
	ShaderManager::getInstance().setVec3("default", "color", COLOR_WHITE);
	ShaderManager::getInstance().setFloat("default", "transparency", 1.0f);

	MeshManager::getInstance().drawMesh("cube", drawLine);
}

void Cube14::randomizeColor()
{
	std::vector<glm::vec3> randomColors;
	randomColors.reserve(36);	// reserve - 용량을 늘려둬서 push_back 시 재할당이 발생하지 않음
	
	for (int i = 0; i < 36; ++i)
	{
		glm::vec3 color{ realDist(gen), realDist(gen), realDist(gen) };
		randomColors.push_back(color);
	}
	MeshManager::getInstance().updateMeshColors("cube", randomColors);
}
