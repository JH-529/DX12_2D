#pragma once
#include "Component.h"

class Transform;
class RectCollider2D;

class Attack : public Component
{
public:
	Attack();
	virtual ~Attack();

	virtual void Update();
	virtual void LateUpdate();
	virtual void FinalUpdate();

	void Render();

private:
	shared_ptr<Transform>		_position;
	shared_ptr<RectCollider2D>	_collider;

	Vec3 _localPosition = {};
	Vec3 _localScale = Vec3(100.f, 100.f, 0.f);

};

