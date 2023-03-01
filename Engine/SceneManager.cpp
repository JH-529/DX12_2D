#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

#include "Engine.h"
#include "Material.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "Transform.h"
#include "PlayerScript.h"

void SceneManager::Update()
{
	if (_activeScene == nullptr)
		return;

	_activeScene->Update();
	_activeScene->LateUpdate();
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
		gameObject->Init();

		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		meshRenderer->SetMesh(mesh);

		shared_ptr<Material> material = make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(0, texture);
		material->SetInt(0, 1);
		meshRenderer->SetMaterial(material);

		shared_ptr<PlayerScript> playerScript = make_shared<PlayerScript>();
		gameObject->GetTransform()->SetTransform(Vec4(-0.5f, -0.5f, -0.2f, 0.f));

		gameObject->AddComponent(meshRenderer);
		gameObject->AddComponent(playerScript);
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
		gameObject2->Init();

		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		meshRenderer->SetMesh(mesh);

		shared_ptr<Material> material = make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(0, texture2);
		material->SetInt(0, 1);
		meshRenderer->SetMaterial(material);

		gameObject2->GetTransform()->SetTransform(Vec4(0.5f, 0.5f, 0.f, 0.f));

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
		// Mesh ����
		meshField->Init(vec2, indexVec2);

		// GameObject �ʱ�ȭ(Transform Component �߰�)
		field->Init();

		// GameObject�� �߰��� MeshRenderer
		shared_ptr<MeshRenderer> meshRenderer = make_shared<MeshRenderer>();
		meshRenderer->SetMesh(meshField);

		// MeshRenderer�� �߰��� Material
		shared_ptr<Material> material = make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(0, fieldTexture);
		material->SetInt(0, 1);
		meshRenderer->SetMaterial(material);

		field->AddComponent(meshRenderer);
		scene->AddGameObject(field);
	}
#pragma endregion

	_scene.push_back(scene);
}