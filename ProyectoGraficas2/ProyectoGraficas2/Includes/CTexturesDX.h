#pragma once
#include "CTextures.h"
#include <d3d11.h>

class CTexturesDX : public CTextures{

	public:
		///
		/// Miembros 
		/// 
		unsigned int m_width;
		unsigned int m_height;
		unsigned int m_mipLevels;
		unsigned int m_arraySize;
		unsigned int m_format;
		unsigned int m_sampleDescCount;
		unsigned int m_sampleDescQuality;
		unsigned int m_usage;
		unsigned int m_bindFlags;
		unsigned int m_cpuAccessFlags;
		unsigned int m_miscFlags;

		ID3D11Texture2D* m_pDepthStencil;

		///
		/// Métodos
		/// 
		CTexturesDX() = default;
		~CTexturesDX() = default;

		void Init(unsigned int _texture,
				  unsigned int _width, unsigned int _height,
				  unsigned int _mipLevels, unsigned int _arraySize,
				  unsigned int _format, unsigned int _sampleDescCount,
				  unsigned int _sampleDescQuality, unsigned int _usage,
				  unsigned int _bindFlags, unsigned int _cpuAccessFlags,
				  unsigned int _miscFlags, const void* _pSysMem)override;
};