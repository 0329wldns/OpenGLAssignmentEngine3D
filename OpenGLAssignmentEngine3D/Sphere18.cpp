#include "pch.h"
#include "Sphere18.h"
#include "ShaderManager.h"
#include "MeshManager.h"
#include "TimeManager.h"
#include "KeyManager.h"

Sphere18::Sphere18(Color _color, Vector3 _scale, float _orbitRadius, float _orbitTiltDeg)
	: color(_color), orbitRadius(_orbitRadius), orbitTiltDeg(_orbitTiltDeg)
{
	setScale(_scale);
	setPos(orbitRadius, 0.0f, 0.0f);

	orbit.axis = Vector3(0.0f, 1.0f, 0.0f);
	orbit.isActive = true;
	orbit.speed = 45.0f + realDist(gen) * 135.0f;	// 45 ~ 180
}

Sphere18::~Sphere18()
{
}

void Sphere18::update()
{
	orbit.update();
	Vector3 myPos{ getPos() };

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
		
		myPos += moveDir * speed * TimeManager::getInstance().getDeltaTime();
		orbit.offset = myPos;

		cout << "center pos : " << myPos.x << ", " << myPos.y << ", " << myPos.z << endl;
	}
	
	glm::mat4 rotation{ orbit.getRotationMatrix() };
	myPos = rotation * glm::vec4(myPos, 1.0f);

	myPos -= orbit.offset;
	myPos = glm::rotate(glm::mat4(1.0f), glm::radians(orbitTiltDeg), Vector3(0.0f, 0.0f, 1.0f)) * glm::vec4(myPos, 1.0f);
	myPos += orbit.offset;

	for (auto& m : moon)
	{
		m->setPos(myPos + Vector3(m->orbitRadius, 0.0f, 0.0f));
		m->orbit.offset = myPos;
	}

	setPos(myPos);
}

void Sphere18::render() const
{
	ShaderManager::getInstance().useProgram("default");

	glm::mat4 model{ 1.0f };
	model = glm::translate(model, getPos());
	model = glm::scale(model, getScale());

	ShaderManager::getInstance().setMat4("default", "model", model);
	ShaderManager::getInstance().setVec3("default", "color", color);

	MeshManager::getInstance().drawMesh("sphere", false);
}

void Sphere18::addMoon(Sphere18* child)
{
	moon.push_back(child);
}