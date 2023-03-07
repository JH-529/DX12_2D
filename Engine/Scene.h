#pragma once

enum class SCENE_TYPE : uint8
{
	MAIN,
	STAGE1,
	END
};

enum
{
	SCENE_TYPE_COUNT = static_cast<uint8>(SCENE_TYPE::END)
};

class GameObject;


class Scene
{
public:
	Scene(SCENE_TYPE type);

	void Awake();
	void Start();
	void Update();
	void LateUpdate();	
	void FinalUpdate();

	SCENE_TYPE GetType() { return _type; }

	void AddGameObject(shared_ptr<GameObject> gameObject);
	void RemoveGameObject(shared_ptr<GameObject> gameObject);

	void ObjectCollision();
	void AttackCollision();

	const vector<shared_ptr<GameObject>>& GetGameObjects() { return _gameObjects; }

private:
	SCENE_TYPE _type;
	shared_ptr<GameObject> _player;
	vector<shared_ptr<GameObject>> _gameObjects;
	vector<shared_ptr<GameObject>> _colliderGameObjects;
	vector<shared_ptr<GameObject>> _colliderAttack;
};

