#include "pch.h"
#include "Cube14.h"
#include "ShaderManager.h"
#include "MeshManager.h"

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
}

void Cube14::render() const
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
	ShaderManager::getInstance().setVec3("default", "color", COLOR_WHITE);
	ShaderManager::getInstance().setFloat("default", "transparency", 1.0f);

	MeshManager::getInstance().drawMesh("cube");
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
