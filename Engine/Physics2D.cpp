#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "Physics2D.h"
#include "RectCollider2D.h"
#include "SceneManager.h"

RayCastHit2D Physics2D::RayCast(Vec2 pos, Vec2 dir, float dis)
{
	shared_ptr<Scene> scene = ACTIVE_SCENE;
	assert(scene);

	Ray ray;
	ray.pos = pos;
	ray.dir = dir;
	ray.distance = dis;
	vector<shared_ptr<GameObject>> gameObjects = scene->GetColliderObjects();
	
	shared_ptr<GameObject> collidedObject;
	RayCastHit2D rayCastHit2D = {};
	float distance;
	for (auto& gameObject : gameObjects)
	{
		if (RectCollider2D::RayCastRect(ray, *gameObject->GetTransform()))
		{
			collidedObject = gameObject;
			rayCastHit2D._collider = gameObject->GetCollider();
			rayCastHit2D._rigidBody = gameObject->GetRigidBody2D();
			Vec3 position = gameObject->GetTransform()->GetLocalPosition();
			float a = position.x - pos.x;
			float b = position.y - pos.y;
			distance = sqrt(pow(a,2) + pow(b,2));
			rayCastHit2D._distance = distance;
		}
	}

	return rayCastHit2D;
}

// LayerMask에 해당하는 Collider만을 Detect
RayCastHit2D Physics2D::RayCast(Vec2 pos, Vec2 dir, float dis, int LayerMask)
{
	shared_ptr<Scene> scene = ACTIVE_SCENE;
	assert(scene);

	Ray ray;
	ray.pos = pos;
	ray.dir = dir;
	ray.distance = dis;
	vector<shared_ptr<GameObject>> gameObjects = scene->GetColliderObjects();

	shared_ptr<GameObject> collidedObject;
	RayCastHit2D rayCastHit2D = {};
	float distance;
	for (auto& gameObject : gameObjects)
	{
		if (RectCollider2D::RayCastRect(ray, *gameObject->GetTransform()))
		{
			collidedObject = gameObject;
			rayCastHit2D._collider = gameObject->GetCollider();
			rayCastHit2D._rigidBody = gameObject->GetRigidBody2D();
			Vec3 position = gameObject->GetTransform()->GetLocalPosition();
			float a = position.x - pos.x;
			float b = position.y - pos.y;
			distance = sqrt(pow(a, 2) + pow(b, 2));
			rayCastHit2D._distance = distance;
		}
	}

	return rayCastHit2D;
}
