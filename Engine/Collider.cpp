#include "pch.h"
#include "Collider.h"

Collider::Collider(COLLIDER_TYPE type) : Component(COMPONENT_TYPE::COLLIDER), _type(type)
{		
}

Collider::~Collider()
{
}

void Collider::Render()
{
}
