#pragma once
#include "pch.h"
#include "Scene.h"

class Scene_Assignment14 : public Scene
{
public:
	Scene_Assignment14() = default;
	~Scene_Assignment14() = default;

	void processKeyInput() override;
	void update() override;

	void drawBG() const override;
	void drawUI() const override {};

	void enter() override;
	void exit() override;
};