#include "pch.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Collider.h"
#include "RigidBody2D.h"
#include "Input.h"

void GameManager::Init()
{
	
}

void GameManager::Update()
{
	_activeScene = GET_SINGLE(SceneManager)->GetActiveScene();

	// F1을 누를경우 Collider경계를 Rendering 하지 않음
	if (INPUT->GetButton(KEY_TYPE::F1))
	{
		_colliderObjects = _activeScene->GetColliderObjects();
		_objects = _activeScene->GetObjects();

		for (auto& colliderObject : _colliderObjects)
		{
			// Alive인 Object만 Collider On/Off의 대상이 된다.
			if (colliderObject->IsAlive())
			{
				colliderObject->GetCollider()->NotRender();
			}
		}
		for (auto& colliderObject : _objects)
		{
			// Alive인 Object만 Collider On/Off의 대상이 된다.
			if (colliderObject->IsAlive())
			{
				colliderObject->GetCollider()->NotRender();
			}
		}
	}

	// F2를 누를경우 Collider경계를 Rendering 함
	if (INPUT->GetButton(KEY_TYPE::F2))
	{
		_colliderObjects = _activeScene->GetColliderObjects();
		_objects = _activeScene->GetObjects();

		for (auto& colliderObject : _colliderObjects)
		{
			// Alive인 Object만 Collider On/Off의 대상이 된다.
			if (colliderObject->IsAlive())
			{				
				colliderObject->GetCollider()->SetRender();
			}
		}
		for (auto& colliderObject : _objects)
		{
			// Alive인 Object만 Collider On/Off의 대상이 된다.
			if (colliderObject->IsAlive())
			{
				colliderObject->GetCollider()->SetRender();
			}
		}
	}

	// Scene 전환 테스트용
	if (INPUT->GetButton(KEY_TYPE::F3))
	{
		GET_SINGLE(SceneManager)->LoadScene(SCENE_TYPE::STAGE1);		
	}

	if (INPUT->GetButton(KEY_TYPE::W))
	{
		shared_ptr<GameObject> player = _activeScene->GetPlayer();
		if (player->GetRigidBody2D()->IsInportal())
		{
			SCENE_TYPE type = _activeScene->GetPortalType();
			GET_SINGLE(SceneManager)->LoadScene(type);
		}			
	}
}
