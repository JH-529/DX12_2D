#pragma once
#include "Component.h"

struct TransformMatrix
{
	Vec4 offset;
};


class Transform : public Component
{
public:
	Transform();
	virtual ~Transform();

	// TODO : 온갖 Parent/Child 관계
	
	Vec4 GetTransform() { return _transform.offset; }
	void SetTransformX(float value) { _transform.offset.x += value; }
	void SetTransformY(float value) { _transform.offset.y += value; }
	void SetTransformZ(float value) { _transform.offset.z += value; }

	void SetTransform(Vec4 offset) { _transform.offset = offset; }

	void Update();

private:
	// TODO : World 위치 관련
	TransformMatrix _transform = {};
};

