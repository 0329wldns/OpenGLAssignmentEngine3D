#include "pch.h"
#include "Pyramid15.h"
#include "ShaderManager.h"
#include "MeshManager.h"
#include "Scene_Assignment15.h"
#include "SceneManager.h"
#include "EventFunc.h"
#include "TimeManager.h"
#include "KeyManager.h"

Pyramid15::Pyramid15()
{
	setPos(0.0f, 0.0f, 0.0f);
	setScale(0.3f, 0.3f, 0.3f);

	faceData[0].color = COLOR_RED;
	faceData[1].color = COLOR_YELLOW;
	faceData[2].color = COLOR_GREEN;
	faceData[3].color = COLOR_BLUE;
	faceData[4].color = COLOR_GREEN + COLOR_BLUE;

	for (int i = 0; i < 5; ++i) faceData[i].scale = Vector3(0.3f, 0.3f, 0.3f);
	initRotateData();
}

Pyramid15::~Pyramid15()
{
}

void Pyramid15::update()
{
	const float dt{ TimeManager::getInstance().getDeltaTime() };

	processKeyInput();

	for (int i = 0; i < 5; ++i) faceData[i].update();

	if (KeyManager::getInstance().getKeyState(KEY::R) == KEY_STATE::TAP)
	{
		deleteObject(this);
		Pyramid15* pyramid{ new Pyramid15 };
		createObject(pyramid, OBJECT_GROUP::POLYHENDRON);
	}
}

void Pyramid15::render() const
{
	if (!static_cast<Scene_Assignment15*>(SceneManager::getInstance().getCurScene())->getPFlag()) return;
	ShaderManager::getInstance().useProgram("default");

	Vector3 myPos{ getPos() };
	Vector3 myScale{ getScale() };

	glm::mat4 defaultModel{ 1.0f };
	defaultModel = glm::translate(defaultModel, myPos);
	defaultModel = glm::rotate(defaultModel, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	defaultModel = glm::rotate(defaultModel, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	defaultModel = glm::scale(defaultModel, myScale * 2.0f);
	ShaderManager::getInstance().setMat4("default", "model", defaultModel);
	ShaderManager::getInstance().setFloat("default", "transparency", 1.0f);

	MeshData pyramidMesh{ MeshManager::getInstance().getMeshData("pyramid") };
	glBindVertexArray(pyramidMesh.VAO);
	for (int i = 0; i < 5; ++i)
	{
		glm::mat4 model{ defaultModel };
		Vector3 myScale{ faceData[i].scale };

		const vector<RotateData>& myRotateData{ faceData[i].rotateData };
		for (int j = 0; j < myRotateData.size(); ++j)
		{
			const RotateData& data{ myRotateData[j] };

			model = glm::translate(model, data.offset);
			model = glm::rotate(model, glm::radians(data.degree), data.axis);
			model = glm::translate(model, -data.offset);
		}

		model = glm::scale(model, myScale * 2.0f);
		ShaderManager::getInstance().setMat4("default", "model", model);
		ShaderManager::getInstance().setVec3("default", "color", faceData[i].color);
		if (i == 0) glDrawArrays(GL_TRIANGLES, 0, 6);
		else glDrawArrays(GL_TRIANGLES, 6 + (i - 1) * 3, 3);
	}
	glBindVertexArray(0);
}

void Pyramid15::initRotateData()
{
	RotateData y;
	y.axis = Vector3(0.0f, 1.0f, 0.0f);
	y.rotateType = 0;
	y.id = 'y';
	for (int i = 0; i < 5; ++i) faceData[i].addRotateData(y);

	RotateData num6;
	num6.axis = Vector3(1.0f, 0.0f, 0.0f);
	num6.offset = Vector3(0.0f, -0.3f, 0.3f);
	num6.isExpire = true;
	num6.targetDegree = 233.0f;
	num6.rotateType = 1;
	num6.id = '6';
	faceData[1].addRotateData(num6);

	num6.offset = Vector3(0.0f, -0.3f, -0.3f);
	faceData[2].addRotateData(num6);
}

void Pyramid15::processKeyInput()
{
	const KeyManager& keyManager{ KeyManager::getInstance() };

	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < faceData[i].rotateData.size(); ++j)
		{
			RotateData& data{ faceData[i].rotateData[j] };
			if (data.id == 'y' && keyManager.getKeyState(KEY::Y) == KEY_STATE::TAP)
			{
				data.isActive = !data.isActive;
				continue;
			}
			if (data.id == '6' && keyManager.getKeyState(KEY::NUM6) == KEY_STATE::TAP)
			{
				data.isActive = !data.isActive;
				continue;
			}
		}
	}
}
