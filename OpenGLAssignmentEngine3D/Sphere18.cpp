#include "pch.h"
#include "Sphere18.h"
#include "ShaderManager.h"
#include "MeshManager.h"

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