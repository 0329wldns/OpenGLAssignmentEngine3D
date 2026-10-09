#include "pch.h"
#include "collider.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "ShaderManager.h"
#include "MeshManager.h"

static unsigned int g_Id{ 0 };

Collider::Collider()
	: owner(nullptr)
	, pos()
	, scale()
	, offset()
	, id(g_Id++)
	, isCol(false)
{
}

void Collider::finalUpdate()
{
	pos.x = owner->getPos().x + offset.x;
	pos.y = owner->getPos().y + offset.y;
}

void Collider::render()
{
	glm::vec3 color{ 0.0f, 0.0f, 0.0f };

	if (isCol) color[0] = 1.0f; // 충돌 중이면 빨간색

	ShaderManager::getInstance().useProgram("default");

	Vector2 myPos{ getPos() };
	Vector2 myScale{ getScale() };

	glm::mat4 model{ 1.0f };
	model = glm::translate(model, glm::vec3(myPos.x, myPos.y, 0.0f));
	model = glm::scale(model, glm::vec3(myScale.x * 2, myScale.y * 2, 1.0f));

	ShaderManager::getInstance().setMat4("default", "model", model);
	ShaderManager::getInstance().setVec3("default", "color", color);
	ShaderManager::getInstance().setFloat("default", "transparency", 1.0f);

	MeshManager::getInstance().drawQuad(true);
}

void Collider::onCollision(Collider* other)
{
	owner->onCollision(other);
	isCol = true;
}

void Collider::onCollisionEnter(Collider* other)
{
	owner->onCollisionEnter(other);
	isCol = true;
}

void Collider::onCollisionExit(Collider* other)
{
	owner->onCollisionExit(other);
	isCol = false;
}
