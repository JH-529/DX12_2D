#include "pch.h"
#include "Attack.h"
#include "Transform.h"
#include "RectCollider2D.h"

Attack::Attack() : Component(COMPONENT_TYPE::ATTACK)
{
	_collider = make_shared<RectCollider2D>();
	_position = make_shared<Transform>();
}

Attack::~Attack()
{
}

void Attack::Update()
{
	_localPosition = GetTransform()->GetLocalPosition();
	_localRotation = GetTransform()->GetLocalRotation();

	_localPosition.x += 10;
	_position->SetParent(GetTransform());
}

void Attack::LateUpdate()
{
	_position->SetLocalPosition(_localPosition);
	_position->SetLocalRotation(_localRotation);
	_position->SetLocalScale(_localScale);
}

void Attack::FinalUpdate()
{	
	Render();
}

void Attack::Render()
{
	_collider->Render(_position);
}
