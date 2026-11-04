#pragma once
#include "pch.h"
#include "Scene.h"

class Scene_Assignment23 : public Scene
{
public:
	Scene_Assignment23();
	~Scene_Assignment23() = default;

	void processKeyInput() override;
	void update() override;

	void drawBG() const override;
	void drawUI() const override {};

	void enter() override;
	void exit() override;

private:
	FaceData faceData[6];
	bool openTrigger;
};