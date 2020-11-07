#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include "CGraphicApi.h"
#include "CPixelShader.h"
#include "CVertexShader.h"
#include "CConstantBuffer.h"
#include "CTexture.h"

#include "glad/glad.h"
#include "stb_image.h"

class CGraphicApiOGL : public CGraphicApi {

	private:
		///
		/// Miembros
		/// 

		uint32_t m_rendererID;

	public:
		///
		/// Métodos
		/// 
		
		///Constructor
		CGraphicApiOGL() = default;
		///Destructor
		~CGraphicApiOGL() = default;

		///
		/// H E R E N C I A
		/// 
		
		bool InitDevice(HWND& _hWnd)override;
		
		void DrawIndex(unsigned int _indexCountDX,
			unsigned int _startIndexLocationDX,
			unsigned int _baseVertexLocationDX)override;
		
		void SwapChainPresent(unsigned int _syncIntervalDX,
			unsigned int _flagsDX)override;
		
		CTexture* LoadTextureFromFile(const std::string _srcFile)override;
		
		CTexture* GetDefaultBackBuffer()override;
		
		void BindOGL();
		
		void UnbindOGL();

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

		
		CPixelShader* CreatePixelShader(const std::wstring& _namePSDX,
			const std::string& _entryPointDX,
			const std::string& _fragmentSrcOGL)override;
		
		CVertexShader* CreateVertexShader(const std::wstring& _nameVSDX,
			const std::string& _entryPointDX,
			const std::string& _vertexSrcOGL)override;
		
		CVertexBuffer* CreateVertexBuffer(const std::vector <SimpleVertex>& _simpleVertexDX)override;
		
		CIndexBuffer* CreateIndexBuffer(const std::vector <uint32_t>& _simpleIndexDX)override;
		
		CConstantBuffer* CreateConstantBuffer(const unsigned int _bufferSizeDX)override;
		
		CTexture* CreateTexture(const unsigned int _widthDX,
			const unsigned int _heightDX,
			const unsigned int _bindFlagsDX,
			TEXTURE_FORMAT _textureFormatDX)override;
		
		CSamplerState* CreateSamplerState()override;
	
		CInputLayout* CreateInputLayout(CVertexShader& _vertexShaderDX)override;

		///
		/// S E T´s 
		/// 

		
		void SetPixelShader(CPixelShader& _pixelShaderDX)override;
		
		void SetVertexShader(CVertexShader& _vertexShaderDX)override;
		
		void SetVertexBuffer(CVertexBuffer& _vertexBufferDX)override;
		
		void SetIndexBuffer(CIndexBuffer& _indexBufferDX)override;
		
		void SetConstantBuffer(CConstantBuffer& _constantBufferDX,
			const unsigned int _startSlotDX,
			const unsigned int _numBuffersDX)override;
		
		void SetSamplerState(const unsigned int _startSlotDX,
			std::vector<CSamplerState*>& _samplerStateDX)override;
		
		void SetShaderResourceView(std::vector <CTexture*>& _shaderResourceViewDX,
			const unsigned int _startSlotDX,
			const unsigned int _numViewsDX)override;
		
		void SetRenderTarget(CTexture& _renderTargetDX,
			CTexture& _depthStencilDX)override;
		
		void SetDepthStencil(CTexture& _depthStencilDX,
			const unsigned int _stencilRefDX)override;
		
		void SetInputLayout(CInputLayout& _vertexLayoutDX)override;
		
		void SetViewport(const unsigned int _numViewportsDX,
			const unsigned int _widthDX, const unsigned int _heigthDX)override;
		
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