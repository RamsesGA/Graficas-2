#pragma once
#include "CTexture.h"

class CTextureOGL : public CTexture{

	protected:
		///
		/// Métodos
		/// 

		/// <summary>
		/// Miembro para guardar la posición
		/// de la información
		/// </summary>
		unsigned int m_texture;
		/// <summary>
		/// Miembro para guardar la posición
		/// de la información
		unsigned char m_data;
		/// <summary>
		/// Puede ser el render target view de DX
		/// </summary>
		unsigned int m_framebuffer;
		/// <summary>
		/// Puede ser el depthStencil
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