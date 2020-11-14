#pragma once
#include "CTexture.h"

class CTextureOGL : public CTexture{

	protected:
		///
		/// Métodos
		/// 

		unsigned int* m_texture;
		unsigned char* m_data;

	public:
		///
		/// Métodos
		/// 

		///Constructor
		CTextureOGL() = default;
		///Destructor
		~CTextureOGL() = default;
friend class CGraphicApiOGL;
};