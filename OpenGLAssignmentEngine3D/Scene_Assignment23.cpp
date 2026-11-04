#include "pch.h"
#include "Scene_Assignment23.h"
#include "KeyManager.h"
#include "EventFunc.h"
#include "MeshManager.h"
#include "ShaderManager.h"
#include "TimeManager.h"

Scene_Assignment23::Scene_Assignment23()
	: openTrigger(false)
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
}

void Scene_Assignment23::drawBG() const
{
	ShaderManager::getInstance().useProgram("default");

	MeshData cubeMesh{ MeshManager::getInstance().getMeshData("cube") };
	glBindVertexArray(cubeMesh.VAO);
	for (int i = 0; i < 6; ++i)
	{
		glm::mat4 model{ 1.0f };
		model = glm::scale(model, faceData[i].scale);

		ShaderManager::getInstance().setMat4("default", "model", model);
		ShaderManager::getInstance().setVec3("default", "color", faceData[i].color);
		glDrawArrays(GL_TRIANGLES, i * 6, 6);
	}
	glBindVertexArray(0);
}

void Scene_Assignment23::enter()
{
	glm::mat4 view{
		glm::lookAt(glm::vec3(0.0f, 500.0f, 2000.0f)
		, glm::vec3(0.0f, 0.0f, 0.0f)
		, glm::vec3(0.0f, 1.0f, 0.0f))
	};
	ShaderManager::getInstance().useProgram("default");
	ShaderManager::getInstance().setMat4("default", "view", view);

	ShaderManager::getInstance().setBool("default", "projectionMode", true);

	glm::mat4 perspective{ glm::perspective(glm::radians(45.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 4800.0f) };
	ShaderManager::getInstance().useProgram("default");
	ShaderManager::getInstance().setMat4("default", "perspective", perspective);

	// glCullFace(GL_FRONT);
	// glEnable(GL_CULL_FACE);
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
