#pragma once
#include "Component.h"

enum class COLLIDER_TYPE : uint8
{
	RECT_COLLIDER_2D,
	TILEMAP_COLLIDER,
	END,
};

enum
{
	COLLIDER_TYPE_COUNT = static_cast<uint8>(COLLIDER_TYPE::END)
};

class Material;
class Mesh;
class Transform;

class Collider : public Component
{
public:
	Collider(COLLIDER_TYPE type);
	virtual ~Collider();			

	virtual void Render();

	COLLIDER_TYPE GetColloderType() { return _type; }
	void SetAlive() { _isAlive = true; }
	void SetDead() { _isAlive = false; }
	bool IsAlive() { return _isAlive; }
	
	bool GetCollided() { return _collided; }
	void SetCollidedTrue() { _collided = true; }
	void SetCollidedFalse() { _collided = false; }

	void SetTransform(const weak_ptr<Transform> transform) { _transform = transform.lock(); }
	shared_ptr<Transform> GetColliderTransform() { return _transform; }

protected:
	// Collider�� ������ �� Transform�� ���� ��� ��ü Transform����, �׿� ���� Rendering
	// ���� ���� ��� �ڽ��� ���� GameObject�� Transform�� �״�� ������ ��
	shared_ptr<Transform>	_transform;
	shared_ptr<Material>	_material;
	shared_ptr<Mesh>		_mesh;	

	Vec4	_baseColor = { 0.f, 1.f, 0.f, 0.f };
	Vec4	_collidedColor = { 1.f, 0.f, 0.f, 0.f };

	COLLIDER_TYPE			_type;
	bool					_collided = false;	
	bool					_isAlive = false;
};

