#include "pch.h"
#include "Debug.h"
#include "Transform.h"
#include "Mesh.h"
#include "Material.h"
#include "Shader.h"

void Debug::DrawRay2D(Vec2 start, Vec2 dir, float distance)
{
	float ratio = 0.f;
	ratio = sqrt(pow(distance, 2) / (pow(dir.x, 2) + pow(dir.y, 2)));
	Vec2 rayEnd = Vec2(start.x + dir.x * ratio, start.y + dir.y * ratio);

	vector<Vertex> vec(2);
	vec[0].pos = Vec3(start.x, start.y, 1.f);
	vec[0].color = Vec4(0.f, 1.f, 0.f, 0.f);
	vec[0].uv = Vec2(0.f, 0.f);
	vec[1].pos = Vec3(rayEnd.x, rayEnd.y, 1.f);
	vec[1].color = Vec4(0.f, 1.f, 0.f, 0.f);
	vec[1].uv = Vec2(0.f, 0.f);

	vector<uint32> index;
	index.push_back(0);
	index.push_back(1);

	shared_ptr<Transform> transform = make_shared<Transform>();
	transform->SetLocalPosition(Vec3(start.x, start.y, 1.f));
	transform->SetLocalScale(Vec3(1.f, 1.f, 1.f));
	transform->SetLocalRotation(Vec3(0.f, 0.f, 0.f));

	shared_ptr<Mesh> mesh = make_shared<Mesh>();
	mesh->Init(vec, index);

	shared_ptr<Material> material = make_shared<Material>();
	shared_ptr<Shader> shader = make_shared<Shader>();
	shader->Init(L"..\\Resources\\Shader\\rayCast.hlsl", TOPOLOGY_TYPE::LINE);
	material->SetShader(shader);

	transform->PushData();
	material->Update();
	mesh->Render(LINESTRIP_MESH);	
}
