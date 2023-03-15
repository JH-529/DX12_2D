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
#include "RigidBody2D.h"
#include "Physics2D.h"
#include "Debug.h"

PlayerScript::PlayerScript() : MonoBehaviour(BEHAVIOUR_TYPE::PLAYER)
{
}

PlayerScript::~PlayerScript()
{
}

void PlayerScript::Update()
{
	Vec3 pos = GetTransform()->GetLocalPosition();
	shared_ptr<GameObject> player = GetGameObject();

	// force, mass�� �Ʒ� ��ȣ�ۿ��� RigidBody2D����
	// AddForce()�޼��带 ���� ����Ǿ����
	float force = player->GetRigidBody2D()->GetForce();
	float mass = player->GetRigidBody2D()->GetMass();
	float jumpPower = force - mass;

	if (jumpPower <= 0)
	{
		jumpPower = 0.1f;
	}
	
	if (INPUT->GetButton(KEY_TYPE::SPACE))
		pos += GetTransform()->GetUp() * jumpPower;
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

	// RayCast ���� Debuging��
	// *********�������� ����*********
	/*Vec2 rayPos = Vec2(pos.x, pos.y);
	Vec2 dir = Vec2(0.f, -1.f);
	float dis = 3.f;
	Debug::DrawRay2D(rayPos, dir, dis*10.f);
	RayCastHit2D rayHit = Physics2D::RayCast(rayPos, dir, dis);

	if (rayHit._collider != nullptr)
	{
		rayHit._collider->GetGameObject()->GetRectCollider2D()->CollidedColor();
	}*/
}


