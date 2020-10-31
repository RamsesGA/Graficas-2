#pragma once
#include <d3d11.h>
#include "CIndexBuffer.h"

class CIndexBufferDX : public CIndexBuffer {

	public:
		///
		/// Miembros
		/// 
	
		ID3D11Buffer* m_pIndexBuffer;
		///
		/// Métodos
		/// 
	
		///Constructor
		CIndexBufferDX() = default;
		///Destructor
		~CIndexBufferDX() = default;
};