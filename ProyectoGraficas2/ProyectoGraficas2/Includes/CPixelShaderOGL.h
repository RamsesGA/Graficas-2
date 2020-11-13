#pragma once
#include "CPixelShader.h"

class CPixelShaderOGL : public CPixelShader {

	private:
		///
		///	M�todos
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