#pragma once
#include "Component.h"
#include "Object.h"

class Transform;
class MeshRenderer;
class MonoBehaviour;
class Camera;
class Collider;
class RectCollider2D;
class TilemapCollider;
class RigidBody2D;
class Portal;

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
	shared_ptr<Portal> GetPortal();
	shared_ptr<Collider> GetCollider();
	shared_ptr<RectCollider2D> GetRectCollider2D();
	//shared_ptr<TilemapCollider> GetTilemapCollider();

	void AddComponent(shared_ptr<Component> component);

	void SetScene(const shared_ptr<Scene> scene) { _scene = scene; }
	const shared_ptr<Scene> GetScene() { return _scene; }

	void ObjectAlive() { _isAlive = true; }
	void ObjectDead() { _isAlive = false; }
	bool IsAlive() { return _isAlive; }
		
	void InitializeStatus() { _status = make_shared<Status>(); }
	void SetStatus(shared_ptr<Status> status) { _status = status; }
	shared_ptr<Status> GetStatus() { return _status; }

private:
	shared_ptr<Status>	_status;
	array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components;
	vector<shared_ptr<MonoBehaviour>> _scripts;
	shared_ptr<Scene>	_scene;
	bool				_isAlive = true;
	
};
