#pragma once
#include "CVertexBuffer.h"

class CVertexBufferOGL : public CVertexBuffer {

	protected:
		///
		/// Miembros 
		/// 
	
		unsigned int m_vertexBufferObject;
		unsigned int m_vertexBufferSize;
	
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
