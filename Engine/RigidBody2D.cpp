#include "pch.h"
#include "RigidBody2D.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "RectCollider2D.h"
#include "Timer.h"

// Transform()에 COMPONENT_TYPE::RIGID_BODY를 넣지 않을경우
// RigidBody2D가 들어간 Object가 비정상작동
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
	// Collision 형태 다양화(해당 Collision은 그냥 AABB충돌만 처리) 필요
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
	// RigidBody2D를 갖고 있는 GameObject가 속한 Scene에 있는
	// Collider를 포함하고 있는 모든 GameObject들을 가져옴
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