#include "..\Includes\CTexturesOGL.h"

void CTexturesOGL::Init(unsigned int _texture,
						unsigned int _width, unsigned int _height,
						unsigned int _mipLevels, unsigned int _arraySize,
						unsigned int _format, unsigned int _sampleDescCount,
						unsigned int _sampleDescQuality, unsigned int _usage,
						unsigned int _bindFlags, unsigned int _cpuAccessFlags,
						unsigned int _miscFlags, const void* _pSysMem){

	m_texture = _texture;
}