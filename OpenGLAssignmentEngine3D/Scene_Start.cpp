#include "pch.h"
#include "Scene_Start.h"
#include "KeyManager.h"
#include "EventFunc.h"
#include "UIButton.h"

void Scene_Start::processKeyInput()
{
	if (KeyManager::getInstance().getKeyState(KEY::ESC) == KEY_STATE::TAP)
		glfwSetWindowShouldClose(Core::getInstance().getWindow(), true);
}

void Scene_Start::update()
{	
	processKeyInput();
	Scene::update();
}

void Scene_Start::enter()
{
	for (int i = (int)SCENE_TYPE::ASSIGNMENT13; i < (int)SCENE_TYPE::END; ++i)
	{
		UIButton* button = new UIButton();
		button->setPos(-400.0f + (i - 1) % 3 * 400.0f, 200.0f - ((i - 1) / 3) * 200.0f);
		button->setTargetScene((SCENE_TYPE)i);
		createObject(button, OBJECT_GROUP::UIBUTTON);
	}
}

void Scene_Start::exit()
{
	reset();
}