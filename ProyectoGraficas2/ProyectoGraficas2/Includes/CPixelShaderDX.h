#pragma once
#include <d3d11.h>

class CPixelShaderDX {

	public:
		///
		/// Miembros
		/// 
		ID3D11PixelShader* m_pPixelShader;

		/// 
		/// Métodos
		/// 
		CPixelShaderDX() = default;
		~CPixelShaderDX()= default;
};