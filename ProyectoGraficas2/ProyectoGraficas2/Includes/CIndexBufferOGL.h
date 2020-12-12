#pragma once
#include "CIndexBuffer.h"

/// <summary>
/// EBO (Element Buffer Object)
/// </summary>
class CIndexBufferOGL : public CIndexBuffer {

	protected:
		///
		/// M�todos
		/// 
	
		/// <summary>
		/// Miembro para guardar el �ndice
		/// </summary>
		unsigned int m_indexBufferObject;
		/// <summary>
		/// Miembro para almacenar el tama�o
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