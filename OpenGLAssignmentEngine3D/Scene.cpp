#include "pch.h"
#include "Scene.h"
#include "KeyManager.h"
#include "Core.h"
#include "MeshManager.h"
#include "ShaderManager.h"

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

void Scene::drawAxis() const
{
	ShaderManager::getInstance().useProgram("default");

	// X축
	glm::mat4 model{ 1.0f };
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, Vector3(2.0f));
	ShaderManager::getInstance().setMat4("default", "model", model);
	ShaderManager::getInstance().setVec3("default", "color", COLOR_RED);
	ShaderManager::getInstance().setFloat("default", "transparency", 1.0f);

	MeshManager::getInstance().drawLine();

	// Y축
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::scale(model, Vector3(2.0f));
	ShaderManager::getInstance().setMat4("default", "model", model);
	ShaderManager::getInstance().setVec3("default", "color", COLOR_GREEN);

	MeshManager::getInstance().drawLine();

	// Z축
	model = glm::mat4(1.0f);
	model = glm::rotate(model, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::rotate(model, glm::radians(120.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::scale(model, Vector3(2.0f));
	ShaderManager::getInstance().setMat4("default", "model", model);
	ShaderManager::getInstance().setVec3("default", "color", COLOR_BLUE);

	MeshManager::getInstance().drawLine();
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
