#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "Camera.h"
#include "Collider.h"
#include "RectCollider2D.h"
#include "TilemapCollider.h"
#include "RigidBody2D.h"
#include "MonoBehaviour.h"

GameObject::GameObject() : Object(OBJECT_TYPE::GAMEOBJECT)
{

}
 
GameObject::~GameObject()
{

}

void GameObject::Awake()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->Awake();
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Awake();
	}
}

void GameObject::Start()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->Start();
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Start();
	}
}

void GameObject::Update()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->Update();
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->Update();
	}
}

void GameObject::LateUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->LateUpdate();
	}

	for (shared_ptr<MonoBehaviour>& script : _scripts)
	{
		script->LateUpdate();
	}
}

void GameObject::FinalUpdate()
{
	for (shared_ptr<Component>& component : _components)
	{
		if (component)
			component->FinalUpdate();
	}
}

shared_ptr<Component> GameObject::GetFixedComponent(COMPONENT_TYPE type)
{
	uint8 index = static_cast<uint8>(type);
	assert(index < FIXED_COMPONENT_COUNT);
	return _components[index];
}

shared_ptr<Transform> GameObject::GetTransform()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::TRANSFORM);
	return static_pointer_cast<Transform>(component);
}

shared_ptr<MeshRenderer> GameObject::GetMeshRenderer()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::MESH_RENDERER);
	return static_pointer_cast<MeshRenderer>(component);
}

shared_ptr<Camera> GameObject::GetCamera()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::CAMERA);
	return static_pointer_cast<Camera>(component);
}

shared_ptr<RigidBody2D> GameObject::GetRigidBody2D()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::RIGID_BODY);
	return static_pointer_cast<RigidBody2D>(component);
}

shared_ptr<Collider> GameObject::GetCollider()
{
	shared_ptr<Component> component = GetFixedComponent(COMPONENT_TYPE::COLLIDER);
	shared_ptr<Collider> collider = static_pointer_cast<Collider>(component);

	if (collider != nullptr)
	{
		if(collider->GetColloderType() == COLLIDER_TYPE::RECT_COLLIDER_2D)
			return static_pointer_cast<RectCollider2D>(collider);
		if (collider->GetColloderType() == COLLIDER_TYPE::TILEMAP_COLLIDER)
			return static_pointer_cast<TilemapCollider>(collider);
	}		

	return nullptr;
}

shared_ptr<RectCollider2D> GameObject::GetRectCollider2D()
{
	shared_ptr<Collider> component = GetCollider();
	return static_pointer_cast<RectCollider2D>(component);
}

void GameObject::AddComponent(shared_ptr<Component> component)
{
	component->SetGameObject(shared_from_this());

	uint8 index = static_cast<uint8>(component->GetType());
	if (index < FIXED_COMPONENT_COUNT)
	{
		_components[index] = component;
	}
	else
	{
		_scripts.push_back(dynamic_pointer_cast<MonoBehaviour>(component));
	}
}