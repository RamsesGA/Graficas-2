#include "../Includes/CGraphicApiOGL.h"
#include "../Includes/CBufferOGL.h"

int CGraphicApiOGL::GACreateBuffer(unsigned int _bufferOGL, 
								   unsigned int _byteWidth, unsigned int _usage, 
								   unsigned int _bindFlags, unsigned int _CPUAccessFlags, 
								   unsigned int _miscFlags, unsigned int _structureByteStride, 
								   const void* _pSysMem, CBuffer* _pBuffer){
	
	glBindBuffer(GL_ARRAY_BUFFER, _bufferOGL);
	return 0;
}

int CGraphicApiOGL::GACreateTexture2D(unsigned int _texture,
									  unsigned int _width, unsigned int _height,
									  unsigned int _mipLevels, unsigned int _arraySize,
									  unsigned int _format, unsigned int _sampleDescCount,
									  unsigned int _sampleDescQuality, unsigned int _usage,
									  unsigned int _bindFlags, unsigned int _cpuAccessFlags,
									  unsigned int _miscFlags, const void* _pSysMem,
									  CTextures* _pTexture){

	glBindTexture(GL_TEXTURE_2D, _texture);
	return 0;
}

int CGraphicApiOGL::GACreateVertexShader(const char* _vertexPath, const char* _fragmentPath, 
										 const char* _geometryPath){
	
	
	return 0;
}
