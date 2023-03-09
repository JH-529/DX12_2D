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
	_material->SetShader(shader);	
	_material->SetInt(0, 1);		
	_material->SetVec4(_baseColor);
}

RectCollider2D::~RectCollider2D()
{

}

void RectCollider2D::Update()
{	
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
	GetTransform()->PushData();
	_material->Update();
	_mesh->Render(MESH_TYPE::LINESTRIP_MESH);	
}

void RectCollider2D::Render(weak_ptr<Transform> position)
{		
	position.lock()->PushData();
	_material->Update();
	_mesh->Render(MESH_TYPE::LINESTRIP_MESH);	
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
	position1.x = world1.GetWorldPosition().x;
	position1.y = world1.GetWorldPosition().y;
	Vec2 position2;
	position2.x = world2.GetWorldPosition().x;
	position2.y = world2.GetWorldPosition().y;

	// �� ��ü�� x, y�� ������ ũ��
	Vec2 scale1;
	scale1.x = world1.GetWorldScale().x;
	scale1.y = world1.GetWorldScale().y;
	Vec2 scale2;
	scale2.x = world2.GetWorldScale().x;
	scale2.y = world2.GetWorldScale().y;

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

bool RectCollider2D::RayCastRect(Ray& ray, Transform& object)
{
	// Ray�� ���� ���� ���� ���ϱ�
	Vec2 rayPosition;
	rayPosition = ray.pos;
	Vec2 rayDir;
	rayDir = ray.dir;
	float rayScale;
	rayScale = ray.distance;

	// ratio^2 = d^2 / pos.x^2 + pos.y^2
	float ratio = 0.f;	
	ratio = sqrt(pow(rayScale, 2) / (pow(rayDir.x, 2) + pow(rayDir.y, 2)));
	Vec2 rayEnd = Vec2(rayPosition.x + rayDir.x * ratio, rayPosition.y + rayDir.y * ratio);

	// ������ ���� Ray�� �浹 ���θ� �Ǵ��� Object�� Position, Scale
	Vec2 objectPosition;
	objectPosition.x = object.GetWorldPosition().x;
	objectPosition.y = object.GetWorldPosition().y;
	Vec2 objectScale;
	objectScale.x = object.GetWorldScale().x;
	objectScale.y = object.GetWorldScale().y;

	// Ray�� �� ������ Object�� �� �������� ���Ͽ� Ray�� Object������ �浹 üũ
	if ((rayEnd.x > objectPosition.x - objectScale.x / 2) && (rayEnd.x < objectPosition.x + objectScale.x / 2) &&
		(rayEnd.y > objectPosition.y - objectScale.y / 2) && (rayEnd.y < objectPosition.y + objectScale.y / 2))
	{
		return true;
	}
	if ((rayPosition.x > objectPosition.x - objectScale.x / 2) && (rayPosition.x < objectPosition.x + objectScale.x / 2) &&
		(rayPosition.y > objectPosition.y - objectScale.y / 2) && (rayPosition.y < objectPosition.y + objectScale.y / 2))
	{
		return true;
	}

	return false;
}