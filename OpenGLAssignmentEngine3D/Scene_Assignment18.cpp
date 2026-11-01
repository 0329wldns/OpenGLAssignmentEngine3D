#include "pch.h"
#include "Scene_Assignment18.h"
#include "KeyManager.h"
#include "EventFunc.h"
#include "Sphere18.h"
#include "ShaderManager.h"

void Scene_Assignment18::processKeyInput()
{
	if (KeyManager::getInstance().getKeyState(KEY::P) == KEY_STATE::TAP)
	{
		projectionMode = !projectionMode;
		ShaderManager::getInstance().setBool("default", "projectionMode", projectionMode);
	}
	if (KeyManager::getInstance().getKeyState(KEY::M) == KEY_STATE::TAP)
	{
		drawMode = !drawMode;
	}
	if (KeyManager::getInstance().getKeyState(KEY::ESC) == KEY_STATE::TAP) changeScene(SCENE_TYPE::START);
}

void Scene_Assignment18::update()
{
	Scene::update();
}

void Scene_Assignment18::drawBG() const
{
	Scene::drawAxis();
}

void Scene_Assignment18::enter()
{
	Sphere18* center = new Sphere18(COLOR_RED, Vector3(100.0f, 100.0f, 100.0f));
	Sphere18* moon = new Sphere18(COLOR_RED + COLOR_BLUE, Vector3(50.0f, 50.0f, 50.0f), 300.0f);
	Sphere18* moon1 = new Sphere18(COLOR_GREEN, Vector3(30.0f, 30.0f, 30.0f), 100.0f, -45.0f);
	Sphere18* moon2 = new Sphere18(COLOR_BLUE, Vector3(15.0f, 15.0f, 15.0f), 50.0f);
	center->addMoon(moon);
	moon->addMoon(moon1);
	moon1->addMoon(moon2);

	Sphere18::setCenter(center);

	createObject(center, OBJECT_GROUP::POLYHENDRON);
	createObject(moon, OBJECT_GROUP::POLYHENDRON);
	createObject(moon1, OBJECT_GROUP::POLYHENDRON);
	createObject(moon2, OBJECT_GROUP::POLYHENDRON);
}

void Scene_Assignment18::exit()
{
	reset();
}
