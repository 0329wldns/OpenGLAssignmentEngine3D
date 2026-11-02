#include "pch.h"
#include "Scene_Assignment19.h"
#include "KeyManager.h"
#include "EventFunc.h"
#include "MeshManager.h"
#include "ShaderManager.h"
#include "TimeManager.h"
#include "Tank.h"

Scene_Assignment19::Scene_Assignment19()
{
	cameraPos.y = 300.0f;
	cameraPos.z = 600.0f;
}

void Scene_Assignment19::processKeyInput()
{
	const KeyManager& keyManager{ KeyManager::getInstance() };

	if (keyManager.getKeyState(KEY::UP) == KEY_STATE::TAP) cameraMoveDir.z -= 1.0f;
	else if (keyManager.getKeyState(KEY::UP) == KEY_STATE::AWAY) cameraMoveDir.z += 1.0f;
	if (keyManager.getKeyState(KEY::DOWN) == KEY_STATE::TAP) cameraMoveDir.z += 1.0f;
	else if (keyManager.getKeyState(KEY::DOWN) == KEY_STATE::AWAY) cameraMoveDir.z -= 1.0f;
	if (keyManager.getKeyState(KEY::LEFT) == KEY_STATE::TAP) cameraMoveDir.x -= 1.0f;
	else if (keyManager.getKeyState(KEY::LEFT) == KEY_STATE::AWAY) cameraMoveDir.x += 1.0f;
	if (keyManager.getKeyState(KEY::RIGHT) == KEY_STATE::TAP) cameraMoveDir.x += 1.0f;
	else if (keyManager.getKeyState(KEY::RIGHT) == KEY_STATE::AWAY) cameraMoveDir.x -= 1.0f;
	if (keyManager.getKeyState(KEY::MINUS) == KEY_STATE::TAP) cameraMoveDir.y -= 1.0f;
	else if (keyManager.getKeyState(KEY::MINUS) == KEY_STATE::AWAY) cameraMoveDir.y += 1.0f;
	if (keyManager.getKeyState(KEY::EQUAL) == KEY_STATE::TAP) cameraMoveDir.y += 1.0f;
	else if (keyManager.getKeyState(KEY::EQUAL) == KEY_STATE::AWAY) cameraMoveDir.y -= 1.0f;

	if (keyManager.getKeyState(KEY::Y) == KEY_STATE::TAP) cameraRotate.isActive = !cameraRotate.isActive;
	if (keyManager.getKeyState(KEY::R) == KEY_STATE::TAP) cameraOrbit.isActive = !cameraOrbit.isActive;

	if (KeyManager::getInstance().getKeyState(KEY::ESC) == KEY_STATE::TAP) changeScene(SCENE_TYPE::START);
}

void Scene_Assignment19::update()
{
	float dt{ TimeManager::getInstance().getDeltaTime() };
	float cameraDist{ glm::length(Vector2(0.0f) - Vector2(cameraPos.x, cameraPos.z)) };

	cameraRotate.update();
	cameraOrbit.update();

	cemeraAt = cameraRotate.getRotationMatrix() * glm::vec4(0.0f, 0.0f, -200.0f, 1.0f);
	cameraPos = cameraOrbit.getRotationMatrix() * glm::vec4(0.0f, cameraPos.y, cameraDist, 1.0f);

	cameraPos += cameraMoveDir * 300.0f * dt;
	cemeraAt += cameraPos;

	glm::mat4 view{
		glm::lookAt(Vector3(cameraPos.x, cameraPos.y, cameraPos.z)
		//, Vector3(0.0f, cemeraAt.y, 0.0f)
		, Vector3(cemeraAt.x, cemeraAt.y, cemeraAt.z - 200.0f)
		, Vector3(0.0f, 1.0f, 0.0f))
	};
	ShaderManager::getInstance().useProgram("default");
	ShaderManager::getInstance().setMat4("default", "view", view);
	
	Scene::update();
}

void Scene_Assignment19::drawBG() const
{
	ShaderManager::getInstance().useProgram("default");

	glm::mat4 model{ 1.0f };
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, Vector3(1200.0f, 1200.0f, 1.0f));

	ShaderManager::getInstance().setMat4("default", "model", model);
	ShaderManager::getInstance().setVec3("default", "color", COLOR_GREEN);
	MeshManager::getInstance().drawQuad();
}

void Scene_Assignment19::enter()
{
	Tank* tank{ new Tank() };
	createObject(tank, OBJECT_GROUP::POLYHENDRON);

	ShaderManager::getInstance().setBool("default", "projectionMode", true);
}

void Scene_Assignment19::exit()
{
	reset();

	glm::mat4 view{
		glm::lookAt(glm::vec3(0.0f, 0.0f, 600.0f)
		, glm::vec3(0.0f, 0.0f, 0.0f)
		, glm::vec3(0.0f, 1.0f, 0.0f))
	};
	ShaderManager::getInstance().useProgram("default");
	ShaderManager::getInstance().setMat4("default", "view", view);

	ShaderManager::getInstance().setBool("default", "projectionMode", false);
}
