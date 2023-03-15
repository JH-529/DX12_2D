#pragma once

class GameObject;
class Scene;

// RayCast 함수 사용시 프레임 저하 발생
class Physics2D
{
public:

	static RayCastHit2D RayCast(Vec2 pos, Vec2 dir, float dis);
	static RayCastHit2D RayCast(Vec2 pos, Vec2 dir, float dis, int LayerMask);

private:

};

