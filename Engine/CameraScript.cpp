#include "pch.h"
#include "CameraScript.h"
#include "Engine.h"
#include "Transform.h"
#include "GameObject.h"
#include "Component.h"
#include "Scene.h"
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

void CameraScript::LateUpdate()
{	
	_player = GetGameObject()->GetScene()->GetPlayer();
	_field = GetGameObject()->GetScene()->GetField();
	
	if (_player && _field)
	{
		_playerTransform = _player->GetTransform();
		_fieldTransform = _field->GetTransform();
	}
	else
		return;

	Vec3 playerPos = _playerTransform->GetLocalPosition();
	Vec3 fieldPos = _fieldTransform->GetLocalPosition();
	Vec3 fieldScale = _fieldTransform->GetLocalScale();
	Vec3 cameraPos = playerPos;
	
	float width = static_cast<float>(GEngine->GetWindow().width);
	float height = static_cast<float>(GEngine->GetWindow().height);

	if ((cameraPos.x - width / 2) < (fieldPos.x - fieldScale.x / 2))
	{
		cameraPos.x = (fieldPos.x - fieldScale.x / 2) + width / 2;
	}
	if ((cameraPos.x + width / 2) > (fieldPos.x + fieldScale.x / 2))
	{
		cameraPos.x = (fieldPos.x + fieldScale.x / 2) - width / 2;
	}
	if ((cameraPos.y - height / 2) < (fieldPos.y - fieldScale.y / 2))
	{
		cameraPos.y = (fieldPos.y - fieldScale.y / 2) + height / 2;
	}
	if ((cameraPos.y + height / 2) > (fieldPos.y + fieldScale.y / 2))
	{
		cameraPos.y = (fieldPos.y + fieldScale.y / 2) - height / 2;
	}

	cameraPos.z = -100.f;
	GetTransform()->SetLocalPosition(cameraPos);
}
