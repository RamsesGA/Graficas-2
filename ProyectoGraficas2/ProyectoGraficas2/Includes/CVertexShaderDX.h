#pragma once
#include "CVertexShader.h"
#include <d3d11.h>

class CVertexShaderDX : public CVertexShader {

	protected:
		///
		/// Miembros
		/// 

		ID3D11VertexShader* m_pVertexShader;
		ID3DBlob* m_pVSBlob;

	public:
		///
		/// Métodos
		/// 

		///Constructor
		CVertexShaderDX() = default;
		///Destructor
		~CVertexShaderDX() = default;

friend class CGraphicApiDX;
};