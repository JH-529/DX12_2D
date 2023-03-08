#include "pch.h"
#include "Physics2D.h"
#include "SceneManager.h"

int Physics2D::RayCast(Vec2 pos, Vec2 dir, float dis)
{
	shared_ptr<Scene> scene = ACTIVE_SCENE;
	assert(scene);

	vector<shared_ptr<GameObject>> _gameObjects = scene->GetGameObjects();

	return 0;
}
