#pragma once

class GameObject;
class Scene;

// RayCast �Լ� ���� ������ ���� �߻�
class Physics2D
{
public:

	static RayCastHit2D RayCast(Vec2 pos, Vec2 dir, float dis);
	static RayCastHit2D RayCast(Vec2 pos, Vec2 dir, float dis, int LayerMask);

private:

};

