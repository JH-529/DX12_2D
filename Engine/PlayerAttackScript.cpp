#include "pch.h"
#include "PlayerScript.h"
#include "PlayerAttackScript.h"
#include "GameObject.h"
#include "Collider.h"
#include "RectCollider2D.h"
#include "Input.h"
#include "Timer.h"

PlayerAttackScript::PlayerAttackScript() : MonoBehaviour(BEHAVIOUR_TYPE::ATTACK)
{
}

PlayerAttackScript::~PlayerAttackScript()
{
}

void PlayerAttackScript::Update()
{	
	GetGameObject()->ObjectDead();
	GetGameObject()->GetCollider()->SetDead();
	
	if (INPUT->GetButtonDown(KEY_TYPE::J))
	{
		GetGameObject()->ObjectAlive();
		GetGameObject()->GetCollider()->SetAlive();
	}		
}
