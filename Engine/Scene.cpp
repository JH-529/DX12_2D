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

	ObjectCollision();
	AttackCollision();
}

void Scene::AddGameObject(shared_ptr<GameObject> gameObject)
{
	_gameObjects.push_back(gameObject);

	// 반드시 플레이어가 가장 먼저 추가되어야 한다.
	if (_player == nullptr)
	{
		_player = gameObject;
		return;
	}		

	if (gameObject->GetCollider())
	{
		if (gameObject->GetMeshRenderer())
			_colliderGameObjects.push_back(gameObject);
		if (!gameObject->GetMeshRenderer())
			_colliderAttack.push_back(gameObject);
	}
		
}

void Scene::RemoveGameObject(shared_ptr<GameObject> gameObject)
{
	auto findIt = std::find(_gameObjects.begin(), _gameObjects.end(), gameObject);
	if (findIt != _gameObjects.end())
	{
		_gameObjects.erase(findIt);
	}
}

void Scene::ObjectCollision()
{
	shared_ptr<Transform> playerTransform = _player->GetTransform();
	_player->GetRectCollider2D()->SetCollidedFalse();

	for (const shared_ptr<GameObject>& colliderGameObject : _colliderGameObjects)
	{
		colliderGameObject->GetRectCollider2D()->SetCollidedFalse();
		shared_ptr<Transform> objectTransform = colliderGameObject->GetTransform();

		// Collider가 살아있는 오브젝트에 대해서만 AABB 적용
		if (_player->GetCollider()->IsAlive() && colliderGameObject->GetCollider()->IsAlive())
		{
			if (RectCollider2D::AABB(*playerTransform, *objectTransform))
			{
				_player->GetRectCollider2D()->SetCollidedTrue();
				_player->GetRectCollider2D()->CollidedColor();
				colliderGameObject->GetRectCollider2D()->SetCollidedTrue();
				colliderGameObject->GetRectCollider2D()->CollidedColor();
			}
			else
			{
				if (_player->GetRectCollider2D()->GetCollided())
					_player->GetRectCollider2D()->CollidedColor();
				else
					_player->GetRectCollider2D()->BaseColor();

				if (colliderGameObject->GetRectCollider2D()->GetCollided())
					colliderGameObject->GetRectCollider2D()->CollidedColor();
				else
					colliderGameObject->GetRectCollider2D()->BaseColor();
			}
		}
	}
}

void Scene::AttackCollision()
{

	for (const shared_ptr<GameObject>& colliderAttack : _colliderAttack)
	{
		colliderAttack->GetRectCollider2D()->SetCollidedFalse();

		if (colliderAttack->GetCollider()->IsAlive())
		{
			for (const shared_ptr<GameObject>& colliderGameObject : _colliderGameObjects)
			{
				if (colliderGameObject->GetCollider()->IsAlive())
				{
					if (RectCollider2D::AABB(*(colliderAttack->GetTransform()), *(colliderGameObject->GetTransform())))
					{
						colliderAttack->GetRectCollider2D()->SetCollidedTrue();
						colliderAttack->GetRectCollider2D()->CollidedColor();
						colliderGameObject->GetRectCollider2D()->SetCollidedTrue();
						colliderGameObject->GetRectCollider2D()->CollidedColor();
					}
					else
					{
						if (colliderAttack->GetRectCollider2D()->GetCollided())
							colliderAttack->GetRectCollider2D()->CollidedColor();
						else
							colliderAttack->GetRectCollider2D()->BaseColor();

						if(colliderGameObject->GetRectCollider2D()->GetCollided())
							colliderGameObject->GetRectCollider2D()->CollidedColor();
						else
						{
							colliderGameObject->GetRectCollider2D()->SetCollidedFalse();
							colliderGameObject->GetRectCollider2D()->BaseColor();
						}
							
					}
				}
			}
		}
	}
}
