#pragma once
#include <d3d11.h>
#include "CVertexBuffer.h"

class CVertexBufferDX : public CVertexBuffer {

	protected:
		///
		/// Miembros
		/// 
	
		ID3D11Buffer* m_pVertexBuffer;
	
	public:
		///
		/// M�todos
		/// 
	
		///Constructor
		CVertexBufferDX() = default;
		///Destructor
		~CVertexBufferDX() = default;
	
friend class CGraphicApiDX;
};