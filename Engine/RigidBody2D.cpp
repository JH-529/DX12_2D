#include "pch.h"
#include "RigidBody2D.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "RectCollider2D.h"
#include "Timer.h"

// Transform()에 COMPONENT_TYPE::RIGID_BODY를 넣지 않을경우
// RigidBody2D가 들어간 Object가 비정상작동
RigidBody2D::RigidBody2D() : Transform(COMPONENT_TYPE::RIGID_BODY)
{
}

RigidBody2D::~RigidBody2D()
{
}

void RigidBody2D::Awake()
{
	_transform = GetGameObject()->GetTransform();
}

void RigidBody2D::Start()
{	
}

void RigidBody2D::Update()
{
	// 충돌시 수행할 RigidBody의 코드	
	Collision();

	if (!_bottomCollided)
	{
		Vec3 pos = GetGameObject()->GetTransform()->GetLocalPosition();

		pos.y -= _gravity;
		GetGameObject()->GetTransform()->SetLocalPosition(pos);
	}
	
}

void RigidBody2D::LateUpdate()
{
}

void RigidBody2D::FinalUpdate()
{
}

bool RigidBody2D::Collision()
{
	// RigidBody2D를 갖고 있는 GameObject가 속한 Scene에 있는
	// Collider를 포함하고 있는 모든 GameObject들을 가져옴
	shared_ptr<Scene> scene = GetGameObject()->GetScene();
	vector<shared_ptr<GameObject>> gameObjects = scene->GetColliderObjects();

	_bottomCollided = false;
	_sideCollided = false;
	_leftCollided = false;
	_rightCollided = false;

	// 지면 충돌 판별
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->GetCollider()->IsAlive())
		{
			if (BottomCollision(*_transform, *gameObject->GetTransform()))
			{
				_bottomCollided = true;
			}
		}		
	}

	// 측면 충돌 판별
	for (auto& gameObject : gameObjects)
	{
		if (gameObject->GetCollider()->IsAlive())
		{
			if (SideCollision(*_transform, *gameObject->GetTransform()))
			{
				_sideCollided = true;
			}
		}		
	}

	// 한번이라도 충돌이 발생했다면 Collision발생
	if (_bottomCollided || _sideCollided)
		return true;

	return false;
}

// object1의 바닥면이 object2의 윗면과 충돌하였는지 판단
bool RigidBody2D::BottomCollision(Transform& object1, Transform& object2)
{
	// 두 물체의 위치
	Vec2 position1;
	position1.x = object1.GetLocalPosition().x;
	position1.y = object1.GetLocalPosition().y;
	Vec2 position2;			 
	position2.x = object2.GetLocalPosition().x;
	position2.y = object2.GetLocalPosition().y;

	// 두 물체의 x, y축 각각의 크기
	Vec2 scale1;
	scale1.x = object1.GetLocalScale().x;
	scale1.y = object1.GetLocalScale().y;
	Vec2 scale2;		  
	scale2.x = object2.GetLocalScale().x;
	scale2.y = object2.GetLocalScale().y;

	// 각 물체의 x, y축의 크기의 절반
	Vec2 halfDistance1, halfDistance2;
	halfDistance1 = Vec2(fabsf(scale1.x), fabsf(scale1.y)) * 0.5f;
	halfDistance2 = Vec2(fabsf(scale2.x), fabsf(scale2.y)) * 0.5f;

	// object1의 아래 축을 담당하는 두개의 Vertex의 position
	Vec2 object1_Vertex1;
	object1_Vertex1.x = position1.x - halfDistance1.x;
	object1_Vertex1.y = position1.y - halfDistance1.y;
	Vec2 object1_Vertex2;
	object1_Vertex2.x = position1.x + halfDistance1.x;
	object1_Vertex2.y = position1.y - halfDistance1.y;

	// object2의 위축을 담당하는 두개의 Vertex의 position
	Vec2 object2_Vertex1;
	object2_Vertex1.x = position2.x - halfDistance2.x;
	object2_Vertex1.y = position2.y + halfDistance2.y;
	Vec2 object2_Vertex2;						  
	object2_Vertex2.x = position2.x + halfDistance2.x;
	object2_Vertex2.y = position2.y + halfDistance2.y;

	// object1의 아랫변의 양끝 각각의 x값, object2의 윗변의 양끝 각각의 x값을 비교(3가지 방면)
	// 위의 비교를 통해 object2의 위에 object1이 위치하는지 판단
	// 이후 object1의 아랫변의 y값이 object2의 윗변의 y값 - 중력적용 크기 ~ object2의 윗변의 y값
	// 사이에 들어가는지를 통해 object1이 object2의 윗변과 충돌한 것인지를 판단(그림참조)
	if ((object1_Vertex1.x > object2_Vertex1.x && object1_Vertex1.x < object2_Vertex2.x) ||
		(object1_Vertex2.x > object2_Vertex1.x && object1_Vertex2.x < object2_Vertex2.x) ||
		(object1_Vertex1.x < object2_Vertex1.x && object1_Vertex2.x > object2_Vertex2.x))
	{
		if ((object1_Vertex1.y <= object2_Vertex1.y) && 
			(object2_Vertex1.y - _gravity * 1.f <= object1_Vertex1.y))
		{			
			return true;
		}
	}

	return false;
}

// object1의 옆면이 object2의 옆면과 충돌하였는지 판단
bool RigidBody2D::SideCollision(Transform& object1, Transform& object2)
{
	// 두 물체의 위치
	Vec2 position1;
	position1.x = object1.GetLocalPosition().x;
	position1.y = object1.GetLocalPosition().y;
	Vec2 position2;
	position2.x = object2.GetLocalPosition().x;
	position2.y = object2.GetLocalPosition().y;

	// 두 물체의 x, y축 각각의 크기
	Vec2 scale1;
	scale1.x = object1.GetLocalScale().x;
	scale1.y = object1.GetLocalScale().y;
	Vec2 scale2;
	scale2.x = object2.GetLocalScale().x;
	scale2.y = object2.GetLocalScale().y;

	// 각 물체의 x, y축의 크기의 절반
	Vec2 halfDistance1, halfDistance2;
	halfDistance1 = Vec2(fabsf(scale1.x), fabsf(scale1.y)) * 0.5f;
	halfDistance2 = Vec2(fabsf(scale2.x), fabsf(scale2.y)) * 0.5f;

	// object1의 4개의 Vertex
	// 1 2
	// 3 4
	Vec2 object1_Vertex1;
	object1_Vertex1.x = position1.x - halfDistance1.x;
	object1_Vertex1.y = position1.y + halfDistance1.y;
	Vec2 object1_Vertex2;
	object1_Vertex2.x = position1.x + halfDistance1.x;
	object1_Vertex2.y = position1.y + halfDistance1.y;
	Vec2 object1_Vertex3;
	object1_Vertex3.x = position1.x - halfDistance1.x;
	object1_Vertex3.y = position1.y - halfDistance1.y;
	Vec2 object1_Vertex4;
	object1_Vertex4.x = position1.x + halfDistance1.x;
	object1_Vertex4.y = position1.y - halfDistance1.y;

	// object2의 4개의 Vertex
	// 1 2
	// 3 4
	Vec2 object2_Vertex1;
	object2_Vertex1.x = position2.x - halfDistance2.x;
	object2_Vertex1.y = position2.y + halfDistance2.y;
	Vec2 object2_Vertex2;
	object2_Vertex2.x = position2.x + halfDistance2.x;
	object2_Vertex2.y = position2.y + halfDistance2.y;
	Vec2 object2_Vertex3;
	object2_Vertex3.x = position2.x - halfDistance2.x;
	object2_Vertex3.y = position2.y - halfDistance2.y;
	Vec2 object2_Vertex4;
	object2_Vertex4.x = position2.x + halfDistance2.x;
	object2_Vertex4.y = position2.y - halfDistance2.y;

	// object1기준 충돌 판별(object2의 측면 사이에 object1의 측면의 두 정점이 들어가는 경우)
	// o1	o2	o2	 o1
	// 2    1	2    1
	// 4 vs 3	4 vs 3
	// Object1의 우측이 Object2의 좌측에 충돌
	if ((object1_Vertex2.y < object2_Vertex1.y - _gravity * 1.f && object1_Vertex2.y > object2_Vertex3.y) ||
		(object1_Vertex4.y < object2_Vertex1.y - _gravity * 1.f && object1_Vertex4.y > object2_Vertex3.y))
	{
		//object1이 object2보다 왼쪽에 있어야한다.
		if (object1_Vertex2.x < object2_Vertex2.x)
		{
			if (object1_Vertex2.x >= object2_Vertex1.x)
			{
				_rightCollided = true;
				return true;
			}
		}		
	}

	// Object1의 좌측이 Object2의 우측에 충돌
	if ((object1_Vertex1.y < object2_Vertex2.y - _gravity * 1.f && object1_Vertex1.y > object2_Vertex4.y) ||
		(object1_Vertex3.y < object2_Vertex2.y - _gravity * 1.f && object1_Vertex3.y > object2_Vertex4.y))
	{
		// object1이 object2보다 우측에 있어야한다.
		if (object1_Vertex1.x > object2_Vertex1.x)
		{
			if (object1_Vertex1.x < object2_Vertex2.x)
			{
				_leftCollided = true;
				return true;
			}
		}		
	}


	// object2기준 충돌 판별(object1의 측면 사이에 object2의 측면의 두 정점이 들어가는 경우)
	// o2	o1	o1	 o2
	// 2    1	2    1
	// 4 vs 3	4 vs 3
	// Object2의 우측이 Object1의 좌측에 충돌
	//if ((object2_Vertex2.y < object1_Vertex1.y - _gravity * 1.f && object2_Vertex2.y > object1_Vertex3.y) ||
	//	(object2_Vertex4.y < object1_Vertex1.y - _gravity * 1.f && object2_Vertex4.y > object1_Vertex3.y))
	//{
	//	//object2가 object1보다 왼쪽에 있어야한다.
	//	if (object2_Vertex2.x < object1_Vertex2.x)
	//	{
	//		if (object2_Vertex2.x >= object1_Vertex1.x)
	//		{
	//			_leftCollided = true; // object1의 좌측에서 충돌
	//			return true;
	//		}
	//	}
	//}

	//// Object2의 좌측이 Object1의 우측에 충돌
	//if ((object2_Vertex1.y < object1_Vertex2.y - _gravity * 1.f && object2_Vertex1.y > object1_Vertex4.y) ||
	//	(object2_Vertex3.y < object1_Vertex2.y - _gravity * 1.f && object2_Vertex3.y > object1_Vertex4.y))
	//{
	//	// object2가 object1보다 우측에 있어야한다.
	//	if (object2_Vertex1.x > object1_Vertex1.x)
	//	{
	//		if (object2_Vertex1.x < object1_Vertex2.x)
	//		{
	//			_rightCollided = true; // object1의 우측에서 충돌
	//			return true;
	//		}
	//	}
	//}

	return false;
}
