#include "pch.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Collider.h"
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

		for (auto& colliderObject : _colliderObjects)
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

		for (auto& colliderObject : _colliderObjects)
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
}
