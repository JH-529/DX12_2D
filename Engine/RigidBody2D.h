#pragma once
#include "Transform.h"

enum class RIGID_BODY_TYPE : uint8
{
	NONE,
	DYNAMIC,
	STATIC,
	KINEMATIC,
	END,
};

class RigidBody2D : public Transform
{
public:
	RigidBody2D();
	virtual ~RigidBody2D();

	virtual void Awake() override;
	virtual void Start() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FinalUpdate() override;

	bool Collision();
	bool BottomCollision(Transform& object1, Transform& object2);
	bool SideCollision(Transform& object1, Transform& object2);

	void SetForce(float value) { _force = value; }
	void SetMass(float value) { _mass = value; }
	void SetGravity(float value) { _gravity = value; }
	
	float GetForce() { return _force; }
	float GetMass() { return _mass; }
	float GetGravity() { return _gravity; }
	bool GetLeftCollided() { return _leftCollided; }
	bool GetRightCollided() { return _rightCollided; }

	void InPortal() { _inPortal = true; }
	void NotInPortal() { _inPortal = false; }
	bool IsInportal() { return _inPortal; }

private:
	RIGID_BODY_TYPE _type = RIGID_BODY_TYPE::NONE;
	shared_ptr<Transform> _transform;

	float	_force = 1.f;
	float	_mass = 1.f;
	float	_gravity = 2.f;

	bool	_bottomCollided = false;
	bool	_sideCollided = false;
	bool	_leftCollided = false;
	bool	_rightCollided = false;
	bool	_inPortal = false;
};
