#pragma once
#include "Collider.h"

class TilemapCollider : public Collider
{
public:
	TilemapCollider();
	TilemapCollider(weak_ptr<Transform> transform);
	virtual ~TilemapCollider();

	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void FinalUpdate() override;

	virtual void Render() override;
	void Render(weak_ptr<Transform> position);

	bool AABB(Transform& world1, Transform& world2);

private:

};

