#pragma once
#include "MonoBehaviour.h"


class PlayerScript : public MonoBehaviour
{
public:
	PlayerScript();
	virtual ~PlayerScript();

	float GetSpeed() { return _speed; }
	void Update() override;

private:
	float						_speed = 5.f;

};

