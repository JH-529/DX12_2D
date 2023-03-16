#pragma once
class GameManager
{
public:
	void Init();
	void Update();

private:
	shared_ptr<class Scene> _activeScene;
	vector<shared_ptr<class GameObject>> _colliderObjects;
};

