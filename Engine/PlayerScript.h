#pragma once
#include "MonoBehaviour.h"

class Collider;
class RectCollider2D;

class PlayerScript : public MonoBehaviour
{
public:
	PlayerScript();
	virtual ~PlayerScript();

	void Update() override;

	void OnTrigger(shared_ptr<RectCollider2D> collider);

private:
	float						_speed = 5.f;

	shared_ptr<RectCollider2D>	_rectCollider;
};

