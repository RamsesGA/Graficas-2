#pragma once
#include "CBuffer.h"
#include <d3d11.h>

class CBufferDX : public CBuffer {

	public:
		///
		/// Miembros
		/// 
		
		ID3D11Buffer* m_pIndexBuffer;
		ID3D11Buffer* m_pVertexBuffer;
		ID3D11Buffer* m_pCBNeverChanges;
		ID3D11Buffer* m_pCBChangeOnResize;
		ID3D11Buffer* m_pCBChangesEveryFrame;

		/// 
		/// Métodos
		/// 

		///Constructor
		CBufferDX() = default;
		///Destructor
		~CBufferDX() = default;
};