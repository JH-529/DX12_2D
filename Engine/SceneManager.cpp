#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Engine.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Resources.h"
#include "RectCollider2D.h"

#include "PlayerScript.h"
#include "CameraScript.h"

void SceneManager::Update()
{
	if (_activeScene == nullptr)
		return;

	_activeScene->Update();
	_activeScene->LateUpdate();
	_activeScene->FinalUpdate();
}

void SceneManager::Render()
{
	if (_activeScene == nullptr)
		return;

	const vector<shared_ptr<GameObject>>& gameObjects = _activeScene->GetGameObjects();
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->GetCamera() == nullptr)
			continue;

		gameObject->GetCamera()->Render();
	}
}

// ���ڷ� ���� type�� �ش��ϴ� Scene�� _activeScene���� ����
void SceneManager::LoadScene(SCENE_TYPE type)
{
	// TODO : ���� Scene ����
	// TODO : ���Ͽ��� Scene ���� �ε�

	//_activeScene = LoadTestScene();

	/*for (auto it : _scene)
	{
		if (it->GetType() == type)
		{
			_activeScene = it;
			break;
		}
	}*/

	MakeMainScene();	

	for (auto it = _scene.begin(); it != _scene.end(); ++it)
	{
		shared_ptr<Scene> scene = *it;

		if (scene->GetType() == type)
		{
			_activeScene = scene;
			break;
		}
	}

	_activeScene->Awake();
	_activeScene->Start();
}

void SceneManager::MakeMainScene()
{
	shared_ptr<Scene> scene = make_shared<Scene>(SCENE_TYPE::MAIN);
	
	shared_ptr<Shader> defaultShader = make_shared<Shader>();
	shared_ptr<Texture> playerTexture = make_shared<Texture>();
	shared_ptr<Texture> monsterTexture = make_shared<Texture>();	
	shared_ptr<Texture> fieldTexture = make_shared<Texture>();
	defaultShader->Init(L"..\\Resources\\Shader\\default.hlsl");
	playerTexture->Init(L"..\\Resources\\Texture\\Cat.png");
	monsterTexture->Init(L"..\\Resources\\Texture\\BlueSnail.jpg");
	fieldTexture->Init(L"..\\Resources\\Texture\\field.png");

#pragma region Player
	{
		shared_ptr<GameObject> player = make_shared<GameObject>();
		player->SetName(L"Player");
		// Transform �߰�
		player->AddComponent(make_shared<Transform>());
		player->GetTransform()->SetLocalScale(Vec3(170.f, 170.f, 0.f));
		player->GetTransform()->SetLocalPosition(Vec3(-280.f, -160.f, -2.f));

		// MeshRenderer ����
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{ // 1. Mesh
			shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadRectMesh();
			meshRenderer->SetMesh(mesh);
		}
		{ // 2. Material
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(defaultShader);
			material->SetTexture(0, playerTexture);
			material->SetInt(0, 1);
			meshRenderer->SetMaterial(material);
		}
		player->AddComponent(meshRenderer);
		player->AddComponent(make_shared<RectCollider2D>());
		player->AddComponent(make_shared<PlayerScript>());
		scene->AddGameObject(player);
	}
#pragma endregion

#pragma region Object
	{
		shared_ptr<GameObject> gameObject = make_shared<GameObject>();
		gameObject->SetName(L"Object");
		// Transform �߰�
		gameObject->AddComponent(make_shared<Transform>());
		gameObject->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 0.f));
		gameObject->GetTransform()->SetLocalPosition(Vec3(300.f, -110.f, -2.f));
		// MeshRenderer ����
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{ // 1. Mesh
			shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadRectMesh();
			meshRenderer->SetMesh(mesh);
		}
		{ // 2. Material
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(defaultShader);
			material->SetTexture(0, monsterTexture);
			material->SetInt(0, 1);
			meshRenderer->SetMaterial(material);
		}							
		gameObject->AddComponent(meshRenderer);
		gameObject->AddComponent(make_shared<RectCollider2D>());
		scene->AddGameObject(gameObject);
	}
#pragma endregion

#pragma region Object
	{
		shared_ptr<GameObject> gameObject2 = make_shared<GameObject>();
		gameObject2->SetName(L"Object2");
		// Transform �߰�
		gameObject2->AddComponent(make_shared<Transform>());
		gameObject2->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 0.f));
		gameObject2->GetTransform()->SetLocalPosition(Vec3(0.f, -110.f, -2.f));
		// MeshRenderer ����
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{ // 1. Mesh
			shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadRectMesh();
			meshRenderer->SetMesh(mesh);
		}
		{ // 2. Material
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(defaultShader);
			material->SetTexture(0, monsterTexture);
			material->SetInt(0, 1);
			meshRenderer->SetMaterial(material);
		}
		gameObject2->AddComponent(meshRenderer);
		gameObject2->AddComponent(make_shared<RectCollider2D>());
		scene->AddGameObject(gameObject2);
	}
#pragma endregion

#pragma region field
	{
		shared_ptr<GameObject> fieldObject = make_shared<GameObject>();
		fieldObject->SetName(L"Field");
		// Transform ����
		fieldObject->AddComponent(make_shared<Transform>());
		float height = GEngine->GetWindow().height;
		float width = GEngine->GetWindow().width;
		fieldObject->GetTransform()->SetLocalScale(Vec3(width, height, 0.f));

		// GameObject�� �߰��� MeshRenderer
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{ // 1. Mesh
			shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadRectMesh();
			meshRenderer->SetMesh(mesh);
		}
		{ // 2. Material
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(defaultShader);
			material->SetTexture(0, fieldTexture);
			material->SetInt(0, 1);
			meshRenderer->SetMaterial(material);
		}
		
		fieldObject->AddComponent(meshRenderer);
		scene->AddGameObject(fieldObject);
	}
#pragma endregion

#pragma region Camera
	{
		shared_ptr<GameObject> camera = make_shared<GameObject>();
		camera->SetName(L"Camera");
		camera->AddComponent(make_shared<Transform>());
		camera->AddComponent(make_shared<Camera>());		
		camera->GetCamera()->SetProjectionType(PROJECTION_TYPE::ORTHOGRAPHIC);
		camera->AddComponent(make_shared<CameraScript>());
		camera->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, -100.f));
		scene->AddGameObject(camera);
	}
#pragma endregion

	_scene.push_back(scene);
}