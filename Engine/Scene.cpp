#include "pch.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "RectCollider2D.h"

Scene::Scene(SCENE_TYPE type) : _type(type)
{
}

void Scene::Awake()
{
	for (const shared_ptr<GameObject>& gameObject : _gameObjects)
	{
		gameObject->Awake();
	}
}

void Scene::Start()
{
	for (const shared_ptr<GameObject>& gameObject : _gameObjects)
	{
		gameObject->Start();
	}
}

void Scene::Update()
{
	shared_ptr<Transform> player = _player->GetTransform();

	for (const shared_ptr<GameObject>& colliderGameObject : _colliderGameObjects)
	{
		shared_ptr<Transform> object = colliderGameObject->GetTransform();
		if (RectCollider2D::AABB(*player, *object))
		{
			_player->GetCollider();
		}
	}

	for (const shared_ptr<GameObject>& gameObject : _gameObjects)
	{
		gameObject->Update();
	}
}

void Scene::LateUpdate()
{
	for (const shared_ptr<GameObject>& gameObject : _gameObjects)
	{
		gameObject->LateUpdate();
	}
}

void Scene::FinalUpdate()
{
	for (const shared_ptr<GameObject>& gameObject : _gameObjects)
	{
		gameObject->FinalUpdate();
	}
}

void Scene::AddGameObject(shared_ptr<GameObject> gameObject)
{
	_gameObjects.push_back(gameObject);

	// �ݵ�� �÷��̾ ���� ���� �߰��Ǿ�� �Ѵ�.
	if (_colliderGameObjects.empty())
	{
		_player = gameObject;
		return;
	}		

	if (gameObject->GetCollider())
		_colliderGameObjects.push_back(gameObject);
}

void Scene::RemoveGameObject(shared_ptr<GameObject> gameObject)
{
	auto findIt = std::find(_gameObjects.begin(), _gameObjects.end(), gameObject);
	if (findIt != _gameObjects.end())
	{
		_gameObjects.erase(findIt);
	}
}