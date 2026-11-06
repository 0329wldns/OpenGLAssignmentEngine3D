#include "pch.h"
#include "Scene_Assignment23.h"
#include "KeyManager.h"
#include "EventFunc.h"
#include "MeshManager.h"
#include "ShaderManager.h"
#include "TimeManager.h"
#include "Robot.h"

Scene_Assignment23::Scene_Assignment23()
	: openTrigger(true)
{
	for (int i = 0; i < 6; ++i)
	{
		faceData[i].color = glm::vec3(realDist(gen), realDist(gen), realDist(gen));
		faceData[i].scale = Vector3(1200.0f, 800.0f, 1200.0f);
	}
}

void Scene_Assignment23::processKeyInput()
{
	if (KeyManager::getInstance().getKeyState(KEY::O) == KEY_STATE::TAP) openTrigger = true;

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

	if (KeyManager::getInstance().getKeyState(KEY::ESC) == KEY_STATE::TAP) changeScene(SCENE_TYPE::START);
}

void Scene_Assignment23::update()
{
	Scene::update();

	float dt{ TimeManager::getInstance().getDeltaTime() };

	if (openTrigger)
	{
		faceData[0].scale -= Vector3(1200.0f, 800.0f, 1200.0f) * 2.0f * dt;
		if (glm::any(glm::lessThanEqual(faceData[0].scale, Vector3(0.0f, 0.0f, 0.0f))))
		{
			faceData[0].scale = Vector3(0.0f, 0.0f, 0.0f);
			openTrigger = false;
		}
	}

	cameraPos += cameraMoveDir * 300.0f * dt;

	glm::mat4 view{
		glm::lookAt(cameraPos
		, glm::vec3(0.0f, 400.0f, 0.0f)
		, glm::vec3(0.0f, 1.0f, 0.0f))
	};
	ShaderManager::getInstance().useProgram("default");
	ShaderManager::getInstance().setMat4("default", "view", view);
}

void Scene_Assignment23::drawBG() const
{
	ShaderManager::getInstance().useProgram("default");

	MeshData cubeMesh{ MeshManager::getInstance().getMeshData("cube") };
	glBindVertexArray(cubeMesh.VAO);

	glm::mat4 defaultModel{ 1.0f };
	defaultModel = glm::translate(defaultModel, Vector3(0.0f, 400.0f, 0.0f));

	for (int i = 0; i < 6; ++i)
	{
		glm::mat4 model{ defaultModel };
		model = glm::scale(model, faceData[i].scale);

		ShaderManager::getInstance().setMat4("default", "model", model);
		ShaderManager::getInstance().setVec3("default", "color", faceData[i].color);
		glDrawArrays(GL_TRIANGLES, i * 6, 6);
	}
	glBindVertexArray(0);
}

void Scene_Assignment23::enter()
{
	Robot* robot{ new Robot };
	createObject(robot, OBJECT_GROUP::POLYHENDRON);

	glm::mat4 view{
		glm::lookAt(cameraPos
		, glm::vec3(0.0f, 400.0f, 0.0f)
		, glm::vec3(0.0f, 1.0f, 0.0f))
	};
	ShaderManager::getInstance().useProgram("default");
	ShaderManager::getInstance().setMat4("default", "view", view);

	ShaderManager::getInstance().setBool("default", "projectionMode", true);

	glm::mat4 perspective{ glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 4800.0f) };
	ShaderManager::getInstance().useProgram("default");
	ShaderManager::getInstance().setMat4("default", "perspective", perspective);
}

void Scene_Assignment23::exit()
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

	glm::mat4 perspective{ glm::perspective(glm::radians(90.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 1200.0f) };
	ShaderManager::getInstance().useProgram("default");
	ShaderManager::getInstance().setMat4("default", "perspective", perspective);
}
