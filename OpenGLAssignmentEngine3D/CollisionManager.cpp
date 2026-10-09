#include "pch.h"
#include "CollisionManager.h"

void CollisionManager::update()
{
	for (int row = 0; row < (int)OBJECT_GROUP::END; ++row)
	{
		for (int col = row; col < (int)OBJECT_GROUP::END; ++col)
		{
			if (arrCheck[row] & (1 << col))
				collisionGroupUpdate((OBJECT_GROUP)row, (OBJECT_GROUP)col);
		}
	}
}

void CollisionManager::checkCollisionGroup(OBJECT_GROUP left, OBJECT_GROUP right)
{
	int row{ (int)left };
	int col{ (int)right };
	if (col < row)
	{
		col = (int)left;
		row = (int)right;
	}
	if (!(arrCheck[row] & (1 << col))) arrCheck[row] |= (1 << col);
	else arrCheck[row] &= ~(1 << col);
}

void CollisionManager::collisionGroupUpdate(OBJECT_GROUP left, OBJECT_GROUP right)
{
	Scene* curScene = SceneManager::getInstance().getCurScene();
	const vector<Object*>& vecLeft = curScene->getGroupObject(left);
	const vector<Object*>& vecRight = curScene->getGroupObject(right);

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		if (vecLeft[i]->getCollider() == nullptr) continue;
		size_t startJ = (left == right) ? i + 1 : 0;
		for (size_t j = startJ; j < vecRight.size(); ++j)
		{
			if (vecRight[j]->getCollider() == nullptr || vecLeft[i] == vecRight[j]) continue;

			Collider* leftCol = vecLeft[i]->getCollider();
			Collider* rightCol = vecRight[j]->getCollider();

			COLLIDER_ID id;
			if (leftCol->getId() < rightCol->getId())
			{
				id.leftId = leftCol->getId();
				id.rightId = rightCol->getId();
			}
			else
			{
				id.leftId = rightCol->getId();
				id.rightId = leftCol->getId();
			}

			auto iter = collisionInfo.find(id.id);

			if (collisionInfo.end() == iter)
			{
				collisionInfo.insert(make_pair(id.id, false));
				iter = collisionInfo.find(id.id);
			}

			// 충돌
			if (isCollision(leftCol, rightCol))
			{
				// 이전에도 충돌이 있었다
				if (iter->second)
				{
					if (leftCol->getObj()->isDead() || rightCol->getObj()->isDead())
					{
						leftCol->onCollisionExit(rightCol);
						rightCol->onCollisionExit(leftCol);
						iter->second = false;
					}
					else
					{
						leftCol->onCollision(rightCol);
						rightCol->onCollision(leftCol);
					}
				}
				// 이전에는 충돌이 없었다
				else
				{
					if (!leftCol->getObj()->isDead() && !rightCol->getObj()->isDead())
					{
						leftCol->onCollisionEnter(rightCol);
						rightCol->onCollisionEnter(leftCol);
						iter->second = true;
					}
				}
			}
			else
			{
				// 이전에는 충돌이 있었다
				if (iter->second)
				{
					leftCol->onCollisionExit(rightCol);
					rightCol->onCollisionExit(leftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CollisionManager::isCollision(const Collider* leftCol, const Collider* rightCol) const
{
	if ((leftCol->getPos().x - leftCol->getScale().x < rightCol->getPos().x + rightCol->getScale().x
		&& leftCol->getPos().x + leftCol->getScale().x > rightCol->getPos().x - rightCol->getScale().x
		&& leftCol->getPos().y - leftCol->getScale().y < rightCol->getPos().y + rightCol->getScale().y
		&& leftCol->getPos().y + leftCol->getScale().y > rightCol->getPos().y - rightCol->getScale().y))
	{
		return true;
	}
	return false;
}

void CollisionManager::reset()
{
	memset(arrCheck, 0, sizeof(unsigned int) * (int)OBJECT_GROUP::END);
	collisionInfo.clear();
}
