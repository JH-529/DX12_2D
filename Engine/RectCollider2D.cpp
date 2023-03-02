#include "pch.h"
#include "Engine.h"
#include "RectCollider2D.h"
#include "Transform.h"
#include "GameObject.h"
#include "Component.h"
#include "Resources.h"
#include "Mesh.h"
#include "Material.h"

RectCollider2D::RectCollider2D() : Collider(COLLIDER_TYPE::RECT_COLLIDER_2D)
{
	_mesh = GET_SINGLE(Resources)->LoadColliderMesh();

	shared_ptr<Shader> shader = make_shared<Shader>();
	shader->Init(L"..\\Resources\\Shader\\collider.hlsl");
	_material->SetShader(shader);
	_material->SetInt(0, 0);
}

RectCollider2D::~RectCollider2D()
{

}

void RectCollider2D::FinalUpdate()
{	
	_transform = GetTransform();
}

void RectCollider2D::Render()
{	
	_transform->PushData();
	_material->Update();
	_mesh->Render(MESH_TYPE::LINESTRIP_MESH);
}
