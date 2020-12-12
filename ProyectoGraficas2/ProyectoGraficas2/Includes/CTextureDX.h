#pragma once
#include "CTexture.h"
#include <d3d11.h>

class CTextureDX : public CTexture {

	protected:
		///
		/// Miembros
		///

		/// <summary>
		/// Miembro de DX para guardar
		/// la textura
		/// </summary>
		ID3D11Texture2D* m_pTexture;
		/// <summary>
		/// Miembro de DX para guardar
		/// el shader resource view
		/// </summary>
		ID3D11ShaderResourceView* m_pShaderResourceView;
		/// <summary>
		/// Miembro de DX para guardar
		/// el depth stencil view
		/// </summary>
		ID3D11DepthStencilView* m_pDepthStencilView;
		/// <summary>
		/// Miembro de DX para guardar
		/// el render target view
		/// </summary>
		ID3D11RenderTargetView* m_pRenderTargetView;
		/// <summary>
		/// Miembro de DX para guardar
		/// el depth stencil state
		/// </summary>
		ID3D11DepthStencilState* m_pDepthStencilState;

	public:
		/// 
		/// Métodos
		/// 

		///Constructor
		CTextureDX() = default;
		///Destructor
		~CTextureDX() = default;

friend class CGraphicApiDX;
};