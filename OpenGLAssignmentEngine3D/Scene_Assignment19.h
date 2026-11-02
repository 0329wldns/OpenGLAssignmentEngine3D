#pragma once
#include "pch.h"
#include "Scene.h"

class Scene_Assignment19 : public Scene
{
public:
	Scene_Assignment19();
	~Scene_Assignment19() = default;

	void processKeyInput() override;
	void update();
	void drawBG() const override;
	void drawUI() const override;

	void enter() override;
	void exit() override;

private:
	Vector3 cameraPos{};
	Vector3 cameraMoveDir{};
};