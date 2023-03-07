#include "pch.h"
#include "Engine.h"
#include "PlayerScript.h"
#include "Transform.h"
#include "GameObject.h"
#include "Component.h"
#include "Input.h"
#include "Timer.h"
#include "Collider.h"
#include "RectCollider2D.h"

PlayerScript::PlayerScript() : MonoBehaviour(BEHAVIOUR_TYPE::PLAYER)
{
}

PlayerScript::~PlayerScript()
{
}

void PlayerScript::Update()
{
	Vec3 pos = GetTransform()->GetLocalPosition();

	if (INPUT->GetButton(KEY_TYPE::W))
		pos += GetTransform()->GetUp() * _speed * DELTA_TIME;
	if (INPUT->GetButton(KEY_TYPE::S))
		pos -= GetTransform()->GetUp() * _speed * DELTA_TIME;
	if (INPUT->GetButton(KEY_TYPE::A))
		pos -= GetTransform()->GetRight() * _speed * DELTA_TIME;
	if (INPUT->GetButton(KEY_TYPE::D))
		pos += GetTransform()->GetRight() * _speed * DELTA_TIME;

	if (INPUT->GetButton(KEY_TYPE::Q))
	{
		GetGameObject()->GetCollider()->SetAlive();
	}
	if (INPUT->GetButton(KEY_TYPE::E))
	{
		GetGameObject()->GetCollider()->SetDead();
	}

	GetTransform()->SetLocalPosition(pos);
}


