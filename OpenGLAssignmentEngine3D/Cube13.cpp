#include "pch.h"
#include "Cube13.h"
#include "ShaderManager.h"
#include "MeshManager.h"
#include "TimeManager.h"

Cube13::Cube13()
{
	setPos(0.0f, 0.0f, 0.0f);
	setScale(0.3f, 0.3f, 0.3f);
	for (int i = 0; i < 6; ++i) color[i] = Color{ realDist(gen), realDist(gen), realDist(gen) };
}

void Cube13::update()
{
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

	for (int i = 0; i < 6; ++i)
	{
		glBindVertexArray(cubeMesh.VAO);
		ShaderManager::getInstance().setVec3("default", "color", color[i]);
		glDrawArrays(GL_TRIANGLES, i * 6, 6);
		glBindVertexArray(0);
	}
}