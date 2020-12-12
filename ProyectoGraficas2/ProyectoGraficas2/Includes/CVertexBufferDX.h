#pragma once
#include <d3d11.h>
#include "CVertexBuffer.h"

class CVertexBufferDX : public CVertexBuffer {

	protected:
		///
		/// Miembros
		/// 
	
		/// <summary>
		/// Miembro de DX para guardar
		/// el buffer
		/// </summary>
		ID3D11Buffer* m_pVertexBuffer;
	
	public:
		///
		/// Métodos
		/// 
	
		///Constructor
		CVertexBufferDX() = default;
		///Destructor
		~CVertexBufferDX() = default;
	
friend class CGraphicApiDX;
};