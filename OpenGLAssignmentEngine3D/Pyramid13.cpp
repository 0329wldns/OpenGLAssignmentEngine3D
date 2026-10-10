#include "pch.h"
#include "Pyramid13.h"
#include "KeyManager.h"
#include "ShaderManager.h"
#include "MeshManager.h"

Pyramid13::Pyramid13()
{
	setPos(0.0f, 0.0f, 0.0f);
	setScale(0.3f, 0.3f, 0.3f);
	for (int i = 0; i < 5; ++i) face[i].color = Color{ realDist(gen), realDist(gen), realDist(gen) };
}

void Pyramid13::update()
{
	for (int i = 0; i < 4; ++i)
	{
		if (KeyManager::getInstance().getKeyState((KEY)(i + 6)) == KEY_STATE::TAP)
		{
			face[i + 1].isVisible = !face[i + 1].isVisible;
			face[0].isVisible = true;
		}
	}

	if (KeyManager::getInstance().getKeyState(KEY::T) == KEY_STATE::TAP)
	{
		for (int i = 0; i < 4; ++i)
			face[i + 1].isVisible = false;

		face[intDist(gen) % 4 + 1].isVisible = true;
		face[0].isVisible = true;
	}
}

void Pyramid13::render() const
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

	MeshData pyramidMesh{ MeshManager::getInstance().getMeshData("pyramid") };
	glBindVertexArray(pyramidMesh.VAO);
	ShaderManager::getInstance().setVec3("default", "color", face[0].color);
	if (face[0].isVisible) glDrawArrays(GL_TRIANGLES, 0, 6);
	for (int i = 0; i < 4; ++i)
	{
		if (!face[i + 1].isVisible) continue;
		ShaderManager::getInstance().setVec3("default", "color", face[i + 1].color);
		glDrawArrays(GL_TRIANGLES, 6 + i * 3, 3);
	}
	glBindVertexArray(0);
}
