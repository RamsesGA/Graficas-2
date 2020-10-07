#pragma once
#include "CGraphicApi.h"
#include <d3d11.h>


/// <summary>
/// Clase donde manejaremos toda
/// la lógica gráfica de DirectX
/// </summary>
class CGraphicApiDX : public CGraphicApi {

	private:
		///
		/// Miembros
		/// 
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext;

	public:
		///
		///Métodos
		/// 
		CGraphicApiDX() = default;
		~CGraphicApiDX() = default;

		void Init()override;

		void Update()override {};

		void Delete()override {};

		///
		/// Create
		/// 

		/// <summary>
		/// Creates a device that represents the display adapter.
		/// </summary>
		/// <returns></returns>
		int GACreateDeviceAndSwapChain()override;
		/// <summary>
		/// Creates a buffer (vertex buffer, 
		/// index buffer, or shader-constant buffer).
		/// </summary>
		/// <returns></returns>
		int GACreateBuffer(unsigned int _bufferOGL,
						   unsigned int _byteWidth, unsigned int _usage,
						   unsigned int _bindFlags, unsigned int _CPUAccessFlags,
						   unsigned int _miscFlags, unsigned int _structureByteStride,
						   const void* _pSysMem, CBuffer* _pBuffer)override;
		/// <summary>
		/// Create an array of 3D textures.
		/// </summary>
		/// <returns></returns>
		int GACreateTexture3D(const D3D11_TEXTURE3D_DESC * _pDesc,
							  const D3D11_SUBRESOURCE_DATA * _pInitialData,
							  ID3D11Texture3D * *_ppTexture3D)override;
		/// <summary>
		/// Create a pixel shader.
		/// </summary>
		/// <returns></returns>
		int GACreatePixelShader(const void* _pShaderBytecode,
								SIZE_T _bytecodeLength,
								ID3D11ClassLinkage * _pClassLinkage,
								ID3D11PixelShader * *_ppPixelShader)override;
		/// <summary>
		/// Create an input-layout object to describe 
		/// the input-buffer data for the input-assembler stage.
		/// </summary>
		/// <returns></returns>
		int GACreateInputLayout(const D3D11_INPUT_ELEMENT_DESC * _pInputElementDescs,
								unsigned int _numElements,
								const void* _pShaderBytecodeWithInputSignature,
								SIZE_T _bytecodeLength,
								ID3D11InputLayout * *_ppInputLayout)override;
		/// <summary>
		/// Create a vertex-shader object from a compiled shader.
		/// </summary>
		/// <returns></returns>
		int GACreateVertexShader(const void* _pShaderBytecode,
								 SIZE_T _bytecodeLength,
								 ID3D11ClassLinkage * _pClassLinkage,
								 ID3D11VertexShader * *_ppVertexShader)override;
		/// <summary>
		/// Create a sampler-state object 
		/// that encapsulates sampling information for a texture.
		/// </summary>
		/// <returns></returns>
		int GACreateSamplerState(const D3D11_SAMPLER_DESC * _pSamplerDesc,
								 ID3D11SamplerState * *_ppSamplerState)override;
		/// <summary>
		/// Create a depth-stencil state object that encapsulates 
		/// depth-stencil test information for the output-merger stage.
		/// </summary>
		/// <returns></returns>
		int GACreateDepthStencil(const D3D11_DEPTH_STENCIL_DESC * _pDepthStencilDesc,
								 ID3D11DepthStencilState * *_ppDepthStencilState)override;
		/// <summary>
		/// Create a rasterizer state object that 
		/// tells the rasterizer stage how to behave.
		/// </summary>
		/// <returns></returns>
		int GACreateRasterizerState(const D3D11_RASTERIZER_DESC * _pRasterizerDesc,
									ID3D11RasterizerState * *_ppRasterizerState)override;
		/// <summary>
		/// Creates a deferred context, which can record command lists.
		/// </summary>
		/// <returns></returns>
		int GACreateDeferredContext(unsigned int _contextFlags,
									ID3D11DeviceContext * *_ppDeferredContext)override;
		/// <summary>
		/// Creates a render-target view for accessing resource data.
		/// </summary>
		/// <returns></returns>
		int GACreateRenderTargetView(ID3D11Resource * _pResource,
									 const D3D11_RENDER_TARGET_VIEW_DESC * _pDesc,
									 ID3D11RenderTargetView * *_ppRTView)override;
		/// <summary>
		/// The depth-stencil view to bind to the device
		/// </summary>
		/// <returns></returns>
		int GACreateDepthStencilView(ID3D11Resource * _pResource,
									 const D3D11_DEPTH_STENCIL_VIEW_DESC * _pDesc,
									 ID3D11DepthStencilView * *_ppDepthStencilView)override;
		/// <summary>
		/// Create a shader-resource view for accessing data in a resource.
		/// </summary>
		/// <returns></returns>
		int GACreateShaderResourceView(ID3D11Resource * _pResource,
									   const D3D11_SHADER_RESOURCE_VIEW_DESC * _pDesc,
									   ID3D11ShaderResourceView * *_ppSRView)override;

		///
		/// Set
		/// 

		/// <summary>
		/// Set a device that represents the display adapter.
		/// </summary>
		/// <returns></returns>
		int GASetDeviceAndSwapChain()override;
		/// <summary>
		/// Set a buffer (vertex buffer, 
		/// index buffer, or shader-constant buffer).
		/// </summary>
		/// <returns></returns>
		int GASetBuffer()override;
		/// <summary>
		/// Set an array of 3D textures.
		/// </summary>
		/// <returns></returns>
		int GASetTexture3D()override;
		/// <summary>
		/// Set a pixel shader.
		/// </summary>
		/// <returns></returns>
		int GASetPixelShader()override;
		/// <summary>
		/// Set an input-layout object to describe 
		/// the input-buffer data for the input-assembler stage.
		/// </summary>
		/// <returns></returns>
		int GASetInputLayout()override;
		/// <summary>
		/// Set a vertex-shader object from a compiled shader.
		/// </summary>
		/// <returns></returns>
		int GASetVertexShader()override;
		/// <summary>
		/// Set a sampler-state object 
		/// that encapsulates sampling information for a texture.
		/// </summary>
		/// <returns></returns>
		int GASetSamplerState()override;
		/// <summary>
		/// Set a depth-stencil state object that encapsulates 
		/// depth-stencil test information for the output-merger stage.
		/// </summary>
		/// <returns></returns>
		int GASetDepthStencil()override;
		/// <summary>
		/// Set a render-target view for accessing resource data.
		/// </summary>
		/// <returns></returns>
		int GASetRenderTarget()override;
		/// <summary>
		/// Set a rasterizer state object that 
		/// tells the rasterizer stage how to behave.
		/// </summary>
		/// <returns></returns>
		int GASetRasterizerState()override;
		/// <summary>
		/// Set a deferred context, which can record command lists.
		/// </summary>
		/// <returns></returns>
		int GASetDeferredContext()override;
		/// <summary>
		/// Sets a render-target view for accessing resource data.
		/// </summary>
		/// <returns></returns>
		int GASetRenderTargetView()override;
		/// <summary>
		/// Set the depth-stencil view to bind to the device
		/// </summary>
		/// <returns></returns>
		int GASetDepthStencilView()override;
		/// <summary>
		/// Set a shader-resource view for accessing data in a resource.
		/// </summary>
		/// <returns></returns>
		int GASetShaderResourceView()override;
};