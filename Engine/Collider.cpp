#include "pch.h"
#include "Collider.h"
#include "GameObject.h"
#include "Transform.h"


Collider::Collider(COLLIDER_TYPE type) : Component(COMPONENT_TYPE::COLLIDER), _type(type)
{		
}

Collider::~Collider()
{
}
