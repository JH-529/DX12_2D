#pragma once
#include "Component.h"

enum class COLLIDER_TYPE : uint8
{
	RECT_COLLIDER_2D,
	END,
};

enum
{
	COLLIDER_TYPE_COUNT = static_cast<uint8>(COLLIDER_TYPE::END)
};

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
	
private:
	COLLIDER_TYPE			_type;	
	bool					_isAlive = false;
};

