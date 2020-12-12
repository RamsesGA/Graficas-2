#pragma once
#include "CVertexBuffer.h"

class CVertexBufferOGL : public CVertexBuffer {

	protected:
		///
		/// Miembros 
		/// 
	
		/// <summary>
		/// Miembro para guardar la posición
		/// de la información
		/// <summary>
		unsigned int m_vertexBufferObject;
		/// <summary>
		/// Miembro para el tamaño
		/// <summary>
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
