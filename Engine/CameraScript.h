#pragma once
#include "MonoBehaviour.h"

class CameraScript : public MonoBehaviour
{
public:
	CameraScript();
	virtual ~CameraScript();

	void Update() override;

private:
	float		_speed = 100.f;
};

