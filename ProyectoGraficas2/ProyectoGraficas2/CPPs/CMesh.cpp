#include "..\Includes\CMesh.h"
#include "..\Includes\CGraphicApi.h"


void CMesh::Init(std::vector<Vertex>* _vertices,
	std::vector<unsigned int>* _indices,
	std::vector<Texture> _textures,
	CGraphicApi* _graphicApi){

	m_vertices = _vertices;
	m_indices = _indices;
	m_textures = _textures;

	SetUpMesh(_graphicApi);
}

void CMesh::SetUpMesh(CGraphicApi* _graphicApi){

	m_vertexBuffer = _graphicApi->CreateVertexBuffer(m_vertices->data(),
		sizeof(Vertex) * m_vertices->size());

	m_indexBuffer = _graphicApi->CreateIndexBuffer(m_indices->data(),
		sizeof(unsigned int) * m_indices->size());
}

void CMesh::Draw(CGraphicApi* _graphicApi,
	std::vector <CSamplerState*> _samplerState) {

	for (unsigned int i = 0; i < m_textures.size(); i++) {

		//_graphicApi->SetSamplerState(0, _samplerState,
		//	*m_textures[i].texture);
		//
		//_graphicApi->SetShaderResourceView(m_textures[i].texture,
		//	i, 0);
	}

	_graphicApi->SetVertexBuffer(*m_vertexBuffer);
	_graphicApi->SetIndexBuffer(*m_indexBuffer);
	_graphicApi->DrawIndex(m_indices->size(), 0, 0);
}