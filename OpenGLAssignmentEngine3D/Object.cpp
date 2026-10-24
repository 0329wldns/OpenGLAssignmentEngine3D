#include "pch.h"
#include "Object.h"
#include "TimeManager.h"

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

void RotateData::update()
{
	if (!isActive) return;

	float dt{ TimeManager::getInstance().getDeltaTime() };

	degree += speed * dt;

	if (degree >= abs(targetDegree))
	{
		if (isExpire)
		{
			isEnd = true;
			isActive = false;
			return;
		}
		if (isReverse)
		{
			speed *= -1.0f;
			targetDegree -= targetDegree;
		}
		if (isStop) isActive = false;
	}
}

void FaceData::update()
{
	auto iter{ rotateData.begin() };
	for (; iter != rotateData.end();)
	{
		auto& data = *iter;
		if (data.isEnd)
		{
			iter = rotateData.erase(iter);
			continue;
		}
		data.update();
		++iter;
	}
}

void FaceData::addRotateData(const RotateData& _data)
{
	auto it{ std::find_if(rotateData.begin(), rotateData.end(), [&_data](const auto& data)
	{
		return data.rotateType >= _data.rotateType;
	}) };

	rotateData.insert(it, _data);
}
