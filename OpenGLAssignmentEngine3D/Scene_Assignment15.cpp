#include "pch.h"
#include "Scene_Assignment15.h"
#include "KeyManager.h"
#include "EventFunc.h"
#include "cube15.h"
#include "pyramid15.h"

void Scene_Assignment15::processKeyInput()
{
	if (KeyManager::getInstance().getKeyState(KEY::H) == KEY_STATE::TAP)
	{
		if (hFlag) glDisable(GL_DEPTH_TEST);
		else glEnable(GL_DEPTH_TEST);
		hFlag = !hFlag;
	}
	if (KeyManager::getInstance().getKeyState(KEY::P) == KEY_STATE::TAP) pFlag = !pFlag;
	if (KeyManager::getInstance().getKeyState(KEY::R) == KEY_STATE::TAP)
	{
		glEnable(GL_DEPTH_TEST);
		pFlag = false;
		hFlag = true;
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

	Pyramid15* pyramid{ new Pyramid15 };
	createObject(pyramid, OBJECT_GROUP::POLYHENDRON);

	cout << "y: y축에 대하여 자전한다/멈춘다." << endl;
	cout << "t: 윗면의 가운데 축 (z축)을 중심으로 회전/멈추기" << endl;
	cout << "f: 앞면이 위축을 기준으로 회전하여 열기/닫기" << endl;
	cout << "s: 옆면이 중점을 기준으로 제자리에서 회전/멈추기" << endl;
	cout << "b: 뒷면이 제 자리에서 작아지면서 없어진다/다시 커지면서 원래 크기가 된다." << endl;
	cout << "1: 옆면 4개에서 같은 모서리를 사용하는 두 면 중 랜덤하게 선택하여 모서리를 기준으로 (y축) 360 회전한다." << endl;
	cout << "2: 같은 모서리를 사용하는 두 면 중 랜덤하게 선택하고, 두 면이 육면체 중앙의 y축을 기준으로 서로 반대방향으로 90도 공전하여 자리를 교체한다." << endl;
	cout << "4: 육면체의 4개의 옆면이 육면체 중앙의 y축을 기준으로 공전한다." << endl;
	cout << "5: 육면체의 윗면, 아랫면, 2개의 옆면에 육면체 중앙의 x축을 기준으로 공전한다." << endl;
}

void Scene_Assignment15::exit()
{
	reset();
	system("cls");
}
