#pragma once
#include "CTexture.h"

class CTextureOGL : public CTexture{

	protected:
		///
		/// M�todos
		/// 

		/// <summary>
		/// Miembro para guardar la posici�n
		/// de la informaci�n
		/// </summary>
		unsigned int m_texture;
		/// <summary>
		/// Miembro para guardar la posici�n
		/// de la informaci�n
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
		/// M�todos
		/// 

		///Constructor
		CTextureOGL() = default;
		///Destructor
		~CTextureOGL() = default;
friend class CGraphicApiOGL;
};