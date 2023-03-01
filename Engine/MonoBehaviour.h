#pragma once
#include "Component.h"

enum class BEHAVIOUR_TYPE : uint8
{
	PLAYER,
	CAMERA,
	END,
};

enum
{
	BEHAVIOUR_TYPE_COUNT = static_cast<uint8>(BEHAVIOUR_TYPE::END)
};

class MonoBehaviour : public Component
{
public:
	MonoBehaviour(BEHAVIOUR_TYPE type);
	virtual ~MonoBehaviour();

public:
	BEHAVIOUR_TYPE _type;
};

