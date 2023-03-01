#pragma once
#include "Scene.h"

class Scene;

class SceneManager
{
	DECLARE_SINGLE(SceneManager);

public:
	void Update();
	void Render();
	void LoadScene(SCENE_TYPE type);

public:
	shared_ptr<Scene> GetActiveScene() { return _activeScene; }

private:
	void MakeMainScene();

private:
	vector<shared_ptr<Scene>> _scene;
	shared_ptr<Scene> _activeScene;
};

