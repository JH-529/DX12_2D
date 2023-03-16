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

	// F1�� ������� Collider��踦 Rendering ���� ����
	if (INPUT->GetButton(KEY_TYPE::F1))
	{
		_colliderObjects = _activeScene->GetColliderObjects();

		for (auto& colliderObject : _colliderObjects)
		{
			// Alive�� Object�� Collider On/Off�� ����� �ȴ�.
			if (colliderObject->IsAlive())
			{
				colliderObject->GetCollider()->NotRender();
			}
		}
	}

	// F2�� ������� Collider��踦 Rendering ��
	if (INPUT->GetButton(KEY_TYPE::F2))
	{
		_colliderObjects = _activeScene->GetColliderObjects();

		for (auto& colliderObject : _colliderObjects)
		{
			// Alive�� Object�� Collider On/Off�� ����� �ȴ�.
			if (colliderObject->IsAlive())
			{				
				colliderObject->GetCollider()->SetRender();
			}
		}
	}

	// Scene ��ȯ �׽�Ʈ��
	if (INPUT->GetButton(KEY_TYPE::F3))
	{
		GET_SINGLE(SceneManager)->LoadScene(SCENE_TYPE::STAGE1);		
	}
}
