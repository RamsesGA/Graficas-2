#include "..\Includes\CTexturesDX.h"

void CTexturesDX::Init(unsigned int _texture,
					   unsigned int _width, unsigned int _height,
					   unsigned int _mipLevels, unsigned int _arraySize,
					   unsigned int _format, unsigned int _sampleDescCount,
					   unsigned int _sampleDescQuality, unsigned int _usage,
					   unsigned int _bindFlags, unsigned int _cpuAccessFlags,
					   unsigned int _miscFlags, const void* _pSysMem){

	m_width	= _width;
	m_height = _height;
	m_mipLevels = _mipLevels;
	m_arraySize = _arraySize;
	m_format = (DXGI_FORMAT)_format;
	m_sampleDescCount = _sampleDescCount;
	m_sampleDescQuality = _sampleDescQuality;
	m_usage = (D3D11_USAGE)_usage;
	m_bindFlags = _bindFlags;
	m_cpuAccessFlags = _cpuAccessFlags;
	m_miscFlags = _miscFlags;

	m_pSysMem = _pSysMem;
}
