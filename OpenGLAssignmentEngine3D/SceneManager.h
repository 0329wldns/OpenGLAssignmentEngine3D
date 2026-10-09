#pragma once
#include "pch.h"
#include "Singleton.h"
#include "Scene.h"

class SceneManager : public Singleton<SceneManager>
{
	friend class Singleton<SceneManager>;

public:
	void init();

	void update();
	void finalUpdate();
	void render() const;

	void changeScene(SCENE_TYPE nextScene);

	Scene* getCurScene() const { return curScene; }
	void setCurScene(Scene* _curScene) { curScene = _curScene; }

private:
	SceneManager();
	~SceneManager() = default;

private:
	Scene* scene[(int)SCENE_TYPE::END];
	Scene* curScene;
};