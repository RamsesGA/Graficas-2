#pragma once
#include "CVertexBuffer.h"

class CVertexBufferOGL : public CVertexBuffer{

	public:
		///
		/// Miembros
		/// 
		const char* m_vertexPath;
		const char* m_fragmentPath;
		const char* m_geometryPath;
		///
		/// Métodos
		/// 
		CVertexBufferOGL() = default;
		~CVertexBufferOGL() = default;

		void Init(const char* _vertexPath, const char* _fragmentPath,
				  const char* _geometryPath)override;
};