#include "pch.h"
#include "Scene_Assignment14.h"
#include "KeyManager.h"
#include "EventFunc.h"
#include "Cube14.h"

void Scene_Assignment14::processKeyInput()
{
	if (KeyManager::getInstance().getKeyState(KEY::ESC) == KEY_STATE::TAP)
	{
		changeScene(SCENE_TYPE::START);;
	}
}

void Scene_Assignment14::update()
{
	Scene::update();
}

void Scene_Assignment14::drawBG() const
{
	Scene::drawAxis();
}

void Scene_Assignment14::enter()
{
	Cube14* cube{ new Cube14{} };
	createObject(cube, OBJECT_GROUP::DEFAULT);
}

void Scene_Assignment14::exit()
{
	reset();
}
