#pragma once
#include <string>
#include "CBuffer.h"
#include "CTextures.h"
#include "CVertexBuffer.h"
#include "CInputLayout.h"
#include "CSampleState.h"
#include "CSwapChain.h"

/// <summary>
/// Clase padre donde podremos añadir 
/// nuevas funciones para generalizar
/// una api gráfica
/// </summary>
class CGraphicApi {

	private:
	
	public:
		///
		///Métodos
		/// 
		CGraphicApi() = default;
		~CGraphicApi() = default;

		virtual void Init() = 0;

		virtual void Update() = 0;

		virtual void Delete() = 0;
	
		///
		/// Create
		/// 
		
		
		/// <summary>
		/// Creates a buffer (vertex buffer, 
		/// index buffer, or shader-constant buffer).
		/// </summary>
		/// <returns></returns>
		virtual int GACreateBuffer(unsigned int _bufferOGL,
								   unsigned int _byteWidth, unsigned int _usage,
								   unsigned int _bindFlags, unsigned int _CPUAccessFlags,
								   unsigned int _miscFlags, unsigned int _structureByteStride,
								   const void* _pSysMem, CBuffer* _pBuffer) = 0;
		/// <summary>
		/// Create an array of textures.
		/// </summary>
		/// <returns></returns>
		virtual int GACreateTexture2D(unsigned int _texture,
									  unsigned int _width, unsigned int _height,
									  unsigned int _mipLevels, unsigned int _arraySize,
									  unsigned int _format, unsigned int _sampleDescCount,
									  unsigned int _sampleDescQuality, unsigned int _usage, 
									  unsigned int _bindFlags, unsigned int _cpuAccessFlags, 
									  unsigned int _miscFlags, const void* _pSysMem, 
									  CTextures* _pTexture) = 0;
		/// <summary>
		/// Create a vertex-shader object from a compiled shader.
		/// </summary>
		/// <returns></returns>
		virtual int GACreateVertexShader(unsigned int _shaderType) = 0;
		/// <summary>
		/// Create a pixel shader.
		/// </summary>
		/// <returns></returns>
		virtual int GACreatePixelShader(unsigned int _shaderType) = 0;
		/// <summary>
		/// Create an input-layout object to describe 
		/// the input-buffer data for the input-assembler stage.
		/// 
		/// ---FALTA OGL
		/// </summary>
		/// <returns></returns>
		virtual int GACreateInputLayout(char* _semanticName, unsigned int _semanticIndex,
										unsigned int _format, unsigned int _inputSlot,
										unsigned int _alignedByteOffset, unsigned int _inputSlotClass,
										unsigned int _instanceDataStepRate, unsigned int _numElements,
										CInputLayout** _ppInputLayout) = 0;
		/// <summary>
		/// Create a sampler-state object 
		/// that encapsulates sampling information for a texture.
		/// </summary>
		/// <returns></returns>
		virtual int GACreateSamplerState(unsigned int* _sampler,
										 unsigned int _filter, unsigned int _addresU,
										 unsigned int _addressV, unsigned int _addressW,
										 unsigned int _camparisionFunc, float _minLOD, 
										 float _maxLOD, CSampleState** _ppSamplerState) = 0;
		/// <summary>
		/// The depth-stencil view to bind to the device
		/// </summary>
		/// <returns></returns>
		virtual int GACreateDepthStencilView(unsigned int _mipSliceTex2D, unsigned int m_viewDimension,
											 unsigned int _format) = 0;
		/// <summary>
		/// Creates a render-target view for accessing resource data.
		/// </summary>
		/// <returns></returns>
		virtual int GACreateRenderTargetView() = 0;
		/// <summary>
		/// Create a shader-resource view for accessing data in a resource.
		/// </summary>
		/// <returns></returns>
		virtual int GACreateShaderResourceViewFromFile(const char _pSrcFile,
													   std::string _shaderNameOGL, unsigned int _idOGL) = 0;
		/// <summary>
		/// Creates a device that represents the display adapter.
		/// </summary>
		/// <returns></returns>
		virtual int GACreateDeviceAndSwapChain(unsigned int _driverType, unsigned int _flags,
			unsigned int* _pFeatureLevels, unsigned int _featureLevels,
			unsigned int _sdkVersion, unsigned int _bufferCount,
			unsigned int _width, unsigned int _height,
			unsigned int _format, unsigned int _numerator,
			unsigned int _denominator, unsigned int _bufferUsage,
			int* _hwnd, unsigned int _count,
			unsigned int _quality, bool _windowed,
			CSwapChain** _ppSwapChain, unsigned int* _pFeatureLevel) = 0;
	
		///
		/// Set
		/// 
		
		/// <summary>
		/// Set an input-layout object to describe 
		/// the input-buffer data for the input-assembler stage.
		/// </summary>
		/// <returns></returns>
		virtual int GAIASetInputLayout() = 0;
};