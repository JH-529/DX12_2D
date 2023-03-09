#include "pch.h"
#include "TilemapCollider.h"
#include "RectCollider2D.h"
#include "Transform.h"
#include "Resources.h"
#include "Shader.h"
#include "Texture.h"
#include "Input.h"

TilemapCollider::TilemapCollider() : Collider(COLLIDER_TYPE::TILEMAP_COLLIDER)
{
	_mesh = make_shared<Mesh>();
	_mesh = GET_SINGLE(Resources)->LoadColliderMesh();

	_material = make_shared<Material>();
	shared_ptr<Shader> shader = make_shared<Shader>();
	shared_ptr<Texture> texture = make_shared<Texture>();
	shader->Init(L"..\\Resources\\Shader\\collider.hlsl", TOPOLOGY_TYPE::LINE);
	_material->SetShader(shader);
	_material->SetVec4(_baseColor);
	_material->SetInt(0, 1);
	_material->SetVec4(_baseColor);
}

TilemapCollider::TilemapCollider(weak_ptr<Transform> transform) : Collider(COLLIDER_TYPE::TILEMAP_COLLIDER)
{
	_transform = transform.lock();

	_mesh = make_shared<Mesh>();
	_mesh = GET_SINGLE(Resources)->LoadColliderMesh();

	_material = make_shared<Material>();
	shared_ptr<Shader> shader = make_shared<Shader>();
	shared_ptr<Texture> texture = make_shared<Texture>();
	shader->Init(L"..\\Resources\\Shader\\collider.hlsl", TOPOLOGY_TYPE::LINE);
	_material->SetShader(shader);
	_material->SetVec4(_baseColor);
	_material->SetInt(0, 1);
	_material->SetVec4(_baseColor);
}

TilemapCollider::~TilemapCollider()
{
}

void TilemapCollider::Update()
{
	Render();
}

void TilemapCollider::LateUpdate()
{
	if (IsAlive())
	{
		if (INPUT->GetButton(KEY_TYPE::Q))
			_material->SetVec4(_collidedColor);
		if (INPUT->GetButton(KEY_TYPE::E))
			_material->SetVec4(_baseColor);
	}
}

void TilemapCollider::FinalUpdate()
{

}

void TilemapCollider::Render()
{
	if (_transform == nullptr)
	{
		GetTransform()->PushData();
		_material->Update();
		_mesh->Render(MESH_TYPE::LINESTRIP_MESH);
	}
	else
	{
		_transform->PushData();
		_material->Update();
		_mesh->Render(MESH_TYPE::LINESTRIP_MESH);
	}
}

bool TilemapCollider::AABB(Transform& world1, Transform& world2)
{
	return RectCollider2D::AABB(world1, world2);
}