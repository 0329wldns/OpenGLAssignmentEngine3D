#include "pch.h"
#include "Scene.h"
#include "KeyManager.h"
#include "Core.h"

void Scene::update()
{
	processKeyInput();
	processMouseInput();

	for (int i =  0; i < (int)OBJECT_GROUP::END; ++i)
	{
		auto iter = object[i].begin();
		for (; iter != object[i].end();) {
			if (!(*iter)->isDead())
			{
				(*iter)->update();
				++iter;
			}
			else
			{
				if (focusedObject == *iter)
					focusedObject = nullptr;
				iter = object[i].erase(iter);
			}
		}
	}
}

void Scene::finalUpdate()
{
	for (int i = 0; i < (int)OBJECT_GROUP::END; ++i)
	{
		for (size_t j = 0; j < object[i].size(); ++j)
		{
			object[i][j]->finalUpdate();
		}
	}
}

void Scene::render()
{
	drawBG();
	for (int i = 0; i < (int)OBJECT_GROUP::END; ++i)
	{
		for (size_t j = 0; j < object[i].size(); ++j)
		{
			if (!object[i][j]->isDead())
			{
				object[i][j]->render();
			}
		}
	}
	drawUI();

	drawClear();
}

void Scene::reset()
{
	for (int i = 0; i < (int)OBJECT_GROUP::END; ++i)
	{
		for (size_t j = 0; j < object[i].size(); ++j) 
		{
			delete object[i][j];
		}
		object[i].clear();
	}
	focusedObject = nullptr;
}

void Scene::addObject(Object* obj, OBJECT_GROUP group)
{
	object[(int)group].push_back(obj);
}

const void Scene::processMouseInput()
{
	Vector2 mousePos{ KeyManager::getInstance().getMousePos() };

	
	for (int i = (int)OBJECT_GROUP::END - 1; i >= 0; --i)
	{
		for (int j = object[i].size() - 1; j >= 0; --j)
		{
			Vector2 myPos{ object[i][j]->getPos() };
			Vector2 myScale{ object[i][j]->getScale() };

			if (mousePos.x > myPos.x - myScale.x && mousePos.x < myPos.x + myScale.x &&
				mousePos.y > myPos.y - myScale.y && mousePos.y < myPos.y + myScale.y)
			{
				focusedObject = object[i][j];

				focusedObject->onMouseEnter();
				if (KeyManager::getInstance().getKeyState(KEY::MOUSE_L) == KEY_STATE::TAP)	//	마우스 좌클릭
				{
					focusedObject->onMouseDownLeft();
				}
				else if (KeyManager::getInstance().getKeyState(KEY::MOUSE_R) == KEY_STATE::TAP)	// 마우스 우클릭
				{
						focusedObject->onMouseDownRight();
				}
				break;
			}
		}
	}

	if (focusedObject)
	{
		Vector2 myPos{ focusedObject->getPos() };
		Vector2 myScale{ focusedObject->getScale() };

		if (!(mousePos.x > myPos.x - myScale.x && mousePos.x < myPos.x + myScale.x &&
			mousePos.y > myPos.y - myScale.y && mousePos.y < myPos.y + myScale.y))
		{
			focusedObject->onMouseLeave();
			focusedObject = nullptr;
		}

		if (KeyManager::getInstance().getKeyState(KEY::MOUSE_L) == KEY_STATE::AWAY)	//	마우스 좌클릭
		{
			focusedObject->onMouseUpLeft();
		}
		else if (KeyManager::getInstance().getKeyState(KEY::MOUSE_R) == KEY_STATE::AWAY)	// 마우스 우클릭
		{
			focusedObject->onMouseUpRight();
		}
	}
}
