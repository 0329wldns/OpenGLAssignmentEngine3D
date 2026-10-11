#include "pch.h"
#include "Scene_Assignment15.h"
#include "KeyManager.h"
#include "EventFunc.h"
#include "cube15.h"

void Scene_Assignment15::processKeyInput()
{
	if (KeyManager::getInstance().getKeyState(KEY::H) == KEY_STATE::TAP)
	{
		if (hFlag) glDisable(GL_DEPTH_TEST);
		else glEnable(GL_DEPTH_TEST);
		hFlag = !hFlag;
	}

	if (KeyManager::getInstance().getKeyState(KEY::MINUS) == KEY_STATE::TAP) glDisable(GL_CULL_FACE);
	if (KeyManager::getInstance().getKeyState(KEY::EQUAL) == KEY_STATE::TAP) glEnable(GL_CULL_FACE);
	if (KeyManager::getInstance().getKeyState(KEY::ESC) == KEY_STATE::TAP) changeScene(SCENE_TYPE::START);
}

void Scene_Assignment15::update()
{
	Scene::update();
}

void Scene_Assignment15::drawBG() const
{
	Scene::drawAxis();
}

void Scene_Assignment15::enter()
{
	Cube15* cube{ new Cube15 };
	createObject(cube, OBJECT_GROUP::POLYHENDRON);
}

void Scene_Assignment15::exit()
{
	reset();
}
