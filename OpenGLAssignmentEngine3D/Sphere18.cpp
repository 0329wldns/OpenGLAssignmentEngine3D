#include "pch.h"
#include "Sphere18.h"
#include "ShaderManager.h"
#include "MeshManager.h"
#include "TimeManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "Scene_Assignment18.h"

Sphere18::Sphere18(Color _color, Vector3 _scale, float _orbitRadius, float _orbitTiltDeg, bool _useOrbitRotate)
	: color(_color)
	, orbitRadius(_orbitRadius)
	, orbitTiltDeg(_orbitTiltDeg)
	, useOrbitRotate(_useOrbitRotate)
{
	setScale(_scale);
	setPos(orbitRadius, 0.0f, 0.0f);
	orgOrbitRadius = orbitRadius;

	orbit.axis = Vector3(0.0f, 1.0f, 0.0f);
	orbit.isActive = true;
	orbit.speed = 45.0f + realDist(gen) * 135.0f;	// 45 ~ 180

	if (useOrbitRotate)
	{
		orbitRotate.axis = Vector3(0.0f, 0.0f, 1.0f);
		orbitRotate.isActive = false;
		orbitRotate.speed = 90.0f;
	}
}

Sphere18::~Sphere18()
{
}

void Sphere18::update()
{
	orbit.update();
	Vector3 myPos{ getPos() };
	float  dt{ TimeManager::getInstance().getDeltaTime() };

	if (center != nullptr && center == this)
	{
		if (KeyManager::getInstance().getKeyState(KEY::W) == KEY_STATE::TAP) moveDir.y += 1.0f;
		else if (KeyManager::getInstance().getKeyState(KEY::W) == KEY_STATE::AWAY) moveDir.y -= 1.0f;
		if (KeyManager::getInstance().getKeyState(KEY::A) == KEY_STATE::TAP) moveDir.x -= 1.0f;
		else if (KeyManager::getInstance().getKeyState(KEY::A) == KEY_STATE::AWAY) moveDir.x += 1.0f;
		if (KeyManager::getInstance().getKeyState(KEY::D) == KEY_STATE::TAP) moveDir.x += 1.0f;
		else if (KeyManager::getInstance().getKeyState(KEY::D) == KEY_STATE::AWAY) moveDir.x -= 1.0f;
		if (KeyManager::getInstance().getKeyState(KEY::S) == KEY_STATE::TAP) moveDir.y -= 1.0f;
		else if (KeyManager::getInstance().getKeyState(KEY::S) == KEY_STATE::AWAY) moveDir.y += 1.0f;

		if (KeyManager::getInstance().getKeyState(KEY::MINUS) == KEY_STATE::TAP) moveDir.z -= 1.0f;
		else if (KeyManager::getInstance().getKeyState(KEY::MINUS) == KEY_STATE::AWAY) moveDir.z += 1.0f;
		if (KeyManager::getInstance().getKeyState(KEY::EQUAL) == KEY_STATE::TAP) moveDir.z += 1.0f;
		else if (KeyManager::getInstance().getKeyState(KEY::EQUAL) == KEY_STATE::AWAY) moveDir.z -= 1.0f;

		if (KeyManager::getInstance().getKeyState(KEY::NUM1) == KEY_STATE::TAP) orbitRadiusDelta += 2.0f;
		else if (KeyManager::getInstance().getKeyState(KEY::NUM1) == KEY_STATE::AWAY) orbitRadiusDelta -= 2.0f;

		myPos += moveDir * moveSpeed * dt;
		orbit.offset = myPos;
	}
	
	glm::mat4 rotation{ orbit.getRotationMatrix() };
	myPos = rotation * glm::vec4(myPos, 1.0f);

	if (useOrbitRotate)
	{
		if (KeyManager::getInstance().getKeyState(KEY::NUM3) == KEY_STATE::TAP)
		{
			orbitRotate.isActive = !orbitRotate.isActive;
		}
		orbitRotate.update();

		myPos = orbitRotate.getRotationMatrix() * glm::vec4(myPos, 1.0f);
	}

	myPos -= orbit.offset;
	myPos = glm::rotate(glm::mat4(1.0f), glm::radians(orbitTiltDeg), Vector3(0.0f, 0.0f, 1.0f)) * glm::vec4(myPos, 1.0f);
	myPos += orbit.offset;

	for (auto& m : moon)
	{
		m->orbitRadius += orbitRadiusDelta * m->orgOrbitRadius * 1.1f * dt;
		if (m->orbitRadius <= m->orgOrbitRadius) m->orbitRadius = m->orgOrbitRadius;
		else if (m->orbitRadius >= m->orgOrbitRadius * 1.5f) m->orbitRadius = m->orgOrbitRadius * 1.5f;

		m->setPos(myPos + Vector3(m->orbitRadius, 0.0f, 0.0f));
		m->orbitRotate.offset = m->orbit.offset = myPos;
	}

	setPos(myPos);
}

void Sphere18::render() const
{
	bool drawMode{ static_cast<Scene_Assignment18*>(SceneManager::getInstance().getCurScene())->getDrawMode() };

	ShaderManager::getInstance().useProgram("default");

	glm::mat4 model{ 1.0f };
	// model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	// model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::translate(model, getPos());
	model = glm::scale(model, getScale());

	ShaderManager::getInstance().setMat4("default", "model", model);
	ShaderManager::getInstance().setVec3("default", "color", color);

	MeshManager::getInstance().drawMesh("sphere", drawMode);

	glm::mat4 orbitModel{ 1.0f };
	// orbitModel = glm::rotate(orbitModel, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	// orbitModel = glm::rotate(orbitModel, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	orbitModel = glm::translate(orbitModel, orbit.offset);
	orbitModel = glm::rotate(orbitModel, glm::radians(orbitRotate.degree), Vector3(0.0f, 0.0f, 1.0f));
	orbitModel = glm::rotate(orbitModel, glm::radians(orbitTiltDeg), Vector3(0.0f, 0.0f, 1.0f));
	orbitModel = glm::scale(orbitModel, Vector3(orbitRadius, orbitRadius, orbitRadius));

	orbitModel = glm::rotate(orbitModel, glm::radians(-90.0f), Vector3(1.0f, 0.0f, 0.0f));

	ShaderManager::getInstance().setMat4("default", "model", orbitModel);
	ShaderManager::getInstance().setVec3("default", "color", COLOR_BLACK);

	MeshManager::getInstance().drawCircle();
}

void Sphere18::addMoon(Sphere18* child)
{
	moon.push_back(child);
}