#include "pch.h"
#include "Scene_Assignment14.h"
#include "KeyManager.h"
#include "EventFunc.h"
#include "Cube14.h"

void Scene_Assignment14::processKeyInput()
{
	if (KeyManager::getInstance().getKeyState(KEY::X) == KEY_STATE::TAP)
	{
		if (KeyManager::getInstance().getKeyState(KEY::LEFT_SHIFT) == KEY_STATE::HOLD) rotateDir.x = -1.0f;
		else rotateDir.x = 1.0f;
	}
	if (KeyManager::getInstance().getKeyState(KEY::Y) == KEY_STATE::TAP)
	{
		if (KeyManager::getInstance().getKeyState(KEY::LEFT_SHIFT) == KEY_STATE::HOLD) rotateDir.y = -1.0f;
		else rotateDir.y = 1.0f;
	}
	if (KeyManager::getInstance().getKeyState(KEY::W) == KEY_STATE::TAP)
	{
		if (KeyManager::getInstance().getKeyState(KEY::LEFT_SHIFT) == KEY_STATE::HOLD) drawLine = false;
		else drawLine = true;
	}

	if (KeyManager::getInstance().getKeyState(KEY::UP) == KEY_STATE::TAP) moveDir.y += 1.0f;
	else if (KeyManager::getInstance().getKeyState(KEY::UP) == KEY_STATE::AWAY) moveDir.y -= 1.0f;
	if (KeyManager::getInstance().getKeyState(KEY::DOWN) == KEY_STATE::TAP) moveDir.y -= 1.0f;
	else if (KeyManager::getInstance().getKeyState(KEY::DOWN) == KEY_STATE::AWAY) moveDir.y += 1.0f;
	if (KeyManager::getInstance().getKeyState(KEY::LEFT) == KEY_STATE::TAP) moveDir.x -= 1.0f;
	else if (KeyManager::getInstance().getKeyState(KEY::LEFT) == KEY_STATE::AWAY) moveDir.x += 1.0f;
	if (KeyManager::getInstance().getKeyState(KEY::RIGHT) == KEY_STATE::TAP) moveDir.x += 1.0f;
	else if (KeyManager::getInstance().getKeyState(KEY::RIGHT) == KEY_STATE::AWAY) moveDir.x -= 1.0f;


	if (KeyManager::getInstance().getKeyState(KEY::S) == KEY_STATE::TAP)
	{
		rotateDir.x = 0.0f;
		rotateDir.y = 0.0f;
	}

	if (KeyManager::getInstance().getKeyState(KEY::ESC) == KEY_STATE::TAP)
	{
		changeScene(SCENE_TYPE::START);;
		rotateDir.x = 0.0f;
		rotateDir.y = 0.0f;
		drawLine = false;
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
