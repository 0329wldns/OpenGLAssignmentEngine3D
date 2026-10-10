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

	const Vector2& getRotateDir() const { return rotateDir; }
	const Vector2& getMoveDir() const { return moveDir; }
	bool getDrawLine() const { return drawLine; }

private:
	Vector2 rotateDir{ 0.0f, 0.0f };
	Vector2 moveDir{ 0.0f, 0.0f };
	bool drawLine{ false };
};