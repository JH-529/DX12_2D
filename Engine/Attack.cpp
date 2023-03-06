#include "pch.h"
#include "Attack.h"
#include "Transform.h"
#include "RectCollider2D.h"

Attack::Attack() : Component(COMPONENT_TYPE::ATTACK)
{
	_collider = make_shared<RectCollider2D>();
}

Attack::~Attack()
{
}

void Attack::Update()
{
	_position = GetTransform();
	_localPosition = _position->GetLocalPosition();
}

void Attack::LateUpdate()
{
	if (_position->GetRight().x > 0)
		_localPosition.x += 2.f;
	else
		_localPosition.x -= 2.f;

	_position->SetLocalPosition(_localPosition);
}

void Attack::FinalUpdate()
{
	_collider->Render(*_position);
}

void Attack::Render()
{
}
