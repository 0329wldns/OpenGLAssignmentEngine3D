#include "pch.h"
#include "cube15.h"
#include "ShaderManager.h"
#include "MeshManager.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "EventFunc.h"
#include "Scene_Assignment15.h"
#include "SceneManager.h"

Cube15::Cube15()
{
	setPos(0.0f, 0.0f, 0.0f);
	setScale(200.0f, 200.0f, 200.0f);

	faceData[0].color = COLOR_RED;
	faceData[1].color = COLOR_YELLOW;
	faceData[2].color = COLOR_GREEN;
	faceData[3].color = COLOR_BLUE;
	faceData[4].color = COLOR_GREEN + COLOR_BLUE;
	faceData[5].color = COLOR_RED + COLOR_BLUE;

	for (int i = 0; i < 6; ++i) faceData[i].scale = getScale();
	initRotateData();
}

Cube15::~Cube15()
{
	MeshManager::getInstance().resetMeshColors("cube");
}

void Cube15::update()
{
	processKeyInput();
	const float dt{ TimeManager::getInstance().getDeltaTime() };

	for (int i = 0; i < 6; ++i) faceData[i].update();

	if (bFlag) faceData[1].scale -= Vector3(300.0f, 300.0f, 300.0f) * dt;
	else faceData[1].scale += Vector3(300.0f, 300.0f, 0.0f) * dt;

	bool isLessThanZero{ glm::any(glm::lessThanEqual(faceData[1].scale, Vector3(0.0f, 0.0f, 0.0f))) };
	bool isGreaterThanOrg{ glm::all(glm::greaterThanEqual(faceData[1].scale, getScale())) };
	if (isLessThanZero) faceData[1].scale = Vector3(0.0f, 0.0f, 0.3f);
	else if (isGreaterThanOrg) faceData[1].scale = getScale();
}

void Cube15::render() const
{
	if (static_cast<Scene_Assignment15*>(SceneManager::getInstance().getCurScene())->getPFlag()) return;
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

		for (auto& data : faceData[i].rotateData) model *= data.getRotationMatrix();

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

	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < faceData[i].rotateData.size(); ++j)
		{
			RotateData& data{ faceData[i].rotateData[j] };
			if (data.id == 'y' && keyManager.getKeyState(KEY::Y) == KEY_STATE::TAP)
			{
				data.isActive = !data.isActive;
				continue;
			}
			if (data.id == 't' && keyManager.getKeyState(KEY::T) == KEY_STATE::TAP)
			{
				data.isActive = !data.isActive;
				continue;
			}
			if (data.id == 'f' && keyManager.getKeyState(KEY::F) == KEY_STATE::TAP)
			{
				data.isActive = !data.isActive;
				continue;
			}
			if (data.id == 's' && keyManager.getKeyState(KEY::S) == KEY_STATE::TAP)
			{
				data.isActive = !data.isActive;
				continue;
			}
			if (data.id == '4' && keyManager.getKeyState(KEY::NUM4) == KEY_STATE::TAP)
			{
				data.isActive = !data.isActive;
				continue;
			}
			if (data.id == '5' && keyManager.getKeyState(KEY::NUM5) == KEY_STATE::TAP)
			{
				data.isActive = !data.isActive;
				continue;
			}
		}
	}

	if (keyManager.getKeyState(KEY::NUM1) == KEY_STATE::TAP)
	{
		int face1{ intDist(gen) % 2 }; // 0 or 1
		int face2{ intDist(gen) % 2 + 2 };	// 2 or 3

		RotateData rot;
		if (face1 == 0) 
		{
			if (face2 == 2) rot.offset = Vector3(-0.3f, 0.0f, 0.3f);
			else if (face2 == 3) rot.offset = Vector3(0.3f, 0.0f, 0.3f);
		}
		else if (face1 == 1)
		{
			if (face2 == 2) rot.offset = Vector3(-0.3f, 0.0f, -0.3f);
			else if (face2 == 3) rot.offset = Vector3(0.3f, 0.0f, -0.3f);
		}

		rot.axis = Vector3(0.0f, 1.0f, 0.0f);
		rot.speed = 180.0f;
		rot.rotateType = 1;
		rot.isActive = true;
		rot.isExpire = true;
		rot.id = '1';

		faceData[face1].addRotateData(rot);
		faceData[face2].addRotateData(rot);
	}

	if (keyManager.getKeyState(KEY::NUM2) == KEY_STATE::TAP)
	{
		int face1{ intDist(gen) % 2 }; // 0 or 1
		int face2{ intDist(gen) % 2 + 2 };	// 2 or 3

		RotateData rot;
		rot.id = '2';
		rot.axis = Vector3(0.0f, 1.0f, 0.0f);
		
		rot.isExpire = true;
		rot.rotateType = 1;
		rot.isActive = true;

		if ((face1 + face2) % 2)
		{
			rot.targetDegree = 90.0f;
			rot.speed = 180.0f;
		}
		else
		{
			rot.targetDegree = -90.0f;
			rot.speed = -180.0f;
		}

		faceData[face1].addRotateData(rot);
		rot.targetDegree = -rot.targetDegree;
		rot.speed = -rot.speed;
		faceData[face2].addRotateData(rot);
	}

	if (keyManager.getKeyState(KEY::B) == KEY_STATE::TAP) bFlag = !bFlag;

	if (keyManager.getKeyState(KEY::R) == KEY_STATE::TAP)
	{
		deleteObject(this);
		Cube15* cube{ new Cube15 };
		createObject(cube, OBJECT_GROUP::POLYHENDRON);
	}
}

void Cube15::initRotateData()
{
	RotateData y;
	y.axis = Vector3(0.0f, 1.0f, 0.0f);
	y.rotateType = 0;
	y.id = 'y';
	for (int i = 0; i < 6; ++i) faceData[i].addRotateData(y);

	RotateData t;
	t.offset = Vector3(0.0f, 200.0f, 0.0f);
	t.axis = Vector3(0.0f, 0.0f, 1.0f);
	t.rotateType = 2;
	t.id = 't';
	faceData[4].addRotateData(t);

	RotateData f;
	f.speed = -90.0f;
	f.targetDegree = -180.0f;
	f.offset = Vector3(0.0f, 0.3f, 0.3f);
	f.axis = Vector3(1.0f, 0.0f, 0.0f);
	f.rotateType = 2;
	f.id = 'f';
	f.isReverse = true;
	f.isStop = true;
	faceData[0].addRotateData(f);

	RotateData s;
	s.axis = Vector3(1.0f, 0.0f, 0.0f);
	s.rotateType = 2;
	s.id = 's';
	for (int i = 2; i < 4; ++i) faceData[i].addRotateData(s);

	RotateData num4;
	num4.axis = Vector3(0.0f, 1.0f, 0.0f);
	num4.rotateType = 0;
	num4.id = '4';
	for (int i = 0; i < 4; ++i) faceData[i].addRotateData(num4);

	RotateData num5;
	num5.axis = Vector3(1.0f, 0.0f, 0.0f);
	num5.rotateType = 1;
	num5.id = '5';
	for (int i = 4; i < 6; ++i) faceData[i].addRotateData(num5);
}