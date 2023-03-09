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
		if (RectCollider2D::AABB(*_transform, *gameObject->GetTransform()))
		{
			return true;
		}
	}

	return false;
}