#pragma once
#include "Component.h"
#include "Object.h"

class Transform;
class MeshRenderer;
class MonoBehaviour;
class Camera;
class Collider;
class RectCollider2D;
class RigidBody2D;

class Scene;

class GameObject : public Object, public enable_shared_from_this<GameObject>
{
public:
	GameObject();
	virtual ~GameObject();

	void Awake();
	void Start();
	void Update();
	void LateUpdate();
	void FinalUpdate();

	shared_ptr<Component> GetFixedComponent(COMPONENT_TYPE type);

	shared_ptr<Transform> GetTransform();
	shared_ptr<MeshRenderer> GetMeshRenderer();
	shared_ptr<Camera> GetCamera();
	shared_ptr<RigidBody2D> GetRigidBody2D();
	shared_ptr<Collider> GetCollider();
	shared_ptr<RectCollider2D> GetRectCollider2D();
	
	void AddComponent(shared_ptr<Component> component);

	void SetScene(const shared_ptr<Scene> scene) { _scene = scene; }
	const shared_ptr<Scene> GetScene() { return _scene; }
		
private:
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components;
	vector<shared_ptr<MonoBehaviour>> _scripts;
	shared_ptr<Scene>	_scene;
};