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
	
		unsigned int m_indexBufferObject;
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