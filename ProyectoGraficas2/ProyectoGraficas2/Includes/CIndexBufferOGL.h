#pragma once
#include "CIndexBuffer.h"

/// <summary>
/// EBO (Element Buffer Object)
/// </summary>
class CIndexBufferOGL : public CIndexBuffer {

	protected:
		///
		/// Métodos
		/// 
	
		/// <summary>
		/// Miembro para guardar el índice
		/// </summary>
		unsigned int m_indexBufferObject;
		/// <summary>
		/// Miembro para almacenar el tamaño
		/// </summary>
		unsigned int m_indexBufferSize;
	
	public:
		///
		/// Miembros
		///
	
		///Constructor
		CIndexBufferOGL() = default;
		///Destructor
		~CIndexBufferOGL() = default;
	friend class CGraphicApiOGL;
};