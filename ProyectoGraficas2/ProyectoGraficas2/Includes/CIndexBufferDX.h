#pragma once
#include <d3d11.h>
#include "CIndexBuffer.h"

class CIndexBufferDX : public CIndexBuffer {

	protected:
		///
		/// Miembros
		/// 

		ID3D11Buffer* m_pIndexBuffer;

	public:
		///
		/// Métodos
		/// 
	
		///Constructor
		CIndexBufferDX() = default;
		///Destructor
		~CIndexBufferDX() = default;

friend class CGraphicApiDX;
};