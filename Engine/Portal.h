#pragma once
#include "Component.h"
#include "Scene.h"

class Portal : public Component
{
public:
	Portal(SCENE_TYPE type);
	virtual ~Portal();

	const SCENE_TYPE GetStage() { return _type; }

private:
	SCENE_TYPE		_type;
};

