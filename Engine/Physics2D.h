#pragma once

class GameObject;
class Scene;

class Physics2D
{
public:

	static RayCastHit2D RayCast(Vec2 pos, Vec2 dir, float dis);
	static RayCastHit2D RayCast(Vec2 pos, Vec2 dir, float dis, int LayerMask);

private:

};

