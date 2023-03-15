#include "pch.h"
#include "MonsterScript.h"
#include "GameObject.h"
#include "Collider.h"


MonsterScript::MonsterScript() : MonoBehaviour(BEHAVIOUR_TYPE::MONSTER)
{
}

MonsterScript::~MonsterScript()
{
}

void MonsterScript::Update()
{
	if (GetGameObject()->GetStatus()->GetHp() <= 0)
	{
		GetGameObject()->ObjectDead();
		GetGameObject()->GetCollider()->SetDead();
	}
}
