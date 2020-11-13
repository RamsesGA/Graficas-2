#pragma once
#include "CVertexBuffer.h"

class CVertexBufferOGL : public CVertexBuffer {

	private:
		///
		/// Miembros 
		/// 

		unsigned int* m_vertexBufferObject;

	public:
		///
		/// Métodos
		/// 

		///Constructor
		CVertexBufferOGL() = default;
		///Destructor
		~CVertexBufferOGL() = default;

friend class CGraphicApiOGL;
};
