#pragma once
#include "CInputLayout.h"
#include <d3d11.h>

class CInputLayoutDX : public CInputLayout {

	protected:
		///
		/// Miembros
		/// 
	
		/// <summary>
		/// Miembro de DX para guardar
		/// el vertex layout
		/// </summary>
		ID3D11InputLayout* m_pVertexLayout;
		/// <summary>
		/// Miembro de DX para guardar
		/// el byte off set
		/// </summary>
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