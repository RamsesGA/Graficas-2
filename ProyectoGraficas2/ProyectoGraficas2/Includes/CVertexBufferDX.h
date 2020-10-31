#pragma once
#include <d3d11.h>
#include "CVertexBuffer.h"

class CVertexBufferDX : public CVertexBuffer {

	public:
		///
		/// Miembros
		/// 
		
		ID3D11Buffer* m_pVertexBuffer;
		///
		/// Métodos
		/// 
	
		///Constructor
		CVertexBufferDX() = default;
		///Destructor
		~CVertexBufferDX() = default;
};