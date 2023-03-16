#pragma once
#include "Collider.h"

class RectCollider2D : public Collider
{
public:
	RectCollider2D();
	RectCollider2D(weak_ptr<Transform> transform);
	virtual ~RectCollider2D();

	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FinalUpdate() override;

	virtual void Render() override;
	void Render(weak_ptr<Transform> position);
		
	void CollidedColor();
	void InPortalColor();
	void BaseColor();
		
	static bool AABB(Transform& world1, Transform& world2);
	static bool RayCastRect(Ray& ray, Transform& object);
	static bool InPortal(Transform& position, Transform& portal);

private:

};

