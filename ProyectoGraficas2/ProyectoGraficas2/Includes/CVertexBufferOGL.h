#pragma once
#include "CVertexBuffer.h"

class CVertexBufferOGL : public CVertexBuffer{

	public:
		///
		/// Miembros
		/// 
		unsigned int m_shaderType;
		///
		/// M�todos
		/// 
		CVertexBufferOGL() = default;
		~CVertexBufferOGL() = default;

		void Init(unsigned int _shaderType)override;
};