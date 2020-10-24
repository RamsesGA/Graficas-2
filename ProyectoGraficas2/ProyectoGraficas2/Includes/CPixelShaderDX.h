#pragma once
#include "CPixelShader.h"
#include <d3d11.h>

class CPixelShaderDX : public CPixelShader {

	public:
		///
		/// Miembros
		/// 

		/// <summary>
		/// Miembro de DX
		/// pixel shader
		/// </summary>
		ID3D11PixelShader* m_pPixelShader;


		///
		/// Métodos
		/// 

		///Constructor
		CPixelShaderDX() = default;
		///Destructor
		~CPixelShaderDX() = default;
};