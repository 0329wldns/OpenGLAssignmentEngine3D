#include "pch.h"
#include "Object.h"

Object::Object()
	: pos()
	, scale()
	, collider(nullptr)
	, alive(true)
{

}

Object::~Object()
{
	if (collider != nullptr)
		delete collider;
}

void Object::createCollider()
{
	collider = new Collider;
	collider->setPos(pos);
	collider->setScale(scale);
	collider->owner = this;
}

void Object::finalUpdate()
{
	if (collider != nullptr)
		collider->finalUpdate();
}

void Object::componantRender() const
{
	if (collider != nullptr)
		collider->render();
}