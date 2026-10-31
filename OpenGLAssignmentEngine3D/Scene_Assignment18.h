#pragma once
#include "pch.h"
#include "Scene.h"

class Scene_Assignment18 : public Scene
{
public:
	Scene_Assignment18() = default;
	~Scene_Assignment18() = default;

	void processKeyInput() override;
	void update() override;
	void drawBG() const override;
	void drawUI() const override {};

	void enter() override;
	void exit() override;

private:
	bool projectionMode{ false };	// 1 : 원근, 0 : 직교
};