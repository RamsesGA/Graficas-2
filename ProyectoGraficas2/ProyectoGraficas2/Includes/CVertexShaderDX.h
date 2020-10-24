#pragma once
#include "CVertexShader.h"
#include <d3d11.h>

class CVertexShaderDX : public CVertexShader {

	public:
		///
		/// Miembros
		/// 

		/// <summary>
		/// Miembro de DX para el
		/// vertex shader
		/// </summary>
		ID3D11VertexShader* m_pVertexShader;

		///
		/// Métodos
		/// 

		///Constructor
		CVertexShaderDX() = default;
		///Destructor
		~CVertexShaderDX() = default;
};