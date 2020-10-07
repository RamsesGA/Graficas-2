#pragma once
#include <d3d11.h>
#include "CBuffer.h"
#include "glew-2.1.0/include/GL/glew.h"

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
		/// Creates a device that represents the display adapter.
		/// </summary>
		/// <returns></returns>
		virtual int GACreateDeviceAndSwapChain() = 0;
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
		/// Create an array of 3D textures.
		/// </summary>
		/// <returns></returns>
		virtual int GACreateTexture3D(const D3D11_TEXTURE3D_DESC* _pDesc,
									  const D3D11_SUBRESOURCE_DATA* _pInitialData,
									  ID3D11Texture3D** _ppTexture3D) = 0;
		/// <summary>
		/// Create a pixel shader.
		/// </summary>
		/// <returns></returns>
		virtual int GACreatePixelShader(const void* _pShaderBytecode,
										SIZE_T _bytecodeLength,
										ID3D11ClassLinkage* _pClassLinkage,
										ID3D11PixelShader** _ppPixelShader) = 0;
		/// <summary>
		/// Create an input-layout object to describe 
		/// the input-buffer data for the input-assembler stage.
		/// </summary>
		/// <returns></returns>
		virtual int GACreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* _pInputElementDescs,
										unsigned int _numElements,
										const void* _pShaderBytecodeWithInputSignature,
										SIZE_T _bytecodeLength,
										ID3D11InputLayout** _ppInputLayout) = 0;
		/// <summary>
		/// Create a vertex-shader object from a compiled shader.
		/// </summary>
		/// <returns></returns>
		virtual int GACreateVertexShader(const void* _pShaderBytecode,
										 SIZE_T _bytecodeLength,
										 ID3D11ClassLinkage* _pClassLinkage,
										 ID3D11VertexShader** _ppVertexShader) = 0;
		/// <summary>
		/// Create a sampler-state object 
		/// that encapsulates sampling information for a texture.
		/// </summary>
		/// <returns></returns>
		virtual int GACreateSamplerState(const D3D11_SAMPLER_DESC* _pSamplerDesc,
										 ID3D11SamplerState** _ppSamplerState) = 0;
		/// <summary>
		/// Create a depth-stencil state object that encapsulates 
		/// depth-stencil test information for the output-merger stage.
		/// </summary>
		/// <returns></returns>
		virtual int GACreateDepthStencil(const D3D11_DEPTH_STENCIL_DESC* _pDepthStencilDesc,
										 ID3D11DepthStencilState** _ppDepthStencilState) = 0;
		/// <summary>
		/// Create a rasterizer state object that 
		/// tells the rasterizer stage how to behave.
		/// </summary>
		/// <returns></returns>
		virtual int GACreateRasterizerState(const D3D11_RASTERIZER_DESC* _pRasterizerDesc,
											ID3D11RasterizerState**_ppRasterizerState) = 0;
		/// <summary>
		/// Creates a deferred context, which can record command lists.
		/// </summary>
		/// <returns></returns>
		virtual int GACreateDeferredContext(unsigned int _contextFlags,
											ID3D11DeviceContext** _ppDeferredContext) = 0;
		/// <summary>
		/// Creates a render-target view for accessing resource data.
		/// </summary>
		/// <returns></returns>
		virtual int GACreateRenderTargetView(ID3D11Resource* _pResource,
											 const D3D11_RENDER_TARGET_VIEW_DESC* _pDesc,
											 ID3D11RenderTargetView** _ppRTView) = 0;
		/// <summary>
		/// The depth-stencil view to bind to the device
		/// </summary>
		/// <returns></returns>
		virtual int GACreateDepthStencilView(ID3D11Resource* _pResource,
											 const D3D11_DEPTH_STENCIL_VIEW_DESC* _pDesc,
											 ID3D11DepthStencilView** _ppDepthStencilView) = 0;
		/// <summary>
		/// Create a shader-resource view for accessing data in a resource.
		/// </summary>
		/// <returns></returns>
		virtual int GACreateShaderResourceView(ID3D11Resource* _pResource,
											   const D3D11_SHADER_RESOURCE_VIEW_DESC* _pDesc,
											   ID3D11ShaderResourceView** _ppSRView) = 0;
	
		///
		/// Set
		/// 
		
		/// <summary>
		/// Set a device that represents the display adapter.
		/// </summary>
		/// <returns></returns>
		virtual int GASetDeviceAndSwapChain() = 0;
		/// <summary>
		/// Set a buffer (vertex buffer, 
		/// index buffer, or shader-constant buffer).
		/// </summary>
		/// <returns></returns>
		virtual int GASetBuffer() = 0;
		/// <summary>
		/// Set an array of 3D textures.
		/// </summary>
		/// <returns></returns>
		virtual int GASetTexture3D() = 0;
		/// <summary>
		/// Set a pixel shader.
		/// </summary>
		/// <returns></returns>
		virtual int GASetPixelShader() = 0;
		/// <summary>
		/// Set an input-layout object to describe 
		/// the input-buffer data for the input-assembler stage.
		/// </summary>
		/// <returns></returns>
		virtual int GASetInputLayout() = 0;
		/// <summary>
		/// Set a vertex-shader object from a compiled shader.
		/// </summary>
		/// <returns></returns>
		virtual int GASetVertexShader() = 0;
		/// <summary>
		/// Set a sampler-state object 
		/// that encapsulates sampling information for a texture.
		/// </summary>
		/// <returns></returns>
		virtual int GASetSamplerState() = 0;
		/// <summary>
		/// Set a depth-stencil state object that encapsulates 
		/// depth-stencil test information for the output-merger stage.
		/// </summary>
		/// <returns></returns>
		virtual int GASetDepthStencil() = 0;
		/// <summary>
		/// Set a render-target view for accessing resource data.
		/// </summary>
		/// <returns></returns>
		virtual int GASetRenderTarget() = 0;
		/// <summary>
		/// Set a rasterizer state object that 
		/// tells the rasterizer stage how to behave.
		/// </summary>
		/// <returns></returns>
		virtual int GASetRasterizerState() = 0;
		/// <summary>
		/// Set a deferred context, which can record command lists.
		/// </summary>
		/// <returns></returns>
		virtual int GASetDeferredContext() = 0;
		/// <summary>
		/// Sets a render-target view for accessing resource data.
		/// </summary>
		/// <returns></returns>
		virtual int GASetRenderTargetView() = 0;
		/// <summary>
		/// Set the depth-stencil view to bind to the device
		/// </summary>
		/// <returns></returns>
		virtual int GASetDepthStencilView() = 0;
		/// <summary>
		/// Set a shader-resource view for accessing data in a resource.
		/// </summary>
		/// <returns></returns>
		virtual int GASetShaderResourceView() = 0;
};