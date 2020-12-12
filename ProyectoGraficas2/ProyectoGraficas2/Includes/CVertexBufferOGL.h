#pragma once
#include "CVertexBuffer.h"

class CVertexBufferOGL : public CVertexBuffer {

	protected:
		///
		/// Miembros 
		/// 
	
		/// <summary>
		/// Miembro para guardar la posici�n
		/// de la informaci�n
		/// <summary>
		unsigned int m_vertexBufferObject;
		/// <summary>
		/// Miembro para el tama�o
		/// <summary>
		unsigned int m_vertexBufferSize;
	
	public:
		///
		/// M�todos
		/// 
	
		///Constructor
		CVertexBufferOGL() = default;
		///Destructor
		~CVertexBufferOGL() = default;
	
friend class CGraphicApiOGL;
};
