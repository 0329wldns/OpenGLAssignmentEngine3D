#include "pch.h"
#include "cube15.h"
#include "ShaderManager.h"
#include "MeshManager.h"
#include "TimeManager.h"
#include "KeyManager.h"

Cube15::Cube15()
{
	setPos(0.0f, 0.0f, 0.0f);
	setScale(0.3f, 0.3f, 0.3f);
	faceData[0].color = COLOR_RED;
	faceData[1].color = COLOR_YELLOW;
	faceData[2].color = COLOR_GREEN;
	faceData[3].color = COLOR_BLUE;
	faceData[4].color = COLOR_GREEN + COLOR_BLUE;
	faceData[5].color = COLOR_RED + COLOR_BLUE;
}

Cube15::~Cube15()
{
	MeshManager::getInstance().resetMeshColors("cube");
}

void Cube15::update()
{
	processKeyInput();
	const float dt{ TimeManager::getInstance().getDeltaTime() };

	if (keyState[0])
	{
		for (int i = 0; i < 6; ++i) faceData[i].revolveDegree.y += 90.0f * dt;
	}
	if (keyState[1]) faceData[4].rotateDegree.z += 90.0f * dt;
	if (keyState[2]) faceData[0].rotateDegree.x -= 90.0f * dt;
	else faceData[0].rotateDegree.x += 90.0f * dt;
	if (keyState[3])
	{
		for (int i = 2; i < 4; ++i) faceData[i].rotateDegree.x += 90.0f * dt;
	}

	if (keyState[7])
	{
		for (int i = 0; i < 4; ++i) faceData[i].revolveDegree.y += 90.0f * dt;
	}
	if (keyState[8])
	{
		for (int i = 4; i < 6; ++i) faceData[i].revolveDegree.x += 90.0f * dt;
	}

	if (faceData[0].rotateDegree.x <= -180.0f) faceData[0].rotateDegree.x = -180.0f;
	else if (faceData[0].rotateDegree.x >= 0.0f) faceData[0].rotateDegree.x = 0.0f;
}

void Cube15::render() const
{
	ShaderManager::getInstance().useProgram("default");

	Vector3 myPos{ getPos() };
	Vector3 myScale{ getScale() };

	glm::mat4 model{ 1.0f };
	model = glm::translate(model, myPos);
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	ShaderManager::getInstance().setFloat("default", "transparency", 1.0f);

	MeshData cubeMesh{ MeshManager::getInstance().getMeshData("cube") };
	glBindVertexArray(cubeMesh.VAO);
	for (int i = 0; i < 6; ++i)
	{
		glm::mat4 defaultModel{ model };

		// 공전
		defaultModel = glm::rotate(defaultModel, glm::radians(faceData[i].revolveDegree.y), Vector3(0.0f, 1.0f, 0.0f));
		defaultModel = glm::rotate(defaultModel, glm::radians(faceData[i].revolveDegree.x), Vector3(1.0f, 0.0f, 0.0f));

		// 자전
		defaultModel = glm::translate(defaultModel, Vector3(0.0f, myScale.y, 0.0f));
		defaultModel = glm::rotate(defaultModel, glm::radians(faceData[i].rotateDegree.z), Vector3(0.0f, 0.0f, 1.0f));
		defaultModel = glm::translate(defaultModel, Vector3(0.0f, -myScale.y, 0.0f));

		if (i == 0)
		{
			defaultModel = glm::translate(defaultModel, Vector3(0.0f, myScale.y, myScale.z));
			defaultModel = glm::rotate(defaultModel, glm::radians(faceData[i].rotateDegree.x), Vector3(1.0f, 0.0f, 0.0f));
			defaultModel = glm::translate(defaultModel, Vector3(0.0f, -myScale.y, -myScale.z));
		}
		else defaultModel = glm::rotate(defaultModel, glm::radians(faceData[i].rotateDegree.x), Vector3(1.0f, 0.0f, 0.0f));
		
		defaultModel = glm::scale(defaultModel, myScale * 2.0f);
		ShaderManager::getInstance().setMat4("default", "model", defaultModel);
		ShaderManager::getInstance().setVec3("default", "color", faceData[i].color);
		glDrawArrays(GL_TRIANGLES, i * 6, 6);
	}
	glBindVertexArray(0);
}

void Cube15::randomizeColor()
{
	std::vector<glm::vec3> randomColors;
	randomColors.reserve(36);	// reserve - 용량을 늘려둬서 push_back시 재할당이 발생하지 않음

	for (int i = 0; i < 36; ++i)
	{
		glm::vec3 color{ realDist(gen), realDist(gen), realDist(gen) };
		randomColors.push_back(color);
	}
	MeshManager::getInstance().updateMeshColors("cube", randomColors);
}

void Cube15::processKeyInput()
{
	const KeyManager& keyManager{ KeyManager::getInstance() };

	if (keyManager.getKeyState(KEY::Y) == KEY_STATE::TAP) keyState[0] = !keyState[0];
	if (keyManager.getKeyState(KEY::T) == KEY_STATE::TAP) keyState[1] = !keyState[1];
	if (keyManager.getKeyState(KEY::F) == KEY_STATE::TAP) keyState[2] = !keyState[2];
	if (keyManager.getKeyState(KEY::S) == KEY_STATE::TAP) keyState[3] = !keyState[3];
	if (keyManager.getKeyState(KEY::B) == KEY_STATE::TAP) keyState[4] = !keyState[4];
	if (keyManager.getKeyState(KEY::NUM1) == KEY_STATE::TAP) keyState[5] = !keyState[5];
	if (keyManager.getKeyState(KEY::NUM2) == KEY_STATE::TAP) keyState[6] = !keyState[6];
	if (keyManager.getKeyState(KEY::NUM4) == KEY_STATE::TAP) keyState[7] = !keyState[7];
	if (keyManager.getKeyState(KEY::NUM5) == KEY_STATE::TAP) keyState[8] = !keyState[8];

	if (keyManager.getKeyState(KEY::R) == KEY_STATE::TAP)
	{
		for (int i = 0; i < 9; ++i) keyState[i] = false;

		for (int i = 0; i < 6; ++i)
		{
			faceData[i].revolveDegree = Vector3(0.0f, 0.0f, 0.0f);
			faceData[i].rotateDegree = Vector3(0.0f, 0.0f, 0.0f);
		}
	}
}
