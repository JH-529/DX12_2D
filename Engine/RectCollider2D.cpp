#include "pch.h"
#include "Engine.h"
#include "RectCollider2D.h"
#include "Transform.h"
#include "GameObject.h"
#include "Component.h"
#include "Resources.h"
#include "Mesh.h"
#include "Material.h"
#include "Input.h"

RectCollider2D::RectCollider2D() : Collider(COLLIDER_TYPE::RECT_COLLIDER_2D)
{
	_mesh = GET_SINGLE(Resources)->LoadColliderMesh();

	shared_ptr<Shader> shader = make_shared<Shader>();
	shared_ptr<Texture> texture = make_shared<Texture>();
	shader->Init(L"..\\Resources\\Shader\\collider.hlsl");
	texture->Init(L"..\\Resources\\Texture\\rapi.jpg");
	_material->SetShader(shader);
	_material->SetTexture(0, texture);
	_material->SetInt(0, 1);		
	_material->SetVec4(_baseColor);
}

RectCollider2D::~RectCollider2D()
{

}

void RectCollider2D::LateUpdate()
{
	if (INPUT->GetButton(KEY_TYPE::Q))
		_material->SetVec4(_collidedColor);
	if (INPUT->GetButton(KEY_TYPE::E))
		_material->SetVec4(_baseColor);
}


void RectCollider2D::FinalUpdate()
{		
}

void RectCollider2D::Render()
{	
	GetTransform()->PushData();
	_material->Update();
	_mesh->Render(MESH_TYPE::LINESTRIP_MESH);
}
