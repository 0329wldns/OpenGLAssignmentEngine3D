#pragma once
#include "pch.h"
#include "Singleton.h"

#include "SceneManager.h"

#include "Object.h"
#include "collider.h"

union COLLIDER_ID 
{
	struct 
	{
		unsigned int leftId;
		unsigned int rightId;
	};
	uint64_t id; // ULONGLONG 대신 C++ 표준 타입 사용
};

class CollisionManager : public Singleton<CollisionManager>
{
	friend class Singleton<CollisionManager>;

public:
	void update();
	void checkCollisionGroup(OBJECT_GROUP, OBJECT_GROUP);
	void collisionGroupUpdate(OBJECT_GROUP, OBJECT_GROUP);
	bool isCollision(const Collider*, const Collider*) const;
	void reset();

private:
	CollisionManager() = default;
	~CollisionManager() = default;

private:
	map<uint64_t, bool> collisionInfo;		// 이전 프레임 충돌 상태를 저장
	unsigned int arrCheck[(int)OBJECT_GROUP::END]{};
};