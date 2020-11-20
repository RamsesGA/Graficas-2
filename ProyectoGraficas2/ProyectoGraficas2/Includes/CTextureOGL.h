#pragma once
#include "CTexture.h"

class CTextureOGL : public CTexture{

	protected:
		///
		/// M�todos
		/// 

		unsigned int m_texture;
		unsigned char m_data;
		/// <summary>
		/// Puede ser mi render target view de DX
		/// </summary>
		unsigned int m_framebuffer;
		/// <summary>
		/// Puede ser mi depthStencil
		/// </summary>
		unsigned int m_renderBufferObject;

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