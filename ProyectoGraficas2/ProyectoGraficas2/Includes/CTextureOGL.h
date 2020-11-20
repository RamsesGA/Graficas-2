#pragma once
#include "CTexture.h"

class CTextureOGL : public CTexture{

	protected:
		///
		/// Métodos
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
		/// Métodos
		/// 

		///Constructor
		CTextureOGL() = default;
		///Destructor
		~CTextureOGL() = default;
friend class CGraphicApiOGL;
};