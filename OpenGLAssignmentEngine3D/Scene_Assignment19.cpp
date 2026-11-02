#include "pch.h"
#include "Scene_Assignment19.h"
#include "KeyManager.h"
#include "EventFunc.h"
#include "MeshManager.h"
#include "ShaderManager.h"
#include "TimeManager.h"

Scene_Assignment19::Scene_Assignment19()
{
	cameraPos.y = 200.0f;
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

	if (KeyManager::getInstance().getKeyState(KEY::ESC) == KEY_STATE::TAP) changeScene(SCENE_TYPE::START);
}

void Scene_Assignment19::update()
{
	processKeyInput();
	float dt{ TimeManager::getInstance().getDeltaTime() };

	cameraPos += cameraMoveDir * 100.0f * dt;

	glm::mat4 view{
		glm::lookAt(glm::vec3(cameraPos.x, cameraPos.y, 600.0f + cameraPos.z)
		, glm::vec3(0.0f, 0.0f, 0.0f)
		, glm::vec3(0.0f, 1.0f, 0.0f))
	};
	ShaderManager::getInstance().useProgram("default");
	ShaderManager::getInstance().setMat4("default", "view", view);

	cout << cameraPos.x << " " << cameraPos.y << " " << cameraPos.z << endl;
	
	Scene::update();
}

void Scene_Assignment19::drawBG() const
{
	ShaderManager::getInstance().useProgram("default");

	glm::mat4 model{ 1.0f };
	model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, Vector3(SCREEN_WIDTH, SCREEN_WIDTH, 1.0f));

	ShaderManager::getInstance().setMat4("default", "model", model);
	ShaderManager::getInstance().setVec3("default", "color", COLOR_GRAY);

	MeshManager::getInstance().drawQuad();
}

void Scene_Assignment19::drawUI() const
{
}

void Scene_Assignment19::enter()
{
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
}
