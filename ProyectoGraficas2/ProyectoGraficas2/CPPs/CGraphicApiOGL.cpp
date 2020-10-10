#include "../Includes/CGraphicApiOGL.h"
#include "../Includes/CBufferOGL.h"
#include <iostream>
#include "../Includes/stb_image.h"

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
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// load and generate the texture
	int width, height, nrChannels;
	unsigned char* data = stbi_load("waffle.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	return 0;
}

int CGraphicApiOGL::GACreateVertexShader(unsigned int _shaderType){
	
	
	return 0;
}

int CGraphicApiOGL::GACreatePixelShader(unsigned int _shaderType){

	return 0;
}

int CGraphicApiOGL::GACreateInputLayout(char* _semanticName, 
										unsigned int _semanticIndex, unsigned int _format, 
										unsigned int _inputSlot, unsigned int _alignedByteOffset, 
										unsigned int _inputSlotClass, unsigned int _instanceDataStepRate, 
										unsigned int _numElements, CInputLayout** _ppInputLayout){

	return 0;
}

int CGraphicApiOGL::GACreateSamplerState(unsigned int* _sampler, 
										 unsigned int _filter, unsigned int _addresU, 
										 unsigned int _addressV, unsigned int _addressW, 
										 unsigned int _camparisionFunc, float _minLOD, 
										 float _maxLOD, CSampleState** _ppSamplerState){

	return 0;
}

int CGraphicApiOGL::GACreateDepthStencilView(unsigned int _mipSliceTex2D, unsigned int m_viewDimension, 
											 unsigned int _format){

	return 0;
}

int CGraphicApiOGL::GACreateRenderTargetView(){

	return 0;
}

int CGraphicApiOGL::GACreateShaderResourceViewFromFile(const char _pSrcFile, 
													   std::string _shaderNameOGL, 
													   unsigned int _idOGL){

	return 0;
}

int CGraphicApiOGL::GACreateDeviceAndSwapChain(unsigned int _driverType, unsigned int _flags, 
											   unsigned int* _pFeatureLevels, unsigned int _featureLevels, 
											   unsigned int _sdkVersion, unsigned int _bufferCount, 
											   unsigned int _width, unsigned int _height, 
											   unsigned int _format, unsigned int _numerator, 
											   unsigned int _denominator, unsigned int _bufferUsage, 
											   int* _hwnd, unsigned int _count, 
											   unsigned int _quality, bool _windowed, 
											   CSwapChain** _ppSwapChain, unsigned int* _pFeatureLevel){
	return 0;
}
