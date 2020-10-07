#include "CBufferOGL.h"

void CBufferOGL::Init(unsigned int _bufferOGL, 
					  unsigned int _byteWidth, unsigned int _usage, 
					  unsigned int _bindFlags, unsigned int _CPUAccessFlags, 
					  unsigned int _miscFlags, unsigned int _structureByteStride,
					  const void* _pSysMem){

	///Inicialización de la variable para OGL
	m_bufferOGL = _bufferOGL;
}
