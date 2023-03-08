#include "pch.h"
#include "RigidBody2D.h"
#include "GameObject.h"
#include "Transform.h"
#include "Timer.h"

RigidBody2D::RigidBody2D() : Component(COMPONENT_TYPE::RIGID_BODY)
{
}

RigidBody2D::~RigidBody2D()
{
}

void RigidBody2D::Update()
{
	Vec3 pos = GetGameObject()->GetTransform()->GetLocalPosition();
	pos.y -= _gravityScale;
	GetGameObject()->GetTransform()->SetLocalPosition(pos);
}

void RigidBody2D::LateUpdate()
{
}

void RigidBody2D::FinalUpdate()
{
}
