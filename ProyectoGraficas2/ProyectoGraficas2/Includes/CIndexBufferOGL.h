#pragma once
#include "CIndexBuffer.h"

/// <summary>
/// También se le conoce como 
/// PBO (Pixel Buffer Object)
/// ó
/// EBO (Element Buffer Object)
/// </summary>
class CIndexBufferOGL : public CIndexBuffer {

	private:
		///
		/// Métodos
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