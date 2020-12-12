#pragma once
#include "CShaders.h"
#include <d3d11.h>

class CShadersDX : public CShaders {

	protected:
		///
		/// Miembros
		/// 

		/// <summary>
		/// Miembro de DX para guardar
		/// el vertex shader
		/// </summary>
		ID3D11VertexShader* m_pVertexShader;
		/// <summary>
		/// Miembro de DX para guardar
		/// el blob
		/// </summary>
		ID3DBlob* m_pVSBlob;
		/// <summary>
		/// Miembro de DX para guardar
		/// el pixel shader
		/// </summary>
		ID3D11PixelShader* m_pPixelShader;
		/// <summary>
		/// Miembro de DX para guardar
		/// el blob
		/// </summary>
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