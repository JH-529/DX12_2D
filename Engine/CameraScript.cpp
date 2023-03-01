#include "pch.h"
#include "CameraScript.h"
#include "Engine.h"
#include "Transform.h"
#include "GameObject.h"
#include "Component.h"
#include "Input.h"
#include "Timer.h"

CameraScript::CameraScript() : MonoBehaviour(BEHAVIOUR_TYPE::CAMERA)
{
}

CameraScript::~CameraScript()
{
}

void CameraScript::Update()
{
	Vec3 pos = GetTransform()->GetLocalPosition();

	if (INPUT->GetButton(KEY_TYPE::UP))
		pos += GetTransform()->GetUp() * _speed * DELTA_TIME;
	if (INPUT->GetButton(KEY_TYPE::DOWN))
		pos -= GetTransform()->GetUp() * _speed * DELTA_TIME;
	if (INPUT->GetButton(KEY_TYPE::LEFT))
		pos -= GetTransform()->GetRight() * _speed * DELTA_TIME;
	if (INPUT->GetButton(KEY_TYPE::RIGHT))
		pos += GetTransform()->GetRight() * _speed * DELTA_TIME;

	GetTransform()->SetLocalPosition(pos);
}
