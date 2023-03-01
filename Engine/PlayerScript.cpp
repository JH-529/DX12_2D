#include "pch.h"
#include "Engine.h"
#include "PlayerScript.h"
#include "Transform.h"
#include "GameObject.h"
#include "Component.h"
#include "Input.h"
#include "Timer.h"

PlayerScript::PlayerScript() : MonoBehaviour(BEHAVIOUR_TYPE::PLAYER)
{
}

PlayerScript::~PlayerScript()
{
}

void PlayerScript::Update()
{
	shared_ptr<Transform> t = GetTransform();

	if (INPUT->GetButton(KEY_TYPE::W))
		t->SetTransformY(1.f * DELTA_TIME);
	if (INPUT->GetButton(KEY_TYPE::S))
		t->SetTransformY(-(1.f * DELTA_TIME));
	if (INPUT->GetButton(KEY_TYPE::A))
		t->SetTransformX(-(1.f * DELTA_TIME));
	if (INPUT->GetButton(KEY_TYPE::D))
		t->SetTransformX(1.f * DELTA_TIME);	
}
