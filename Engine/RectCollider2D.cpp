#include "pch.h"
#include "Engine.h"
#include "RectCollider2D.h"
#include "Transform.h"
#include "GameObject.h"
#include "Component.h"
#include "Resources.h"
#include "Mesh.h"
#include "Material.h"
#include "Input.h"

RectCollider2D::RectCollider2D() : Collider(COLLIDER_TYPE::RECT_COLLIDER_2D)
{
	_mesh = GET_SINGLE(Resources)->LoadColliderMesh();

	shared_ptr<Shader> shader = make_shared<Shader>();
	shared_ptr<Texture> texture = make_shared<Texture>();
	shader->Init(L"..\\Resources\\Shader\\collider.hlsl", TOPOLOGY_TYPE::LINE);
	texture->Init(L"..\\Resources\\Texture\\rapi.jpg");
	_material->SetShader(shader);
	_material->SetTexture(0, texture);
	_material->SetInt(0, 1);		
	_material->SetVec4(_baseColor);
}

RectCollider2D::~RectCollider2D()
{

}

void RectCollider2D::Update()
{
	if(IsAlive())
		Render();
}

void RectCollider2D::LateUpdate()
{
	if (IsAlive())
	{
		if (INPUT->GetButton(KEY_TYPE::Q))
			_material->SetVec4(_collidedColor);
		if (INPUT->GetButton(KEY_TYPE::E))
			_material->SetVec4(_baseColor);
	}	
}

void RectCollider2D::FinalUpdate()
{		
}

void RectCollider2D::Render()
{	
	if (IsAlive())
	{
		GetTransform()->PushData();
		_material->Update();
		_mesh->Render(MESH_TYPE::LINESTRIP_MESH);
	}
}

void RectCollider2D::Render(weak_ptr<Transform> position)
{
	if (IsAlive())
	{
		position.lock()->PushData();
		_material->Update();
		_mesh->Render(MESH_TYPE::LINESTRIP_MESH);
	}
}

void RectCollider2D::CollidedColor()
{
	_material->SetVec4(_collidedColor);
}

void RectCollider2D::BaseColor()
{
	_material->SetVec4(_baseColor);
}

bool RectCollider2D::AABB(Transform& world1, Transform& world2)
{	
	// �� ��ü�� ��ġ
	Vec2 position1;
	position1.x = world1.GetLocalPosition().x;
	position1.y = world1.GetLocalPosition().y;
	Vec2 position2;
	position2.x = world2.GetLocalPosition().x;
	position2.y = world2.GetLocalPosition().y;

	// �� ��ü�� x, y�� ������ ũ��
	Vec2 scale1;
	scale1.x = world1.GetLocalScale().x;
	scale1.y = world1.GetLocalScale().y;
	Vec2 scale2;
	scale2.x = world2.GetLocalScale().x;
	scale2.y = world2.GetLocalScale().y;

	// �� ��ü ������ �� �࿡���� �Ÿ�
	Vec2 distance;
	distance.x = fabsf(position1.x - position2.x);
	distance.y = fabsf(position1.y - position2.y);

	// �� ��ü�� x, y���� ũ���� ����
	Vec2 halfDistance1, halfDistance2;
	halfDistance1 = Vec2(fabsf(scale1.x), fabsf(scale1.y)) * 0.5f;
	halfDistance2 = Vec2(fabsf(scale2.x), fabsf(scale2.y)) * 0.5f;

	// �� �࿡�� ��ü ������ �Ÿ��� �� ��ü�� ũ���� ������ ���Ѱͺ��� ũ�ٸ�
	// �� ��ü�� ��ġ�� �ʾҴ�.
	if (distance.x > halfDistance1.x + halfDistance2.x)
		return false;
	if (distance.y > halfDistance1.y + halfDistance2.y)
		return false;

	// ������ �ɷ����� �ʾҴٸ� �� ��ü�� �浹�� �����̴�
	return true;
}
