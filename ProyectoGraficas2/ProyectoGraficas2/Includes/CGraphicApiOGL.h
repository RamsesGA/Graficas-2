#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include "CGraphicApi.h"
#include "CConstantBuffer.h"
#include "CTexture.h"
#include "CShaders.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>


class CGraphicApiOGL : public CGraphicApi {

	private:
		///
		/// Miembros
		/// 

		/// <summary>
		/// 
		/// </summary>
		HDC m_HandleToDC;
		/// <summary>
		/// 
		/// </summary>
		HGLRC m_renderingContext;
		/// <summary>
		/// Miembro para almacenar
		/// la topología y que la api lo conozca
		/// </summary>
		unsigned int m_topology;

	public:
		///
		/// M É T O D O S
		///  
		
		///Constructor
		CGraphicApiOGL() = default;
		///Destructor
		~CGraphicApiOGL() = default;

		///
		/// H E R E N C I A
		/// 
		
		bool InitDevice(HWND& _hWnd)override;
		
		void DrawIndex(unsigned int _indexCount ,
			unsigned int _startIndexLocation ,
			unsigned int _baseVertexLocation )override;
		
		void SwapChainPresent(unsigned int _syncInterval ,
			unsigned int _flags )override;
		
		CTexture* LoadTextureFromFile(const std::string _srcFile)override;
		
		CTexture* GetDefaultBackBuffer()override;

		CTexture* GetDefaultDepthStencil()override;
		
		void UnbindOGL()override;

		///
		/// U P D A T E´s
		/// 

		
		void UpdateConstantBuffer(const void* _srcData ,
			CConstantBuffer& _updateDataCB )override;

		///
		/// C L E A R´s
		/// 

		
		CTexture* ClearYourRenderTargetView(CTexture* _renderTarget )override;
		
		CTexture* ClearYourDepthStencilView(CTexture* _depthStencil )override;
		
		void CleanUpDevices()override;

		///
		/// C R E A T E´s 
		/// 

		CShaders* CreateVertexAndPixelShader(const std::wstring& _nameVS,
			const std::string& _entryPointVS, const std::wstring& _namePS,
			const std::string& _entryPointPS)override;

		CVertexBuffer* CreateVertexBuffer(const std::vector <SimpleVertex>& _simpleVertex)override;
		
		CIndexBuffer* CreateIndexBuffer(const std::vector <uint32_t>& _simpleIndex)override;

		CConstantBuffer* CreateConstantBuffer(const unsigned int _bufferSize)override;
		
		CTexture* CreateTexture(const unsigned int _width ,
			const unsigned int _height ,
			const unsigned int _bindFlags ,
			TEXTURE_FORMAT _textureFormat ,
			const std::string _fileName )override;
		
		CSamplerState* CreateSamplerState()override;
	
		CInputLayout* CreateInputLayout(CShaders& _vertexShader )override;

		///
		/// S E T´s 
		/// 

		void SetPixelShader(CShaders& _pixelShader )override;
		
		void SetVertexShader(CShaders& _vertexShader )override;
		
		void SetVertexBuffer(CVertexBuffer& _vertexBuffer )override;
		
		void SetIndexBuffer(CIndexBuffer& _indexBuffer )override;
		
		void SetConstantBuffer(bool _isVertex,
			CConstantBuffer & _constantBuffer,
			const unsigned int _startSlot,
			const unsigned int _numBuffers)override;
		
		void SetSamplerState(const unsigned int _startSlot ,
			std::vector<CSamplerState*>& _samplerState,
			CTexture & _texture)override;
		
		void SetShaderResourceView(std::vector <CTexture*>& _shaderResourceView ,
			const unsigned int _startSlot ,
			const unsigned int _numViews )override;
		
		void SetRenderTarget(CTexture* _renderTarget ,
			CTexture* _depthStencil )override;
		
		void SetDepthStencil(CTexture& _depthStencil ,
			const unsigned int _stencilRef )override;
		
		void SetInputLayout(CInputLayout& _vertexLayout )override;
		
		void SetViewport(const unsigned int _numViewports ,
			const unsigned int _width , const unsigned int _heigth )override;
		
		void SetPrimitiveTopology(const unsigned int _topology )override;
		
		void SetYourVS(CShaders& _vertexShader )override;
		
		void SetYourVSConstantBuffers(CConstantBuffer* _constantBuffer ,
			const unsigned int _startSlot ,
			const unsigned int _numBuffers )override;
		
		void SetYourPS(CShaders& _pixelShader )override;
		
		void SetYourPSConstantBuffers(CConstantBuffer* _constantBuffer ,
			const unsigned int _startSlot ,
			const unsigned int _numBuffers )override;
		
		void SetYourPSSampler(CSamplerState& _sampler ,
			const unsigned int _startSlot ,
			const unsigned int _numSamplers )override;

		void SetShaders(CShaders& _shaders)override;
};