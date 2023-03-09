#pragma once
#include "Component.h"

enum class RIGID_BODY_TYPE : uint8
{
	NONE,
	DYNAMIC,
	STATIC,
	KINEMATIC,
	END,
};

class RigidBody2D : public Component
{
public:
	RigidBody2D();
	virtual ~RigidBody2D();

	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FinalUpdate() override;

	void SetMass(float value) { _mass = value; }
	void SetGravity(float value) { _gravityScale = value; }

private:
	RIGID_BODY_TYPE _type = RIGID_BODY_TYPE::NONE;
	float	_mass = 1.f;
	float	_gravityScale = 2.f;
};

