#include "pch.h"
#include "SceneManager.h"
#include "Scene_Start.h"
#include "Scene_Assignment13.h"
#include "Scene_Assignment14.h"
// #include "Scene_Assignment15.h"
// #include "Scene_Assignment16.h"
// #include "Scene_Assignment17.h"

SceneManager::SceneManager()
	: scene()
	, curScene(nullptr)
{
}

void SceneManager::init()
{
	scene[(int)SCENE_TYPE::START] = new Scene_Start;
	scene[(int)SCENE_TYPE::ASSIGNMENT13] = new Scene_Assignment13;
	scene[(int)SCENE_TYPE::ASSIGNMENT14] = new Scene_Assignment14;
	// scene[(int)SCENE_TYPE::ASSIGNMENT15] = new Scene_Assignment15;
	// scene[(int)SCENE_TYPE::ASSIGNMENT16] = new Scene_Assignment16;
	// scene[(int)SCENE_TYPE::ASSIGNMENT17] = new Scene_Assignment17;

	curScene = scene[(int)SCENE_TYPE::START];
	curScene->enter();
}

void SceneManager::update()
{
	curScene->update();
}

void SceneManager::finalUpdate()
{
	curScene->finalUpdate();
}

void SceneManager::render() const
{
	curScene->render();
}

void SceneManager::changeScene(SCENE_TYPE nextScene)
{
	curScene->exit();
	curScene = scene[(int)nextScene];
	curScene->enter();
}
