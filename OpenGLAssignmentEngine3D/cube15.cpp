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

	for (int i = 0; i < 6; ++i) faceData[i].scale = Vector3(0.3f, 0.3f, 0.3f);
}

Cube15::~Cube15()
{
	MeshManager::getInstance().resetMeshColors("cube");
}

void Cube15::update()
{
	processKeyInput();
	const float dt{ TimeManager::getInstance().getDeltaTime() };

	for (int i = 0; i < 6; ++i)
	{
		vector<RotateData>& myRotateData{ faceData[i].rotateData };
		for (int j = 0; j < myRotateData.size(); ++j)
		{
			RotateData& data{ myRotateData[j] };
			if (!data.isActive) continue;
			bool isRoop{ data.isRoop };
			float& degree{ data.degree };
			float targetDegree{ data.targetDegree };
			float speed{ data.speed };

			if (targetDegree >= 0)
			{
				degree += speed * dt;
				if (degree > targetDegree)
				{
					if (isRoop) degree -= targetDegree;
					else degree = targetDegree;
				}
			}
			else 
			{
				degree -= speed * dt;
				if (degree < targetDegree)
				{
					if (isRoop) degree += targetDegree;
					else degree = targetDegree;
				}
			}
			
		}
	}

	bool isLessThanZero{ glm::any(glm::lessThanEqual(faceData[1].scale, Vector3(0.0f, 0.0f, 0.0f))) };
	bool isGreaterThanOrg{ glm::all(glm::greaterThanEqual(faceData[1].scale, getScale())) };
	if (isLessThanZero) faceData[1].scale = Vector3(0.0f, 0.0f, 0.3f);
	else if (isGreaterThanOrg) faceData[1].scale = getScale();
}

void Cube15::render() const
{
	ShaderManager::getInstance().useProgram("default");

	Vector3 myPos{ getPos() };

	glm::mat4 defaultModel{ 1.0f };
	defaultModel = glm::translate(defaultModel, myPos);
	defaultModel = glm::rotate(defaultModel, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	defaultModel = glm::rotate(defaultModel, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	ShaderManager::getInstance().setFloat("default", "transparency", 1.0f);

	MeshData cubeMesh{ MeshManager::getInstance().getMeshData("cube") };
	glBindVertexArray(cubeMesh.VAO);
	for (int i = 0; i < 6; ++i)
	{
		glm::mat4 model{ defaultModel };
		Vector3 myScale{ faceData[i].scale };

		const vector<RotateData>& myRotateData{ faceData[i].rotateData };
		for (size_t j = 0; j < myRotateData.size(); ++j)
		{
			const RotateData& data{ myRotateData[(int)j] };
			
			model = glm::translate(model, data.offset);
			model = glm::rotate(model, glm::radians(data.degree), data.axis);
			model = glm::translate(model, -data.offset);
		}
		
		model = glm::scale(model, myScale * 2.0f);
		ShaderManager::getInstance().setMat4("default", "model", model);
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

	if (keyManager.getKeyState(KEY::Y) == KEY_STATE::TAP)
	{
		RotateData newRotate;
		newRotate.axis = Vector3(0.0f, 1.0f, 0.0f);
		newRotate.rotateType = 0;
		for (int i = 0; i < 6; ++i)
		{
			faceData[i].rotateData.push_back(newRotate);
			sort(faceData[i].rotateData.begin(), faceData[i].rotateData.end(), [](const RotateData& a, const RotateData& b) {
				return a.rotateType < b.rotateType; });
		}
	}
	if (keyManager.getKeyState(KEY::T) == KEY_STATE::TAP)
	{
		RotateData newRotate;
		newRotate.offset = Vector3(0.0f, 0.3, 0.0f);
		newRotate.axis = Vector3(0.0f, 0.0f, 1.0f);
		newRotate.rotateType = 2;
		faceData[4].rotateData.push_back(newRotate);
		sort(faceData[4].rotateData.begin(), faceData[4].rotateData.end(), [](const RotateData& a, const RotateData& b) {
			return a.rotateType < b.rotateType; });
	}
	if (keyManager.getKeyState(KEY::F) == KEY_STATE::TAP)
	{
		RotateData newRotate;
		newRotate.targetDegree = -180.0f;
		newRotate.isRoop = false;
		newRotate.offset = Vector3(0.0f, 0.3, 0.3f);
		newRotate.axis = Vector3(1.0f, 0.0f, 0.0f);
		newRotate.rotateType = 1;
		
		faceData[0].rotateData.push_back(newRotate);
		sort(faceData[0].rotateData.begin(), faceData[0].rotateData.end(), [](const RotateData& a, const RotateData& b) {
			return a.rotateType < b.rotateType; });
	}
	if (keyManager.getKeyState(KEY::S) == KEY_STATE::TAP) keyState[3] = !keyState[3];
	if (keyManager.getKeyState(KEY::B) == KEY_STATE::TAP) keyState[4] = !keyState[4];
	if (keyManager.getKeyState(KEY::NUM1) == KEY_STATE::TAP) keyState[5] = !keyState[5];
	if (keyManager.getKeyState(KEY::NUM2) == KEY_STATE::TAP) keyState[6] = !keyState[6];
	if (keyManager.getKeyState(KEY::NUM4) == KEY_STATE::TAP) keyState[7] = !keyState[7];
	if (keyManager.getKeyState(KEY::NUM5) == KEY_STATE::TAP) keyState[8] = !keyState[8];

	if (keyManager.getKeyState(KEY::R) == KEY_STATE::TAP)
	{
		for (int i = 0; i < 9; ++i) keyState[i] = false;

		for (int i = 0; i < 6; ++i) faceData[i].rotateData.clear();
	}
}
