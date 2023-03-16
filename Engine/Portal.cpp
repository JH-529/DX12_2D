#include "pch.h"
#include "Portal.h"

Portal::Portal(SCENE_TYPE type) : Component(COMPONENT_TYPE::PORTAL), _type(type)
{
}

Portal::~Portal()
{
}
