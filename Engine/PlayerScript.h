#pragma once
#include "MonoBehaviour.h"


class PlayerScript : public MonoBehaviour
{
public:
	PlayerScript();
	virtual ~PlayerScript();

	float GetSpeed() { return _speed; }

	void Start() override;
	void Update() override;

private:
	shared_ptr<class RigidBody2D>	_rigidBody2D;
	float							_speed = 5.f;

};

