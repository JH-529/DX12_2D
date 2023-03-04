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

	void Render();

	void CollidedColor();
	void BaseColor();

	static bool AABB(Transform& world1, Transform& world2);

private:
	shared_ptr<Material>	_material = make_shared<Material>();
	shared_ptr<Mesh>		_mesh;	

	Vec4	_baseColor = { 0.f, 1.f, 0.f, 0.f };
	Vec4	_collidedColor = { 1.f, 0.f, 0.f, 0.f };	
};

