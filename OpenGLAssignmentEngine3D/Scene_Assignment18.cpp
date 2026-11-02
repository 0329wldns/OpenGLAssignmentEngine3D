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
	if (KeyManager::getInstance().getKeyState(KEY::M) == KEY_STATE::TAP) drawMode = !drawMode;
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
	Sphere18* moon11 = new Sphere18(COLOR_GREEN, Vector3(50.0f, 50.0f, 50.0f), 300.0f);
	Sphere18* moon12 = new Sphere18(COLOR_GREEN, Vector3(50.0f, 50.0f, 50.0f), 300.0f, -45.0f);
	Sphere18* moon13 = new Sphere18(COLOR_GREEN, Vector3(50.0f, 50.0f, 50.0f), 300.0f, 45.0f);
	Sphere18* moon21 = new Sphere18(COLOR_BLUE, Vector3(30.0f, 30.0f, 30.0f), 100.0f, 0.0f, true);
	Sphere18* moon22 = new Sphere18(COLOR_BLUE, Vector3(30.0f, 30.0f, 30.0f), 100.0f, 0.0f, true);
	Sphere18* moon23 = new Sphere18(COLOR_BLUE, Vector3(30.0f, 30.0f, 30.0f), 100.0f, 0.0f, true);

	center->addMoon(moon11);
	center->addMoon(moon12);
	center->addMoon(moon13);
	moon11->addMoon(moon21);
	moon12->addMoon(moon22);
	moon13->addMoon(moon23);

	Sphere18::setCenter(center);

	createObject(center, OBJECT_GROUP::POLYHENDRON);
	createObject(moon11, OBJECT_GROUP::POLYHENDRON);
	createObject(moon12, OBJECT_GROUP::POLYHENDRON);
	createObject(moon13, OBJECT_GROUP::POLYHENDRON);
	createObject(moon21, OBJECT_GROUP::POLYHENDRON);
	createObject(moon22, OBJECT_GROUP::POLYHENDRON);
	createObject(moon23, OBJECT_GROUP::POLYHENDRON);
}

void Scene_Assignment18::exit()
{
	reset();
}
