#include "CBufferDX.h"

void CBufferDX::Init(unsigned int _bufferOGL, 
					 unsigned int _byteWidth, unsigned int _usage, 
					 unsigned int _bindFlags, unsigned int _cpuAccessFlags, 
					 unsigned int _miscFlags, unsigned int _structureByteStride,
					 const void* _pSysMem){

	///Inicialización de las variables para DX
	m_byteWidth = _byteWidth;
	m_usage =_usage;
	m_bindFlags = _bindFlags;
	m_cpuAccessFlags = _cpuAccessFlags;
	m_miscFlags = _miscFlags;
	m_structureByteStride = _structureByteStride;

	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = _pSysMem;
}