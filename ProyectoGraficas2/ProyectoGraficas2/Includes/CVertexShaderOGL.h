#pragma once
#include "CVertexShader.h"

class CVertexShaderOGL : public CVertexShader {

	private:
		///
		/// Miembros
		/// 

		unsigned int* m_vertexShader;

	public:
		///
		/// Métodos
		/// 

		///Constructor
		CVertexShaderOGL() = default;
		///Destructor
		~CVertexShaderOGL() = default;

friend class CGraphicApiOGL;
};