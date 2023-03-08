#pragma once
#include "MonoBehaviour.h"

class GameObject;
class Transform;

class CameraScript : public MonoBehaviour
{
public:
	CameraScript();
	virtual ~CameraScript();

	void Update() override;
	void LateUpdate() override;

private:
	float		_speed = 100.f;
	shared_ptr<GameObject> _player;
	shared_ptr<GameObject> _field;

	shared_ptr<Transform> _playerTransform;
	shared_ptr<Transform> _fieldTransform;

	array<Vec3, 4> _cameraVertex;
	array<Vec3, 4> _fieldVertex;
};

