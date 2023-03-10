#include "pch.h"
#include "RigidBody2D.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "RectCollider2D.h"
#include "Timer.h"

// Transform()�� COMPONENT_TYPE::RIGID_BODY�� ���� �������
// RigidBody2D�� �� Object�� �������۵�
RigidBody2D::RigidBody2D() : Transform(COMPONENT_TYPE::RIGID_BODY)
{
}

RigidBody2D::~RigidBody2D()
{
}

void RigidBody2D::Awake()
{
	_transform = GetGameObject()->GetTransform();
}

void RigidBody2D::Update()
{
	// Collision ���� �پ�ȭ(�ش� Collision�� �׳� AABB�浹�� ó��) �ʿ�
	if (Collision())
	{
		return;
	}

	Vec3 pos = GetGameObject()->GetTransform()->GetLocalPosition();

	pos.y -= _gravity;
	GetGameObject()->GetTransform()->SetLocalPosition(pos);
}

void RigidBody2D::LateUpdate()
{
}

void RigidBody2D::FinalUpdate()
{
}

bool RigidBody2D::Collision()
{
	// RigidBody2D�� ���� �ִ� GameObject�� ���� Scene�� �ִ�
	// Collider�� �����ϰ� �ִ� ��� GameObject���� ������
	shared_ptr<Scene> scene = GetGameObject()->GetScene();
	vector<shared_ptr<GameObject>> gameObjects = scene->GetColliderObjects();

	for (auto& gameObject : gameObjects)
	{
		if (BottomCollision(*_transform, *gameObject->GetTransform()))
		{
			return true;
		}
	}

	return false;
}

// object1�� �ٴڸ��� object2�� ����� �浹�Ͽ����� �Ǵ�
bool RigidBody2D::BottomCollision(Transform& object1, Transform& object2)
{
	// �� ��ü�� ��ġ
	Vec2 position1;
	position1.x = object1.GetLocalPosition().x;
	position1.y = object1.GetLocalPosition().y;
	Vec2 position2;			 
	position2.x = object2.GetLocalPosition().x;
	position2.y = object2.GetLocalPosition().y;

	// �� ��ü�� x, y�� ������ ũ��
	Vec2 scale1;
	scale1.x = object1.GetLocalScale().x;
	scale1.y = object1.GetLocalScale().y;
	Vec2 scale2;		  
	scale2.x = object2.GetLocalScale().x;
	scale2.y = object2.GetLocalScale().y;

	// �� ��ü�� x, y���� ũ���� ����
	Vec2 halfDistance1, halfDistance2;
	halfDistance1 = Vec2(fabsf(scale1.x), fabsf(scale1.y)) * 0.5f;
	halfDistance2 = Vec2(fabsf(scale2.x), fabsf(scale2.y)) * 0.5f;

	// object1�� �Ʒ� ���� ����ϴ� �ΰ��� Vertex�� position
	Vec2 object1_Vertex1;
	object1_Vertex1.x = position1.x - halfDistance1.x;
	object1_Vertex1.y = position1.y - halfDistance1.y;
	Vec2 object1_Vertex2;
	object1_Vertex2.x = position1.x + halfDistance1.x;
	object1_Vertex2.y = position1.y - halfDistance1.y;

	// object2�� ������ ����ϴ� �ΰ��� Vertex�� position
	Vec2 object2_Vertex1;
	object2_Vertex1.x = position2.x - halfDistance2.x;
	object2_Vertex1.y = position2.y + halfDistance2.y;
	Vec2 object2_Vertex2;						  
	object2_Vertex2.x = position2.x + halfDistance2.x;
	object2_Vertex2.y = position2.y + halfDistance2.y;

	// object1�� �Ʒ����� �糡 ������ x��, object2�� ������ �糡 ������ x���� ��(3���� ���)
	// ���� �񱳸� ���� object2�� ���� object1�� ��ġ�ϴ��� �Ǵ�
	// ���� object1�� �Ʒ����� y���� object2�� ������ y�� - �߷����� ũ�� ~ object2�� ������ y��
	// ���̿� �������� ���� object1�� object2�� ������ �浹�� �������� �Ǵ�(�׸�����)
	if ((object1_Vertex1.x > object2_Vertex1.x && object1_Vertex1.x < object2_Vertex2.x) ||
		(object1_Vertex2.x > object2_Vertex1.x && object1_Vertex2.x < object2_Vertex2.x) ||
		(object1_Vertex1.x < object2_Vertex1.x && object1_Vertex2.x > object2_Vertex2.x))
	{
		if ((object1_Vertex1.y <= object2_Vertex1.y) && 
			(object2_Vertex1.y - _gravity * 1.f <= object1_Vertex1.y))
		{			
			return true;
		}
	}

	return false;
}

// object1�� ������ object2�� ����� �浹�Ͽ����� �Ǵ�
bool RigidBody2D::SideCollision(Transform& object1, Transform& object2)
{
	// �� ��ü�� ��ġ
	Vec2 position1;
	position1.x = object1.GetLocalPosition().x;
	position1.y = object1.GetLocalPosition().y;
	Vec2 position2;
	position2.x = object2.GetLocalPosition().x;
	position2.y = object2.GetLocalPosition().y;

	// �� ��ü�� x, y�� ������ ũ��
	Vec2 scale1;
	scale1.x = object1.GetLocalScale().x;
	scale1.y = object1.GetLocalScale().y;
	Vec2 scale2;
	scale2.x = object2.GetLocalScale().x;
	scale2.y = object2.GetLocalScale().y;

	// �� ��ü�� x, y���� ũ���� ����
	Vec2 halfDistance1, halfDistance2;
	halfDistance1 = Vec2(fabsf(scale1.x), fabsf(scale1.y)) * 0.5f;
	halfDistance2 = Vec2(fabsf(scale2.x), fabsf(scale2.y)) * 0.5f;

	// object1�� 4���� Vertex
	// 1 2
	// 3 4
	Vec2 object1_Vertex1;
	object1_Vertex1.x = position1.x - halfDistance1.x;
	object1_Vertex1.y = position1.y + halfDistance1.y;
	Vec2 object1_Vertex2;
	object1_Vertex2.x = position1.x + halfDistance1.x;
	object1_Vertex2.y = position1.y + halfDistance1.y;
	Vec2 object1_Vertex3;
	object1_Vertex3.x = position1.x - halfDistance1.x;
	object1_Vertex3.y = position1.y - halfDistance1.y;
	Vec2 object1_Vertex4;
	object1_Vertex4.x = position1.x + halfDistance1.x;
	object1_Vertex4.y = position1.y - halfDistance1.y;

	// object2�� 4���� Vertex
	// 1 2
	// 3 4
	Vec2 object2_Vertex1;
	object2_Vertex1.x = position2.x - halfDistance2.x;
	object2_Vertex1.y = position2.y + halfDistance2.y;
	Vec2 object2_Vertex2;
	object2_Vertex2.x = position2.x + halfDistance2.x;
	object2_Vertex2.y = position2.y + halfDistance2.y;
	Vec2 object2_Vertex3;
	object2_Vertex3.x = position2.x - halfDistance2.x;
	object2_Vertex3.y = position2.y - halfDistance2.y;
	Vec2 object2_Vertex4;
	object2_Vertex4.x = position2.x + halfDistance2.x;
	object2_Vertex4.y = position2.y - halfDistance2.y;

	// object1�� ����, object2�� ������ �浹 �Ǵ�
	

	return false;
}

