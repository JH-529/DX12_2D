#pragma once
#include "Collider.h"

class Transform;
class Mesh;
class Material;

class RectCollider2D : public Collider
{
public:
	RectCollider2D();
	virtual ~RectCollider2D();

	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FinalUpdate() override;

	virtual void Render() override;
	void Render(weak_ptr<Transform> position);

	void CollidedColor();
	void BaseColor();
	bool GetCollided() { return _collided; }
	void SetCollidedTrue() { _collided = true; }
	void SetCollidedFalse() { _collided = false; }

	static bool AABB(Transform& world1, Transform& world2);
	static bool RayCastRect(Ray& ray, Transform& object);

private:
	shared_ptr<Material>	_material = make_shared<Material>();
	shared_ptr<Mesh>		_mesh;	

	bool	_collided = false;
	Vec4	_baseColor = { 0.f, 1.f, 0.f, 0.f };
	Vec4	_collidedColor = { 1.f, 0.f, 0.f, 0.f };	
};

