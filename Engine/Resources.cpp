#include "pch.h"
#include "Resources.h"

shared_ptr<Mesh> Resources::LoadRectMesh()
{
	shared_ptr<Mesh> findMesh = Get<Mesh>(L"Rectangle");
	if (findMesh)
		return findMesh;

	vector<Vertex> vec(4);
	vec[0].pos = Vec3(-0.5f, 0.5f, 0.f);
	vec[0].color = Vec4(1.f, 0.f, 0.f, 1.f);
	vec[0].uv = Vec2(0.f, 0.f);
	vec[1].pos = Vec3(0.5f, 0.5f, 0.f);
	vec[1].color = Vec4(0.f, 1.f, 0.f, 1.f);
	vec[1].uv = Vec2(1.f, 0.f);
	vec[2].pos = Vec3(0.5f, -0.5f, 0.f);
	vec[2].color = Vec4(0.f, 0.f, 1.f, 1.f);
	vec[2].uv = Vec2(1.f, 1.f);
	vec[3].pos = Vec3(-0.5f, -0.5f, 0.f);
	vec[3].color = Vec4(0.f, 1.f, 0.f, 1.f);
	vec[3].uv = Vec2(0.f, 1.f);

	vector<uint32> indexVec;
	{
		indexVec.push_back(0);
		indexVec.push_back(1);
		indexVec.push_back(2);
	}
	{
		indexVec.push_back(0);
		indexVec.push_back(2);
		indexVec.push_back(3);
	}

	shared_ptr<Mesh> rect = make_shared<Mesh>();
	rect->Init(vec, indexVec);
	Add(L"Rectangle", rect);

	return rect;
}

shared_ptr<Mesh> Resources::LoadColliderMesh()
{
	shared_ptr<Mesh> findMesh = Get<Mesh>(L"RectCollider");
	if (findMesh)
		return findMesh;

	vector<Vertex> vec(4);
	vec[0].pos = Vec3(-0.5f, 0.5f, 0.f);
	vec[0].color = Vec4(1.f, 0.f, 0.f, 1.f);
	vec[0].uv = Vec2(0.f, 0.f);
	vec[1].pos = Vec3(0.5f, 0.5f, 0.f);
	vec[1].color = Vec4(0.f, 1.f, 0.f, 1.f);
	vec[1].uv = Vec2(1.f, 0.f);
	vec[2].pos = Vec3(0.5f, -0.5f, 0.f);
	vec[2].color = Vec4(0.f, 0.f, 1.f, 1.f);
	vec[2].uv = Vec2(1.f, 1.f);
	vec[3].pos = Vec3(-0.5f, -0.5f, 0.f);
	vec[3].color = Vec4(0.f, 1.f, 0.f, 1.f);
	vec[3].uv = Vec2(0.f, 1.f);

	vector<uint32> indexVec;
	{
		indexVec.push_back(0);
		indexVec.push_back(1);			
	}
	{
		indexVec.push_back(1);
		indexVec.push_back(2);
	}
	{
		indexVec.push_back(2);
		indexVec.push_back(3);
	}
	{
		indexVec.push_back(3);
		indexVec.push_back(0);
	}

	shared_ptr<Mesh> rect = make_shared<Mesh>();
	rect->Init(vec, indexVec);
	Add(L"RectCollider", rect);

	return rect;
}


//shared_ptr<Mesh> Resources::LoadCubeMesh()
//{
//	shared_ptr<Mesh> findMesh = Get<Mesh>(L"Cube");
//	if (findMesh)
//		return findMesh;
//
//	float w2 = 0.5f;
//	float h2 = 0.5f;
//	float d2 = 0.5f;
//
//	vector<Vertex> vec(24);
//
//	// �ո�
//	vec[0] = Vertex(Vec3(-w2, -h2, -d2), Vec2(0.0f, 1.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(1.0f, 0.0f, 0.0f));
//	vec[1] = Vertex(Vec3(-w2, +h2, -d2), Vec2(0.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(1.0f, 0.0f, 0.0f));
//	vec[2] = Vertex(Vec3(+w2, +h2, -d2), Vec2(1.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(1.0f, 0.0f, 0.0f));
//	vec[3] = Vertex(Vec3(+w2, -h2, -d2), Vec2(1.0f, 1.0f), Vec3(0.0f, 0.0f, -1.0f), Vec3(1.0f, 0.0f, 0.0f));
//	// �޸�
//	vec[4] = Vertex(Vec3(-w2, -h2, +d2), Vec2(1.0f, 1.0f), Vec3(0.0f, 0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f));
//	vec[5] = Vertex(Vec3(+w2, -h2, +d2), Vec2(0.0f, 1.0f), Vec3(0.0f, 0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f));
//	vec[6] = Vertex(Vec3(+w2, +h2, +d2), Vec2(0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f));
//	vec[7] = Vertex(Vec3(-w2, +h2, +d2), Vec2(1.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f));
//	// ����
//	vec[8] = Vertex(Vec3(-w2, +h2, -d2), Vec2(0.0f, 1.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f));
//	vec[9] = Vertex(Vec3(-w2, +h2, +d2), Vec2(0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f));
//	vec[10] = Vertex(Vec3(+w2, +h2, +d2), Vec2(1.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f));
//	vec[11] = Vertex(Vec3(+w2, +h2, -d2), Vec2(1.0f, 1.0f), Vec3(0.0f, 1.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f));
//	// �Ʒ���
//	vec[12] = Vertex(Vec3(-w2, -h2, -d2), Vec2(1.0f, 1.0f), Vec3(0.0f, -1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f));
//	vec[13] = Vertex(Vec3(+w2, -h2, -d2), Vec2(0.0f, 1.0f), Vec3(0.0f, -1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f));
//	vec[14] = Vertex(Vec3(+w2, -h2, +d2), Vec2(0.0f, 0.0f), Vec3(0.0f, -1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f));
//	vec[15] = Vertex(Vec3(-w2, -h2, +d2), Vec2(1.0f, 0.0f), Vec3(0.0f, -1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f));
//	// ���ʸ�
//	vec[16] = Vertex(Vec3(-w2, -h2, +d2), Vec2(0.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f));
//	vec[17] = Vertex(Vec3(-w2, +h2, +d2), Vec2(0.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f));
//	vec[18] = Vertex(Vec3(-w2, +h2, -d2), Vec2(1.0f, 0.0f), Vec3(-1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f));
//	vec[19] = Vertex(Vec3(-w2, -h2, -d2), Vec2(1.0f, 1.0f), Vec3(-1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, -1.0f));
//	// �����ʸ�
//	vec[20] = Vertex(Vec3(+w2, -h2, -d2), Vec2(0.0f, 1.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
//	vec[21] = Vertex(Vec3(+w2, +h2, -d2), Vec2(0.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
//	vec[22] = Vertex(Vec3(+w2, +h2, +d2), Vec2(1.0f, 0.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
//	vec[23] = Vertex(Vec3(+w2, -h2, +d2), Vec2(1.0f, 1.0f), Vec3(1.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 1.0f));
//
//	vector<uint32> idx(36);
//
//	// �ո�
//	idx[0] = 0; idx[1] = 1; idx[2] = 2;
//	idx[3] = 0; idx[4] = 2; idx[5] = 3;
//	// �޸�
//	idx[6] = 4; idx[7] = 5; idx[8] = 6;
//	idx[9] = 4; idx[10] = 6; idx[11] = 7;
//	// ����
//	idx[12] = 8; idx[13] = 9; idx[14] = 10;
//	idx[15] = 8; idx[16] = 10; idx[17] = 11;
//	// �Ʒ���
//	idx[18] = 12; idx[19] = 13; idx[20] = 14;
//	idx[21] = 12; idx[22] = 14; idx[23] = 15;
//	// ���ʸ�
//	idx[24] = 16; idx[25] = 17; idx[26] = 18;
//	idx[27] = 16; idx[28] = 18; idx[29] = 19;
//	// �����ʸ�
//	idx[30] = 20; idx[31] = 21; idx[32] = 22;
//	idx[33] = 20; idx[34] = 22; idx[35] = 23;
//
//	shared_ptr<Mesh> mesh = make_shared<Mesh>();
//	mesh->Init(vec, idx);
//	Add(L"Cube", mesh);
//
//	return mesh;
//}
// 
//shared_ptr<Mesh> Resources::LoadSphereMesh()
//{
//	shared_ptr<Mesh> findMesh = Get<Mesh>(L"Sphere");
//	if (findMesh)
//		return findMesh;
//
//	float radius = 0.5f; // ���� ������
//	uint32 stackCount = 20; // ���� ����
//	uint32 sliceCount = 20; // ���� ����
//
//	vector<Vertex> vec;
//
//	Vertex v;
//
//	// �ϱ�
//	v.pos = Vec3(0.0f, radius, 0.0f);
//	v.uv = Vec2(0.5f, 0.0f);
//	v.normal = v.pos;
//	v.normal.Normalize();
//	v.tangent = Vec3(1.0f, 0.0f, 1.0f);
//	vec.push_back(v);
//
//	float stackAngle = XM_PI / stackCount;
//	float sliceAngle = XM_2PI / sliceCount;
//
//	float deltaU = 1.f / static_cast<float>(sliceCount);
//	float deltaV = 1.f / static_cast<float>(stackCount);
//
//	// ������ ���鼭 ������ ����Ѵ� (�ϱ�/���� �������� ���� X)
//	for (uint32 y = 1; y <= stackCount - 1; ++y)
//	{
//		float phi = y * stackAngle;
//
//		// ���� ��ġ�� ����
//		for (uint32 x = 0; x <= sliceCount; ++x)
//		{
//			float theta = x * sliceAngle;
//
//			v.pos.x = radius * sinf(phi) * cosf(theta);
//			v.pos.y = radius * cosf(phi);
//			v.pos.z = radius * sinf(phi) * sinf(theta);
//
//			v.uv = Vec2(deltaU * x, deltaV * y);
//
//			v.normal = v.pos;
//			v.normal.Normalize();
//
//			v.tangent.x = -radius * sinf(phi) * sinf(theta);
//			v.tangent.y = 0.0f;
//			v.tangent.z = radius * sinf(phi) * cosf(theta);
//			v.tangent.Normalize();
//
//			vec.push_back(v);
//		}
//	}
//
//	// ����
//	v.pos = Vec3(0.0f, -radius, 0.0f);
//	v.uv = Vec2(0.5f, 1.0f);
//	v.normal = v.pos;
//	v.normal.Normalize();
//	v.tangent = Vec3(1.0f, 0.0f, 0.0f);
//	vec.push_back(v);
//
//	vector<uint32> idx(36);
//
//	// �ϱ� �ε���
//	for (uint32 i = 0; i <= sliceCount; ++i)
//	{
//		//  [0]
//		//   |  \
//		//  [i+1]-[i+2]
//		idx.push_back(0);
//		idx.push_back(i + 2);
//		idx.push_back(i + 1);
//	}
//
//	// ���� �ε���
//	uint32 ringVertexCount = sliceCount + 1;
//	for (uint32 y = 0; y < stackCount - 2; ++y)
//	{
//		for (uint32 x = 0; x < sliceCount; ++x)
//		{
//			//  [y, x]-[y, x+1]
//			//  |		/
//			//  [y+1, x]
//			idx.push_back(1 + (y) * ringVertexCount + (x));
//			idx.push_back(1 + (y) * ringVertexCount + (x + 1));
//			idx.push_back(1 + (y + 1) * ringVertexCount + (x));
//			//		 [y, x+1]
//			//		 /	  |
//			//  [y+1, x]-[y+1, x+1]
//			idx.push_back(1 + (y + 1) * ringVertexCount + (x));
//			idx.push_back(1 + (y) * ringVertexCount + (x + 1));
//			idx.push_back(1 + (y + 1) * ringVertexCount + (x + 1));
//		}
//	}
//
//	// ���� �ε���
//	uint32 bottomIndex = static_cast<uint32>(vec.size()) - 1;
//	uint32 lastRingStartIndex = bottomIndex - ringVertexCount;
//	for (uint32 i = 0; i < sliceCount; ++i)
//	{
//		//  [last+i]-[last+i+1]
//		//  |      /
//		//  [bottom]
//		idx.push_back(bottomIndex);
//		idx.push_back(lastRingStartIndex + i);
//		idx.push_back(lastRingStartIndex + i + 1);
//	}
//
//	shared_ptr<Mesh> mesh = make_shared<Mesh>();
//	mesh->Init(vec, idx);
//	Add(L"Sphere", mesh);
//
//	return mesh;
//}

