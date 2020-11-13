#pragma once
#include "CPixelShader.h"

class CPixelShaderOGL : public CPixelShader {

	private:
		///
		///	Métodos
		/// 

		unsigned int* m_fragmentShader;

	public:
		///
		/// Miembros
		/// 

		///Constructor
		CPixelShaderOGL() = default;
		///Destructor
		~CPixelShaderOGL() = default;
		
friend class CGraphicApiOGL;
};