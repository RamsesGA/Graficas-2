#pragma once
#include "CGraphicApi.h"
#include "CPixelShader.h"
#include "CVertexShader.h"
#include "CConstantBuffer.h"
#include "CTexture.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>

class CGraphicApiDX : public CGraphicApi{

	private:
		///
		/// Miembros
		/// 

		HWND m_hWnd;
		ID3D11Device* m_pd3dDevice;
		IDXGISwapChain* m_pSwapChain;
		ID3D11DeviceContext* m_pImmediateContext;

		CTexture* m_pDepthStencil;

	public:

		CTexture* m_pBackBuffer;

		
		///
		/// Métodos
		/// 

		///
		/// Funciones para el usuario
		/// 

		///Constructor
		CGraphicApiDX() = default;
		///Destructor
		~CGraphicApiDX() = default;

		///
		/// H E R E N C I A
		/// 

		/// <summary>
		/// Función para generar el
		/// device de DX
		/// </summary>
		/// <returns></returns>
		bool InitDevice(HWND& _hWnd)override;

		void DrawIndex(unsigned int _indexCountDX,
			unsigned int _startIndexLocationDX,
			unsigned int _baseVertexLocationDX)override;

		void SwapChainPresent(unsigned int _syncIntervalDX,
			unsigned int _flagsDX)override;

		CTexture* LoadTextureFromFile(const std::wstring _srcFile)override;

		///
		/// U P D A T E´s
		/// 
		
		void UpdateConstantBuffer(const void* _srcDataDX, 
			CConstantBuffer& _updateDataCBDX)override;

		///
		/// C L E A R´s
		/// 

		CTexture* ClearYourRenderTargetView(CTexture* _renderTargetDX)override;

		CTexture* ClearYourDepthStencilView(CTexture* _depthStencilDX)override;

		void CleanUpDevices(std::vector<CTexture*> _renderTargetView, CTexture* _depthStencilView,
			CVertexShader* _vertexShaderDX, CInputLayout* _vertexLayoutDX,
			CPixelShader* _pixelShaderDX, CVertexBuffer* _vertexBufferDX,
			CIndexBuffer* _indexBufferDX, CConstantBuffer* _neverChangesDX,
			CConstantBuffer* _changeOnResizeDX, CConstantBuffer* _changesEveryFrameDX,
			CSamplerState* _samplerDX)override;

		///
		/// C R E A T E´s 
		/// 


		/// <summary>
		/// Función para generar el
		/// pixel shader de DX
		/// </summary>
		/// <returns></returns>
		CPixelShader* CreatePixelShader(const std::wstring& _namePSDX, 
			const std::string& _entryPointDX)override;
		/// <summary>
		/// Función para generar el
		/// vertex shader de DX
		/// </summary>
		/// <returns></returns>
		CVertexShader* CreateVertexShader(const std::wstring& _nameVSDX, 
			const std::string& _entryPointDX)override;
		/// <summary>
		/// Función para generar el
		/// vertex buffer de DX
		/// </summary>
		/// <returns></returns>
		CVertexBuffer* CreateVertexBuffer(const std::vector <SimpleVertex>& _simpleVertexDX)override;
		/// <summary>
		/// Función para generar el
		/// Index buffer de DX
		/// </summary>
		/// <returns></returns>
		CIndexBuffer* CreateIndexBuffer(const std::vector <uint32_t>& _simpleIndexDX)override;
		/// <summary>
		/// Función para generar los
		/// Constant Buffer de DX
		/// </summary>
		/// <returns></returns>
		CConstantBuffer* CreateConstantBuffer(const unsigned int _bufferSizeDX)override;
		/// <summary>
		/// Función para generar lo siguiente:
		/// °ShaderResourceView
		/// °DepthStencilView
		/// °RenderTargetView
		/// </summary>
		/// <returns></returns>
		CTexture* CreateTexture(const unsigned int _widthDX, 
			const unsigned int _heightDX, 
			const unsigned int _bindFlagsDX, 
			TEXTURE_FORMAT _textureFormatDX)override;
		/// <summary>
		/// Función para generar el
		/// sampler state de DX
		/// </summary>
		/// <returns></returns>
		CSamplerState* CreateSamplerState()override;
		/// <summary>
		/// Función para generar el
		/// Input layout de DX
		/// </summary>
		/// <returns></returns>
		CInputLayout* CreateInputLayout(CVertexShader& _vertexShaderDX)override;

		///
		/// S E T´s 
		/// 

		/// <summary>
		/// Función para guardar la
		/// información del pixel shader de DX
		/// </summary>
		/// <returns></returns>
		void SetPixelShader(CPixelShader& _pixelShaderDX)override;
		/// <summary>
		/// Función para guardar la
		/// información del vertex shader de DX
		/// </summary>
		/// <returns></returns>
		void SetVertexShader(CVertexShader& _vertexShaderDX)override;
		/// <summary>
		/// Función para guardar la
		/// información del vertex buffer de DX
		/// </summary>
		/// <returns></returns>
		void SetVertexBuffer(CVertexBuffer& _vertexBufferDX)override;
		/// <summary>
		/// Función para guardar la
		/// información del index buffer de DX
		/// </summary>
		/// <returns></returns>
		void SetIndexBuffer(CIndexBuffer& _indexBufferDX)override;
		/// <summary>
		/// Función para guardar la
		/// información de los Constant Buffers de DX
		/// </summary>
		/// <returns></returns>
		void SetConstantBuffer(CConstantBuffer& _constantBufferDX, 
			const unsigned int _startSlotDX, 
			const unsigned int _numBuffersDX)override;
		/// <summary>
		/// Función para guardar la
		/// información del sampler state de DX
		/// </summary>
		/// <returns></returns>
		void SetSamplerState(const unsigned int _startSlotDX, 
			std::vector<CSamplerState*>& _samplerStateDX)override;
		/// <summary>
		/// Función para guardar la información
		/// del shader resource view
		/// </summary>
		void SetShaderResourceView(std::vector <CTexture*>& _shaderResourceViewDX,
			const unsigned int _startSlotDX,
			const unsigned int _numViewsDX)override;
		/// <summary>
		/// Función para guardar la información
		/// del render target
		/// </summary>
		void SetRenderTarget(CTexture& _renderTargetDX,
			CTexture& _depthStencilDX)override;
		/// <summary>
		/// Función para gaurdar la información
		/// del depth stencil
		/// </summary>
		void SetDepthStencil(CTexture& _depthStencilDX,
			const unsigned int _stencilRefDX)override;
		/// <summary>
		/// Función para guardar la
		/// información del input layout de DX
		/// </summary>
		/// <returns></returns>
		void SetInputLayout(CInputLayout& _vertexLayoutDX)override;
		/// <summary>
		/// Función para guardar la
		/// información del viewport de DX
		/// </summary>
		void SetViewport(const unsigned int _numViewportsDX,
			const unsigned int _widthDX, const unsigned int _heigthDX)override;
		/// <summary>
		/// Función para guardar la información
		/// de la topología
		/// </summary>
		void SetPrimitiveTopology(const unsigned int _topologyDX)override;

		void SetYourVS(CVertexShader& _vertexShaderDX)override;

		void SetYourVSConstantBuffers(CConstantBuffer* _constantBufferDX,
			const unsigned int _startSlotDX,
			const unsigned int _numBuffersDX)override;

		void SetYourPS(CPixelShader& _pixelShaderDX)override;

		void SetYourPSConstantBuffers(CConstantBuffer* _constantBufferDX,
			const unsigned int _startSlotDX,
			const unsigned int _numBuffersDX)override;

		void SetYourPSSampler(CSamplerState& _samplerDX,
			const unsigned int _startSlotDX,
			const unsigned int _numSamplersDX)override;
};