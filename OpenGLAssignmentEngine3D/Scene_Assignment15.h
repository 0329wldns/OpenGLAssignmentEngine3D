#pragma once
#include "pch.h"
#include "Scene.h"

class Scene_Assignment15 : public Scene
{
public:
	Scene_Assignment15() = default;
	~Scene_Assignment15() = default;

	void processKeyInput() override;
	void update() override;
	void drawBG() const override;
	void drawUI() const override {};

	void enter() override;
	void exit() override;

private:
	bool hFlag{ true };
};