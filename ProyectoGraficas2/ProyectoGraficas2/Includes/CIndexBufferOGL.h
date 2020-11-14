#pragma once
#include "CIndexBuffer.h"

/// <summary>
/// Tambi�n se le conoce como 
/// PBO (Pixel Buffer Object)
/// �
/// EBO (Element Buffer Object)
/// </summary>
class CIndexBufferOGL : public CIndexBuffer {

	protected:
		///
		/// M�todos
		/// 
	
		unsigned int* m_indexBufferObject;
	
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