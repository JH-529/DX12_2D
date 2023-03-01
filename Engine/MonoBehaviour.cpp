#include "pch.h"
#include "MonoBehaviour.h"

MonoBehaviour::MonoBehaviour(BEHAVIOUR_TYPE type) : Component(COMPONENT_TYPE::MONO_BEHAVIOUR), _type(type)
{

}

MonoBehaviour::~MonoBehaviour()
{

}