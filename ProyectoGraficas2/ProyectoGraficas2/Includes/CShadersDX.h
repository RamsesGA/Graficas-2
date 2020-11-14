#pragma once
#include "CShaders.h"
#include <d3d11.h>

class CShadersDX : public CShaders {

	protected:
		///
		/// Miembros
		/// 

		ID3D11VertexShader* m_pVertexShader;
		ID3DBlob* m_pVSBlob;
		ID3D11PixelShader* m_pPixelShader;
		ID3DBlob* m_pPSBlob;

	public:
		///
		/// Métodos
		/// 

		///Constructor
		CShadersDX() = default;
		///Destyructor
		~CShadersDX() = default;
friend class CGraphicApiDX;
};