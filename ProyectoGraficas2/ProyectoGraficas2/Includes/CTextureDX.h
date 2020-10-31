#pragma once
#include "CTexture.h"
#include <d3d11.h>

class CTextureDX : public CTexture {

	public:
		///
		/// Miembros
		///

		ID3D11Texture2D* m_pTexture;
		ID3D11ShaderResourceView* m_pShaderResourceView;
		ID3D11DepthStencilView* m_pDepthStencilView;
		ID3D11RenderTargetView* m_pRenderTargetView;

		/// 
		/// Métodos
		/// 

		///Constructor
		CTextureDX() = default;
		///Destructor
		~CTextureDX() = default;
};