#pragma once
#include "CInputLayout.h"
#include <d3d11.h>

class CInputLayoutDX : public CInputLayout {

	protected:
		///
		/// Miembros
		/// 
	
		ID3D11InputLayout* m_pVertexLayout;
		unsigned int* inputLayoutByteLength;

	public:
		///
		/// Métodos
		/// 
		
		///Constructor
		CInputLayoutDX() = default;
		///Destructor
		~CInputLayoutDX() = default;

friend class CGraphicApiDX;
};