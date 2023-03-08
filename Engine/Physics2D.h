#pragma once

class GameObject;
class Scene;

class Physics2D
{
public:
	static int RayCast(Vec2 pos, Vec2 dir, float dis);

private:
	shared_ptr<GameObject> _collider;
};

