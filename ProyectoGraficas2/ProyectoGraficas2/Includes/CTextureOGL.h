#pragma once
#include "CTexture.h"

class CTextureOGL : public CTexture{

	private:
		///
		/// M�todos
		/// 

		unsigned int* m_texture;
		unsigned char* m_data;

	public:
		///
		/// M�todos
		/// 

		///Constructor
		CTextureOGL() = default;
		///Destructor
		~CTextureOGL() = default;
friend class CGraphicApiOGL;
};