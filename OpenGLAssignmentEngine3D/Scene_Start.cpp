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
		button->setPos(-0.5f + (i - 1) % 3 * 0.5f, 0.25f - (i - 1) / 3 * 0.5f);
		button->setTargetScene((SCENE_TYPE)i);
		createObject(button, OBJECT_GROUP::UIBUTTON);
	}
}

void Scene_Start::exit()
{
	reset();
}