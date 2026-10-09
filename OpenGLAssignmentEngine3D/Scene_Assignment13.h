#pragma once
#include "pch.h"
#include "Scene.h"

class Scene_Assignment13 : public Scene
{
public:
	Scene_Assignment13() = default;
	~Scene_Assignment13() = default;

	void processKeyInput() override;
	void update() override;

	void drawBG() const override;
	void drawUI() const override {};

	void enter() override;
	void exit() override;

private:
	
};