#include "pch.h"
#include "Scene_Assignment13.h"
#include "KeyManager.h"
#include "EventFunc.h"
#include "Cube13.h"
#include "ShaderManager.h"
#include "MeshManager.h"
#include "Pyramid13.h"

void Scene_Assignment13::processKeyInput()
{
	if (KeyManager::getInstance().getKeyState(KEY::C) == KEY_STATE::TAP
		|| KeyManager::getInstance().getKeyState(KEY::NUM1) == KEY_STATE::TAP
		|| KeyManager::getInstance().getKeyState(KEY::NUM2) == KEY_STATE::TAP
		|| KeyManager::getInstance().getKeyState(KEY::NUM3) == KEY_STATE::TAP
		|| KeyManager::getInstance().getKeyState(KEY::NUM4) == KEY_STATE::TAP
		|| KeyManager::getInstance().getKeyState(KEY::NUM5) == KEY_STATE::TAP
		|| KeyManager::getInstance().getKeyState(KEY::NUM6) == KEY_STATE::TAP)
	{
		Pyramid13::setInvisibleAllFace();
	}
	if (KeyManager::getInstance().getKeyState(KEY::T) == KEY_STATE::TAP
		|| KeyManager::getInstance().getKeyState(KEY::NUM7) == KEY_STATE::TAP
		|| KeyManager::getInstance().getKeyState(KEY::NUM8) == KEY_STATE::TAP
		|| KeyManager::getInstance().getKeyState(KEY::NUM9) == KEY_STATE::TAP
		|| KeyManager::getInstance().getKeyState(KEY::NUM0) == KEY_STATE::TAP)
	{
		Cube13::setInvisibleAllFace();
	}
	if (KeyManager::getInstance().getKeyState(KEY::ESC) == KEY_STATE::TAP)
		changeScene(SCENE_TYPE::START);
	if (KeyManager::getInstance().getKeyState(KEY::MINUS) == KEY_STATE::TAP)
		glDisable(GL_CULL_FACE);
	if (KeyManager::getInstance().getKeyState(KEY::EQUAL) == KEY_STATE::TAP)
		glEnable(GL_CULL_FACE);
}

void Scene_Assignment13::update()
{
	Scene::update();
}

void Scene_Assignment13::drawBG() const
{
	ShaderManager::getInstance().useProgram("default");

	// X축
	glm::mat4 model{ 1.0f };
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, Vector3(2.0f));
	ShaderManager::getInstance().setMat4("default", "model", model);
	ShaderManager::getInstance().setVec3("default", "color", COLOR_RED);
	ShaderManager::getInstance().setFloat("default", "transparency", 1.0f);

	MeshManager::getInstance().drawLine();

	// Y축
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, Vector3(2.0f));
	ShaderManager::getInstance().setMat4("default", "model", model);
	ShaderManager::getInstance().setVec3("default", "color", COLOR_GREEN);

	MeshManager::getInstance().drawLine();

	// Z축
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, Vector3(2.0f));
	ShaderManager::getInstance().setMat4("default", "model", model);
	ShaderManager::getInstance().setVec3("default", "color", COLOR_BLUE);

	MeshManager::getInstance().drawLine();
}

void Scene_Assignment13::enter()
{
	Cube13* cube = new Cube13;
	createObject(cube, OBJECT_GROUP::POLYHENDRON);

	Pyramid13* pyramid = new Pyramid13;
	createObject(pyramid, OBJECT_GROUP::POLYHENDRON);
}

void Scene_Assignment13::exit()
{
	reset();
}
