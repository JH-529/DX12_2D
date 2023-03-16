#include "pch.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "Scene.h"

#include "Engine.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"
#include "Resources.h"
#include "RectCollider2D.h"
#include "TilemapCollider.h"
#include "RigidBody2D.h"
#include "Portal.h"

#include "PlayerScript.h"
#include "PlayerAttackScript.h"
#include "MonsterScript.h"
#include "CameraScript.h"

void SceneManager::Init()
{
	_gameManager = make_shared<GameManager>();
	MakeMainScene();
	MakeStage1();
}

void SceneManager::Update()
{
	if (_activeScene == nullptr)
		return;

	_gameManager->Update();
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

// 인자로 들어온 type에 해당하는 Scene을 _activeScene으로 설정
void SceneManager::LoadScene(SCENE_TYPE type)
{
	// TODO : 기존 Scene 정리
	// TODO : 파일에서 Scene 정보 로드
	/*_activeScene = LoadTestScene();
	for (auto it : _scene)
	{
		if (it->GetType() == type)
		{
			_activeScene = it;
			break;
		}
	}*/
		
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
	shared_ptr<Texture> blueSnail = make_shared<Texture>();	
	shared_ptr<Texture> redSnail = make_shared<Texture>();	
	shared_ptr<Texture> attackTexture = make_shared<Texture>();	
	shared_ptr<Texture> fieldTexture = make_shared<Texture>();
	shared_ptr<Texture> portalTexture = make_shared<Texture>();
	defaultShader->Init(L"..\\Resources\\Shader\\default.hlsl");
	playerTexture->Init(L"..\\Resources\\Texture\\Cat.png");
	blueSnail->Init(L"..\\Resources\\Texture\\BlueSnail.jpg");
	redSnail->Init(L"..\\Resources\\Texture\\RedSnail.jpg");
	attackTexture->Init(L"..\\Resources\\Texture\\Effect.png");
	fieldTexture->Init(L"..\\Resources\\Texture\\Field.png");
	portalTexture->Init(L"..\\Resources\\Texture\\Portal.png");

#pragma region Player
	{
		shared_ptr<GameObject> player = make_shared<GameObject>();
		player->SetName(L"Player");
		// Transform 추가
		player->AddComponent(make_shared<Transform>());
		player->GetTransform()->SetLocalScale(Vec3(200.f, 200.f, 0.f));
		player->GetTransform()->SetLocalPosition(Vec3(-800.f, -160.f, -2.f));

		// MeshRenderer 생성
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

		shared_ptr<RectCollider2D> playerCollider = make_shared<RectCollider2D>();
		playerCollider->SetAlive();
		playerCollider->NotRender();
		shared_ptr<RigidBody2D> rigidBody2D = make_shared<RigidBody2D>();
		rigidBody2D->SetGravity(10.f);		
		rigidBody2D->SetForce(1.1f);		
		player->AddComponent(playerCollider);		
		player->AddComponent(rigidBody2D);
		player->AddComponent(make_shared<PlayerScript>());
		scene->AddGameObject(player);

		// 플레이어의 공격 범위
		{
			shared_ptr<GameObject> playerAttack = make_shared<GameObject>();
			playerAttack->SetName(L"Attack");
			playerAttack->AddComponent(make_shared<Transform>());
			playerAttack->GetTransform()->SetLocalPosition(Vec3(0.7f, 0.f, 0.f));
			playerAttack->GetTransform()->SetParent(player->GetTransform());				
			playerAttack->GetTransform()->SetLocalScale(Vec3(1.f, 0.7f, 0));
			// MeshRenderer 생성
			shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
			{ // 1. Mesh
				shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadRectMesh();
				meshRenderer->SetMesh(mesh);
			}
			{ // 2. Material
				shared_ptr<Material> material = make_shared<Material>();
				material->SetShader(defaultShader);
				material->SetTexture(0, attackTexture);
				material->SetInt(0, 1);
				meshRenderer->SetMaterial(material);
			}
			playerAttack->AddComponent(meshRenderer);
			{
				shared_ptr<RectCollider2D> attackCollider = make_shared<RectCollider2D>();
				attackCollider->SetDead();
				playerAttack->AddComponent(attackCollider);
			}			
			playerAttack->AddComponent(make_shared<PlayerAttackScript>());
			playerAttack->ObjectDead();
			scene->AddGameObject(playerAttack);
		}
	}
#pragma endregion

#pragma region BlueSnail
	{
		shared_ptr<GameObject> gameObject = make_shared<GameObject>();
		gameObject->SetName(L"Monster");
		gameObject->InitializeStatus();
		// Transform 추가
		gameObject->AddComponent(make_shared<Transform>());
		gameObject->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 0.f));
		gameObject->GetTransform()->SetLocalPosition(Vec3(0.f, -110.f, -2.f));
		// MeshRenderer 생성
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{ // 1. Mesh
			shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadRectMesh();
			meshRenderer->SetMesh(mesh);
		}
		{ // 2. Material
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(defaultShader);
			material->SetTexture(0, blueSnail);
			material->SetInt(0, 1);
			meshRenderer->SetMaterial(material);
		}							
		gameObject->AddComponent(meshRenderer);
		shared_ptr<RigidBody2D> rigidBody2D = make_shared<RigidBody2D>();
		rigidBody2D->SetGravity(9.8f);
		rigidBody2D->SetForce(1.f);
		shared_ptr<RectCollider2D> collider = make_shared<RectCollider2D>();
		collider->SetAlive();
		collider->NotRender();
		gameObject->AddComponent(rigidBody2D);
		gameObject->AddComponent(collider);
		gameObject->AddComponent(make_shared<MonsterScript>());
		scene->AddGameObject(gameObject);
	}
#pragma endregion

#pragma region RedSnail
	{
		shared_ptr<GameObject> gameObject = make_shared<GameObject>();
		gameObject->SetName(L"Monster");
		gameObject->InitializeStatus();
		// Transform 추가
		gameObject->AddComponent(make_shared<Transform>());
		gameObject->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 0.f));
		gameObject->GetTransform()->SetLocalPosition(Vec3(400.f, -110.f, -2.f));
		// MeshRenderer 생성
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{ // 1. Mesh
			shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadRectMesh();
			meshRenderer->SetMesh(mesh);
		}
		{ // 2. Material
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(defaultShader);
			material->SetTexture(0, redSnail);
			material->SetInt(0, 1);
			meshRenderer->SetMaterial(material);
		}
		gameObject->AddComponent(meshRenderer);
		shared_ptr<RigidBody2D> rigidBody2D = make_shared<RigidBody2D>();
		rigidBody2D->SetGravity(9.8f);
		rigidBody2D->SetForce(1.f);
		shared_ptr<RectCollider2D> collider = make_shared<RectCollider2D>();
		collider->SetAlive();
		collider->NotRender();
		gameObject->AddComponent(rigidBody2D);
		gameObject->AddComponent(collider);
		gameObject->AddComponent(make_shared<MonsterScript>());
		scene->AddGameObject(gameObject);
	}
#pragma endregion

#pragma region TileMap
	// 1 floor
	{
		shared_ptr<GameObject> tileMap = make_shared<GameObject>();
		tileMap->SetName(L"Tile");
		// Transform 추가
		tileMap->AddComponent(make_shared<Transform>());
		tileMap->GetTransform()->SetLocalScale(Vec3(700.f, 100.f, 0.f));
		tileMap->GetTransform()->SetLocalPosition(Vec3(-700.f, -700.f, -2.f));

		shared_ptr<TilemapCollider> collider = make_shared<TilemapCollider>();
		collider->SetAlive();
		collider->NotRender();
		tileMap->AddComponent(collider);
		scene->AddGameObject(tileMap);
	}
	{
		shared_ptr<GameObject> tileMap = make_shared<GameObject>();
		tileMap->SetName(L"Tile");
		// Transform 추가
		tileMap->AddComponent(make_shared<Transform>());
		tileMap->GetTransform()->SetLocalScale(Vec3(200.f, 100.f, 0.f));
		tileMap->GetTransform()->SetLocalPosition(Vec3(-330.f, -620.f, -2.f));

		shared_ptr<TilemapCollider> collider = make_shared<TilemapCollider>();
		collider->SetAlive();
		collider->NotRender();
		tileMap->AddComponent(collider);
		scene->AddGameObject(tileMap);
	}
	// 2 floor
	{
		shared_ptr<GameObject> tileMap = make_shared<GameObject>();
		tileMap->SetName(L"Tile");
		// Transform 추가
		tileMap->AddComponent(make_shared<Transform>());
		tileMap->GetTransform()->SetLocalScale(Vec3(1400.f, 100.f, 0.f));
		tileMap->GetTransform()->SetLocalPosition(Vec3(350.f, -550.f, -2.f));
		
		shared_ptr<TilemapCollider> collider = make_shared<TilemapCollider>();
		collider->SetAlive();
		collider->NotRender();
		tileMap->AddComponent(collider);
		scene->AddGameObject(tileMap);
	}	
#pragma endregion

#pragma region field
	{
		shared_ptr<GameObject> fieldObject = make_shared<GameObject>();
		fieldObject->SetName(L"Field");
		// Transform 생성
		fieldObject->AddComponent(make_shared<Transform>());
		/*float height = GEngine->GetWindow().height;		
		float width = GEngine->GetWindow().width;*/		
		float width = static_cast<float>(GEngine->GetWindow().width) * 2.5f;
		float height = static_cast<float>(GEngine->GetWindow().height) * 2.5f;
		fieldObject->GetTransform()->SetLocalScale(Vec3(width, height, 0.f));

		// GameObject에 추가될 MeshRenderer
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

#pragma region Portal
	{
		shared_ptr<GameObject> portal = make_shared<GameObject>();
		portal->SetName(L"Portal");
		portal->InitializeStatus();
		portal->AddComponent(make_shared<Transform>());
		portal->GetTransform()->SetLocalScale(Vec3(150.f, 350.f, 0.f));
		portal->GetTransform()->SetLocalPosition(Vec3(800.f, -350.f, -2.f));
		portal->AddComponent(make_shared<Portal>(SCENE_TYPE::STAGE1));

		// MeshRenderer 생성
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{ // 1. Mesh
			shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadRectMesh();
			meshRenderer->SetMesh(mesh);
		}
		{ // 2. Material
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(defaultShader);
			material->SetTexture(0, portalTexture);
			material->SetInt(0, 1);
			meshRenderer->SetMaterial(material);
		}
		portal->AddComponent(meshRenderer);
		shared_ptr<RectCollider2D> collider = make_shared<RectCollider2D>();
		collider->SetAlive();
		collider->NotRender();
		portal->AddComponent(collider);
		portal->AddComponent(make_shared<MonsterScript>());
		scene->AddGameObject(portal);
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

void SceneManager::MakeStage1() 

{
	shared_ptr<Scene> scene = make_shared<Scene>(SCENE_TYPE::STAGE1);

#pragma region Shader&Texture
	shared_ptr<Shader> defaultShader = make_shared<Shader>();
	shared_ptr<Texture> playerTexture = make_shared<Texture>();
	shared_ptr<Texture> jrBalrog = make_shared<Texture>();
	shared_ptr<Texture> crimsonBalrog = make_shared<Texture>();
	shared_ptr<Texture> attackTexture = make_shared<Texture>();
	shared_ptr<Texture> fieldTexture = make_shared<Texture>();
	defaultShader->Init(L"..\\Resources\\Shader\\default.hlsl");
	playerTexture->Init(L"..\\Resources\\Texture\\Cat.png");
	jrBalrog->Init(L"..\\Resources\\Texture\\Jr.Balrog.png");
	crimsonBalrog->Init(L"..\\Resources\\Texture\\CrimsonBalrog.png");
	attackTexture->Init(L"..\\Resources\\Texture\\Effect.png");
	fieldTexture->Init(L"..\\Resources\\Texture\\EmptyField.png");
#pragma endregion

#pragma region Player
	{
		shared_ptr<GameObject> player = make_shared<GameObject>();
		player->SetName(L"Player");
		// Transform 추가
		player->AddComponent(make_shared<Transform>());
		player->GetTransform()->SetLocalScale(Vec3(200.f, 200.f, 0.f));
		player->GetTransform()->SetLocalPosition(Vec3(-800.f, -160.f, -2.f));

		// MeshRenderer 생성
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

		shared_ptr<RectCollider2D> playerCollider = make_shared<RectCollider2D>();
		playerCollider->SetAlive();
		playerCollider->NotRender();
		shared_ptr<RigidBody2D> rigidBody2D = make_shared<RigidBody2D>();
		rigidBody2D->SetGravity(10.f);
		rigidBody2D->SetForce(1.1f);
		player->AddComponent(playerCollider);
		player->AddComponent(rigidBody2D);
		player->AddComponent(make_shared<PlayerScript>());
		scene->AddGameObject(player);

		// 플레이어의 공격 범위
		{
			shared_ptr<GameObject> playerAttack = make_shared<GameObject>();
			playerAttack->SetName(L"Attack");
			playerAttack->AddComponent(make_shared<Transform>());
			playerAttack->GetTransform()->SetLocalPosition(Vec3(0.7f, 0.f, 0.f));
			playerAttack->GetTransform()->SetParent(player->GetTransform());
			playerAttack->GetTransform()->SetLocalScale(Vec3(1.f, 0.7f, 0));
			// MeshRenderer 생성
			shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
			{ // 1. Mesh
				shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadRectMesh();
				meshRenderer->SetMesh(mesh);
			}
			{ // 2. Material
				shared_ptr<Material> material = make_shared<Material>();
				material->SetShader(defaultShader);
				material->SetTexture(0, attackTexture);
				material->SetInt(0, 1);
				meshRenderer->SetMaterial(material);
			}
			playerAttack->AddComponent(meshRenderer);
			{
				shared_ptr<RectCollider2D> attackCollider = make_shared<RectCollider2D>();
				attackCollider->SetDead();
				playerAttack->AddComponent(attackCollider);
			}
			playerAttack->AddComponent(make_shared<PlayerAttackScript>());
			playerAttack->ObjectDead();
			scene->AddGameObject(playerAttack);
		}
	}
#pragma endregion

#pragma region Jr.Balrog
	{
		shared_ptr<GameObject> gameObject = make_shared<GameObject>();
		gameObject->SetName(L"Monster");
		gameObject->SetStatus(make_shared<Status>(7.f, 7.f, 3.f));		
		// Transform 추가
		gameObject->AddComponent(make_shared<Transform>());
		gameObject->GetTransform()->SetLocalScale(Vec3(300.f, 300.f, 0.f));
		gameObject->GetTransform()->SetLocalPosition(Vec3(200.f, -200.f, -2.f));
		// MeshRenderer 생성
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{ // 1. Mesh
			shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadRectMesh();
			meshRenderer->SetMesh(mesh);
		}
		{ // 2. Material
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(defaultShader);
			material->SetTexture(0, jrBalrog);
			material->SetInt(0, 1);
			meshRenderer->SetMaterial(material);
		}
		gameObject->AddComponent(meshRenderer);
		shared_ptr<RigidBody2D> rigidBody2D = make_shared<RigidBody2D>();
		rigidBody2D->SetGravity(9.8f);
		rigidBody2D->SetForce(1.f);
		shared_ptr<RectCollider2D> collider = make_shared<RectCollider2D>();
		collider->SetAlive();
		collider->NotRender();
		gameObject->AddComponent(rigidBody2D);
		gameObject->AddComponent(collider);
		gameObject->AddComponent(make_shared<MonsterScript>());
		scene->AddGameObject(gameObject);
	}
#pragma endregion

#pragma region CrimsonBalrog
	{
		shared_ptr<GameObject> gameObject = make_shared<GameObject>();		
		gameObject->SetName(L"Monster");
		gameObject->SetStatus(make_shared<Status>(10.f, 10.f, 5.f));
		// Transform 추가
		gameObject->AddComponent(make_shared<Transform>());
		gameObject->GetTransform()->SetLocalScale(Vec3(450.f, 450.f, 0.f));
		gameObject->GetTransform()->SetLocalPosition(Vec3(700.f, 50.f, -2.f));
		// MeshRenderer 생성
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		{ // 1. Mesh
			shared_ptr<Mesh> mesh = GET_SINGLE(Resources)->LoadRectMesh();
			meshRenderer->SetMesh(mesh);
		}
		{ // 2. Material
			shared_ptr<Material> material = make_shared<Material>();
			material->SetShader(defaultShader);
			material->SetTexture(0, crimsonBalrog);
			material->SetInt(0, 1);
			meshRenderer->SetMaterial(material);
		}
		gameObject->AddComponent(meshRenderer);
		shared_ptr<RigidBody2D> rigidBody2D = make_shared<RigidBody2D>();
		rigidBody2D->SetGravity(9.8f);
		rigidBody2D->SetForce(1.f);
		shared_ptr<RectCollider2D> collider = make_shared<RectCollider2D>();
		collider->SetAlive();
		collider->NotRender();
		gameObject->AddComponent(rigidBody2D);
		gameObject->AddComponent(collider);
		gameObject->AddComponent(make_shared<MonsterScript>());
		scene->AddGameObject(gameObject);
	}
#pragma endregion

#pragma region field
	{
		shared_ptr<GameObject> fieldObject = make_shared<GameObject>();
		fieldObject->SetName(L"Field");
		// Transform 생성
		fieldObject->AddComponent(make_shared<Transform>());
		/*float height = GEngine->GetWindow().height;
		float width = GEngine->GetWindow().width;*/
		float width = static_cast<float>(GEngine->GetWindow().width) * 2.5f;
		float height = static_cast<float>(GEngine->GetWindow().height) * 2.5f;
		fieldObject->GetTransform()->SetLocalScale(Vec3(width, height, 0.f));

		// GameObject에 추가될 MeshRenderer
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

#pragma region TileMap
	// 1 floor
	{
		shared_ptr<GameObject> tileMap = make_shared<GameObject>();
		tileMap->SetName(L"Tile");
		// Transform 추가
		tileMap->AddComponent(make_shared<Transform>());
		tileMap->GetTransform()->SetLocalScale(Vec3(2000.f, 100.f, 0.f));
		tileMap->GetTransform()->SetLocalPosition(Vec3(0.f, -700.f, -2.f));

		shared_ptr<TilemapCollider> collider = make_shared<TilemapCollider>();
		collider->SetAlive();
		collider->NotRender();
		tileMap->AddComponent(collider);
		scene->AddGameObject(tileMap);
	}
#pragma endregion

#pragma region object
	{
		shared_ptr<GameObject> tileMap = make_shared<GameObject>();
		tileMap->SetName(L"Object");
		// Transform 추가
		tileMap->AddComponent(make_shared<Transform>());
		tileMap->GetTransform()->SetLocalScale(Vec3(250.f, 250.f, 0.f));
		tileMap->GetTransform()->SetLocalPosition(Vec3(-350.f, -530.f, -2.f));

		shared_ptr<TilemapCollider> collider = make_shared<TilemapCollider>();
		collider->SetAlive();
		collider->NotRender();
		tileMap->AddComponent(collider);
		scene->AddGameObject(tileMap);
	}
	{
		shared_ptr<GameObject> tileMap = make_shared<GameObject>();
		tileMap->SetName(L"Object");
		// Transform 추가
		tileMap->AddComponent(make_shared<Transform>());
		tileMap->GetTransform()->SetLocalScale(Vec3(250, 250.f, 0.f));
		tileMap->GetTransform()->SetLocalPosition(Vec3(-100.f, -530.f, -2.f));

		shared_ptr<TilemapCollider> collider = make_shared<TilemapCollider>();
		collider->SetAlive();
		collider->NotRender();
		tileMap->AddComponent(collider);
		scene->AddGameObject(tileMap);
	}
	{
		shared_ptr<GameObject> tileMap = make_shared<GameObject>();
		tileMap->SetName(L"Object");
		// Transform 추가
		tileMap->AddComponent(make_shared<Transform>());
		tileMap->GetTransform()->SetLocalScale(Vec3(250.f, 250.f, 0.f));
		tileMap->GetTransform()->SetLocalPosition(Vec3(-200.f, -330.f, -2.f));

		shared_ptr<TilemapCollider> collider = make_shared<TilemapCollider>();
		collider->SetAlive();
		collider->NotRender();
		tileMap->AddComponent(collider);
		scene->AddGameObject(tileMap);
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
