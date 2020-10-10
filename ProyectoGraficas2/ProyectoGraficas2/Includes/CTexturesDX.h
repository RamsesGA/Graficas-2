#pragma once
#include "CTextures.h"
#include <d3d11.h>

class CTexturesDX : public CTextures{

	public:
		///
		/// Miembros 
		/// 
		UINT m_width;
		UINT m_height;
		UINT m_mipLevels;
		UINT m_arraySize;
		DXGI_FORMAT m_format;
		UINT m_sampleDescCount;
		UINT m_sampleDescQuality;
		D3D11_USAGE m_usage;
		UINT m_bindFlags;
		UINT m_cpuAccessFlags;
		UINT m_miscFlags;

		const void* m_pSysMem;

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