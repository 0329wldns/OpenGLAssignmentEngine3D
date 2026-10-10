#include "pch.h"
#include "Cube13.h"
#include "ShaderManager.h"
#include "MeshManager.h"
#include "TimeManager.h"
#include "KeyManager.h"

Cube13::Cube13()
{
	setPos(0.0f, 0.0f, 0.0f);
	setScale(0.3f, 0.3f, 0.3f);
	for (int i = 0; i < 6; ++i) 
		face[i].color = Color{ realDist(gen), realDist(gen), realDist(gen) };
}

void Cube13::update()
{
	for (int i = 0; i < 6; ++i)
	{
		if (KeyManager::getInstance().getKeyState((KEY)i) == KEY_STATE::TAP)
			face[i].isVisible = !face[i].isVisible;
	}

	if (KeyManager::getInstance().getKeyState(KEY::R) == KEY_STATE::TAP)
	{
		for (int i = 0; i < 6; ++i)
		{
			face[i].color = Color{ realDist(gen), realDist(gen), realDist(gen) };
			face[i].isVisible = false;
		}
			
	}

	if (KeyManager::getInstance().getKeyState(KEY::C) == KEY_STATE::TAP)
	{
		for (int i = 0; i < 6; ++i)
			face[i].isVisible = false;

		int firstFace{ intDist(gen) % 6 };
		int secondFace{ intDist(gen) % 6 };
		while (firstFace == secondFace)
			secondFace = intDist(gen) % 6;

		face[firstFace].isVisible = true;
		face[secondFace].isVisible = true;
	}
}

void Cube13::render() const
{
	ShaderManager::getInstance().useProgram("default");

	Vector3 myPos{ getPos() };
	Vector3 myScale{ getScale() };

	glm::mat4 model{ 1.0f };
	model = glm::translate(model, myPos);
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, myScale * 2.0f);
	ShaderManager::getInstance().setMat4("default", "model", model);
	ShaderManager::getInstance().setFloat("default", "transparency", 1.0f);

	MeshData cubeMesh{ MeshManager::getInstance().getMeshData("cube") };
	glBindVertexArray(cubeMesh.VAO);
	for (int i = 0; i < 6; ++i)
	{
		if (!face[i].isVisible) continue;
		ShaderManager::getInstance().setVec3("default", "color", face[i].color);
		glDrawArrays(GL_TRIANGLES, i * 6, 6);
	}
	glBindVertexArray(0);
}