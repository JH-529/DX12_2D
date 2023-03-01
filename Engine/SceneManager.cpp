#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Engine.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "Camera.h"

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

// 인자로 들어온 type에 해당하는 Scene을 _activeScene으로 설정
void SceneManager::LoadScene(SCENE_TYPE type)
{
	// TODO : 기존 Scene 정리
	// TODO : 파일에서 Scene 정보 로드

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

	shared_ptr<Mesh> mesh = make_shared<Mesh>();
	shared_ptr<Mesh> meshField = make_shared<Mesh>();
	shared_ptr<GameObject> field = make_shared<GameObject>();

	shared_ptr<Shader> shader = make_shared<Shader>();
	shared_ptr<Texture> texture = make_shared<Texture>();
	shared_ptr<Texture> texture2 = make_shared<Texture>();
	shared_ptr<Texture> fieldTexture = make_shared<Texture>();
	shader->Init(L"..\\Resources\\Shader\\default.hlsl");
	texture->Init(L"..\\Resources\\Texture\\anis2.jpg");
	texture2->Init(L"..\\Resources\\Texture\\rapi.jpg");
	fieldTexture->Init(L"..\\Resources\\Texture\\field.png");

#pragma region Rect
	{
		shared_ptr<GameObject> gameObject = make_shared<GameObject>();

		vector<Vertex> vec(4);
		vec[0].pos = Vec3(-0.5f, 0.5f, FIELD_DEPTH - 0.5f);
		vec[0].color = Vec4(1.f, 0.f, 0.f, 1.f);
		vec[0].uv = Vec2(0.f, 0.f);
		vec[1].pos = Vec3(0.5f, 0.5f, FIELD_DEPTH - 0.5f);
		vec[1].color = Vec4(0.f, 1.f, 0.f, 1.f);
		vec[1].uv = Vec2(1.f, 0.f);
		vec[2].pos = Vec3(0.5f, -0.5f, FIELD_DEPTH - 0.5f);
		vec[2].color = Vec4(0.f, 0.f, 1.f, 1.f);
		vec[2].uv = Vec2(1.f, 1.f);
		vec[3].pos = Vec3(-0.5f, -0.5f, FIELD_DEPTH - 0.5f);
		vec[3].color = Vec4(0.f, 1.f, 0.f, 1.f);
		vec[3].uv = Vec2(0.f, 1.f);

		vector<uint32> indexVec;
		{
			indexVec.push_back(0);
			indexVec.push_back(1);
			indexVec.push_back(2);
		}
		{
			indexVec.push_back(0);
			indexVec.push_back(2);
			indexVec.push_back(3);
		}

		mesh->Init(vec, indexVec);

		// Transform 추가
		gameObject->AddComponent(make_shared<Transform>());
		gameObject->GetTransform()->SetLocalScale(Vec3(170.f, 170.f, 0.f));
		gameObject->GetTransform()->SetLocalPosition(Vec3(-280.f, -160.f, -2.f));

		// MeshRenderer 생성
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		meshRenderer->SetMesh(mesh);

		// Material 설정
		shared_ptr<Material> material = make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(0, texture);
		material->SetInt(0, 1);
		meshRenderer->SetMaterial(material);
				
		gameObject->AddComponent(make_shared<PlayerScript>());
		gameObject->AddComponent(meshRenderer);		
		scene->AddGameObject(gameObject);
	}
#pragma endregion

#pragma region Rect2
	{
		shared_ptr<GameObject> gameObject2 = make_shared<GameObject>();

		vector<Vertex> vec(4);
		vec[0].pos = Vec3(-0.5f, 0.5f, FIELD_DEPTH - 0.5f);
		vec[0].color = Vec4(1.f, 0.f, 0.f, 1.f);
		vec[0].uv = Vec2(0.f, 0.f);
		vec[1].pos = Vec3(0.5f, 0.5f, FIELD_DEPTH - 0.5f);
		vec[1].color = Vec4(0.f, 1.f, 0.f, 1.f);
		vec[1].uv = Vec2(1.f, 0.f);
		vec[2].pos = Vec3(0.5f, -0.5f, FIELD_DEPTH - 0.5f);
		vec[2].color = Vec4(0.f, 0.f, 1.f, 1.f);
		vec[2].uv = Vec2(1.f, 1.f);
		vec[3].pos = Vec3(-0.5f, -0.5f, FIELD_DEPTH - 0.5f);
		vec[3].color = Vec4(0.f, 1.f, 0.f, 1.f);
		vec[3].uv = Vec2(0.f, 1.f);

		vector<uint32> indexVec;
		{
			indexVec.push_back(0);
			indexVec.push_back(1);
			indexVec.push_back(2);
		}
		{
			indexVec.push_back(0);
			indexVec.push_back(2);
			indexVec.push_back(3);
		}

		mesh->Init(vec, indexVec);

		// Transform 추가
		gameObject2->AddComponent(make_shared<Transform>());
		gameObject2->GetTransform()->SetLocalScale(Vec3(100.f, 100.f, 0.f));
		gameObject2->GetTransform()->SetLocalPosition(Vec3(300.f, -110.f, -2.f));

		// MeshRenderer 생성
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		meshRenderer->SetMesh(mesh);

		// Material 생성
		shared_ptr<Material> material = make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(0, texture2);
		material->SetInt(0, 1);
		meshRenderer->SetMaterial(material);
			
		gameObject2->AddComponent(meshRenderer);
		scene->AddGameObject(gameObject2);
	}
#pragma endregion

#pragma region field
	{
		vector<Vertex> vec2(4);
		vec2[0].pos = Vec3(-1.f, 1.f, FIELD_DEPTH);
		vec2[0].color = Vec4(1.f, 0.f, 0.f, 1.f);
		vec2[0].uv = Vec2(0.f, 0.f);
		vec2[1].pos = Vec3(1.f, 1.f, FIELD_DEPTH);
		vec2[1].color = Vec4(0.f, 1.f, 0.f, 1.f);
		vec2[1].uv = Vec2(1.f, 0.f);
		vec2[2].pos = Vec3(-1.f, -1.f, FIELD_DEPTH);
		vec2[2].color = Vec4(0.f, 0.f, 1.f, 1.f);
		vec2[2].uv = Vec2(0.f, 1.f);
		vec2[3].pos = Vec3(1.f, -1.f, FIELD_DEPTH);
		vec2[3].color = Vec4(0.f, 1.f, 0.f, 1.f);
		vec2[3].uv = Vec2(1.f, 1.f);

		vector<uint32> indexVec2;
		{
			indexVec2.push_back(0);
			indexVec2.push_back(1);
			indexVec2.push_back(3);
		}
		{
			indexVec2.push_back(0);
			indexVec2.push_back(3);
			indexVec2.push_back(2);
		}
		// Mesh 생성
		meshField->Init(vec2, indexVec2);

		// Transform 생성
		field->AddComponent(make_shared<Transform>());
		float height = GEngine->GetWindow().height;
		float width = GEngine->GetWindow().width;
		field->GetTransform()->SetLocalScale(Vec3(width/2, height/2, 0.f));

		// GameObject에 추가될 MeshRenderer
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		meshRenderer->SetMesh(meshField);

		// MeshRenderer에 추가될 Material
		shared_ptr<Material> material = make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(0, fieldTexture);
		material->SetInt(0, 1);
		meshRenderer->SetMaterial(material);

		field->AddComponent(meshRenderer);
		scene->AddGameObject(field);
	}
#pragma endregion

#pragma region Camera
	{
		shared_ptr<GameObject> camera = make_shared<GameObject>();
		camera->AddComponent(make_shared<Transform>());
		camera->AddComponent(make_shared<Camera>());		
		camera->AddComponent(make_shared<CameraScript>());
		camera->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, -700.f));
		scene->AddGameObject(camera);
	}
#pragma endregion

	_scene.push_back(scene);
}