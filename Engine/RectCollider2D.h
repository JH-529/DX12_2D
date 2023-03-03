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

	virtual void Update() override { Render(); }
	virtual void LateUpdate() override;
	virtual void FinalUpdate() override;
	virtual void Render() override;

private:
	shared_ptr<Material>	_material = make_shared<Material>();
	shared_ptr<Mesh>		_mesh;	

	Vec4	_baseColor = { 0.f, 1.f, 0.f, 0.f };
	Vec4	_collidedColor = { 1.f, 0.f, 0.f, 0.f };	
};

