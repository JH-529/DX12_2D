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

class Collider : Component
{
public:
	Collider(COLLIDER_TYPE type);
	virtual ~Collider();
	
private:
	COLLIDER_TYPE			_type;	
	
};

