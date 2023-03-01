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

	SCENE_TYPE GetType() { return _type; }

	void AddGameObject(shared_ptr<GameObject> gameObject);
	void RemoveGameObject(shared_ptr<GameObject> gameObject);

private:
	SCENE_TYPE _type;
	vector<shared_ptr<GameObject>> _gameObjects;	
};

