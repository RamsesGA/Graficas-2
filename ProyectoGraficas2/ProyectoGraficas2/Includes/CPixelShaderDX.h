#pragma once
#include "CPixelShader.h"
#include <d3d11.h>

class CPixelShaderDX : public CPixelShader {

	protected:
		///
		/// Miembros
		/// 

		ID3D11PixelShader* m_pPixelShader;
		ID3DBlob* m_pPSBlob;

	public:
		///
		/// Métodos
		/// 

		///Constructor
		CPixelShaderDX() = default;
		///Destructor
		~CPixelShaderDX() = default;

friend class CGraphicApiDX;
};