#pragma once
#include <d3d11.h>
#include "CVertexBuffer.h"

class CVertexBufferDX : public CVertexBuffer{

	public:
		///
		/// Miembros
		/// 
		ID3D11VertexShader* m_pVertexShader;

		/// 
		/// 
		/// Métodos
		/// 
		CVertexBufferDX() = default;
		~CVertexBufferDX() = default;

		void Init(const char* _vertexPath, const char* _fragmentPath,
				  const char* _geometryPath)override;
};