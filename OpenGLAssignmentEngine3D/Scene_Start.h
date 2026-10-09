#pragma once
#include "pch.h"
#include "Scene.h"

class Scene_Start : public Scene
{
public:
	Scene_Start() = default;
	~Scene_Start() = default;

	void processKeyInput() override;
	void update() override;

	void drawBG() const override {};
	void drawUI() const override {};

	void enter() override;
	void exit() override;

private:
};
