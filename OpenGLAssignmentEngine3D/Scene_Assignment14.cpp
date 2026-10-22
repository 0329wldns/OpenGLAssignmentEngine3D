#include "pch.h"
#include "Scene_Assignment14.h"
#include "KeyManager.h"
#include "EventFunc.h"
#include "Cube14.h"
#include "Pyramid14.h"

void Scene_Assignment14::processKeyInput()
{
	if (KeyManager::getInstance().getKeyState(KEY::C) == KEY_STATE::TAP)
	{
		drawMode = false;
	}
	if (KeyManager::getInstance().getKeyState(KEY::P) == KEY_STATE::TAP)
	{
		drawMode = true;
	}
	if (KeyManager::getInstance().getKeyState(KEY::H) == KEY_STATE::TAP)
	{
		if (hFlag) glDisable(GL_DEPTH_TEST);
		else glEnable(GL_DEPTH_TEST);
		hFlag = !hFlag;
	}
	if (KeyManager::getInstance().getKeyState(KEY::W) == KEY_STATE::TAP)
	{
		if (KeyManager::getInstance().getKeyState(KEY::LEFT_SHIFT) == KEY_STATE::HOLD) drawLine = false;
		else drawLine = true;
	}
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

	if (KeyManager::getInstance().getKeyState(KEY::ESC) == KEY_STATE::TAP) changeScene(SCENE_TYPE::START);
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
	Cube14* cube{ new Cube14 };
	createObject(cube, OBJECT_GROUP::POLYHENDRON);

	Pyramid14* pyramid{ new Pyramid14 };
	createObject(pyramid, OBJECT_GROUP::POLYHENDRON);

	cout << "c: 육면체	p: 사각 뿔" << endl;
	cout << "h: 은면제거 적용/해제" << endl;
	cout << "w/W: 와이어 객체/솔리드 객체" << endl;
	cout << "x/X: x축을 기준으로 양/음 방향으로 회전 애니메이션 (자전)" << endl;
	cout << "y/Y: y축을 기준으로 양/음 방향으로 회전 애니메이션 (자전)" << endl;
	cout << "←/→/↑/↓: 좌/우/상/하로 객체를 이동한다. (x축, y축으로 이동)" << endl;
	cout << "s: 초기 위치로 리셋 (모든 애니메이션 멈추기" << endl;
}

void Scene_Assignment14::exit()
{
	reset();
	rotateDir.x = 0.0f;
	rotateDir.y = 0.0f;
	drawLine = false;
	drawMode = false;

	system("cls");
}
