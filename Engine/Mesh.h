#pragma once
#include "Object.h"

enum MESH_TYPE : uint8
{
	NORMAL_MESH,
	LINESTRIP_MESH,
};

class Material;

// [유니티짱]과 같이 정점으로 이루어진 물체
class Mesh : public Object
{
public:
	Mesh();
	virtual ~Mesh();

	void Init(const vector<Vertex>& vertexBuffer, const vector<uint32>& indexbuffer);
	void Render(MESH_TYPE meshType = NORMAL_MESH);

private:
	void CreateVertexBuffer(const vector<Vertex>& buffer);
	void CreateIndexBuffer(const vector<uint32>& buffer);

private:
	MESH_TYPE _meshType = NORMAL_MESH;

	ComPtr<ID3D12Resource>		_vertexBuffer;
	D3D12_VERTEX_BUFFER_VIEW	_vertexBufferView = {};
	uint32 _vertexCount = 0;

	ComPtr<ID3D12Resource>		_indexBuffer;
	D3D12_INDEX_BUFFER_VIEW		_indexBufferView;
	uint32 _indexCount = 0;
};

