#pragma once
#include "CGraphicApi.h"
#include "CConstantBuffer.h"
#include "CTexture.h"
#include "CShaders.h"
#include "CVertexBuffer.h"
#include "CIndexBuffer.h"

#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d11shader.h>

class CGraphicApiDX : public CGraphicApi{

	private:
		///
		/// M I E M B R O S
		/// 

		/// <summary>
		/// Miembro con la información
		/// de la ventana traida del usuario
		/// </summary>
		HWND m_hWnd;
		/// <summary>
		/// Miembro representa 
		/// un adaptador virtual
		/// </summary>
		ID3D11Device* m_pd3dDevice;
		/// <summary>
		/// Miembro para implementar una o más 
		/// superficies para almacenar datos renderizados
		/// </summary>
		IDXGISwapChain* m_pSwapChain;
		/// <summary>
		/// Miembro para representar un contexto de 
		/// dispositivo que genera comandos de renderizado
		/// </summary>
		ID3D11DeviceContext* m_pImmediateContext;
		/// <summary>
		/// Miembro para almacenar y acceder a un recurso de 
		/// textura durante la prueba de plantilla en profundidad
		/// </summary>
		CTexture* m_pDepthStencil;
		/// <summary>
		/// Miembro para almacenar la textura por default al crear
		/// el device
		/// </summary>
		CTexture* m_pBackBuffer;

	public:
		///
		/// M É T O D O S
		/// 

		///Constructor
		CGraphicApiDX() = default;
		///Destructor
		~CGraphicApiDX();

		///
		/// H E R E N C I A
		/// 

		bool InitDevice(HWND _hWnd)override;

		void DrawIndex(unsigned int _indexCount,
			unsigned int _startIndexLocation,
			unsigned int _baseVertexLocation)override;

		void SwapChainPresent(unsigned int _syncInterval,
			unsigned int _flags)override;

		CTexture* LoadTextureFromFile(std::string _srcFile)override;

		CTexture* GetDefaultBackBuffer()override;

		CTexture* GetDefaultDepthStencil()override;

		void UnbindOGL()override;

		///
		/// U P D A T E´s
		/// 


		void UpdateConstantBuffer(const void* _srcData,
			CConstantBuffer& _updateDataCB)override;

		///
		/// C L E A R´s
		/// 


		void ClearYourRenderTargetView(CTexture* _renderTarget,
			float _r, float _g, float _b, float _a)override;

		void ClearYourDepthStencilView(CTexture* _depthStencil)override;

		///
		/// C R E A T E´s 
		/// 

		CShaders* CreateShadersProgram(const std::wstring& _nameVS,
			const std::string& _entryPointVS, const std::wstring& _namePS,
			const std::string& _entryPointPS)override;

		CVertexBuffer* CreateVertexBuffer(const void* _data,
			const unsigned int _size)override;

		CIndexBuffer* CreateIndexBuffer(const void* _data,
			const unsigned int _size)override;

		CConstantBuffer* CreateConstantBuffer(const unsigned int _bufferSize)override;

		CTexture* CreateTexture(const unsigned int _width,
			const unsigned int _height,
			const unsigned int _bindFlags,
			TEXTURE_FORMAT _textureFormat,
			const std::string _fileName)override;

		CSamplerState* CreateSamplerState()override;

		CInputLayout* CreateInputLayout(CShaders & _vertexShader)override;

		///
		/// S E T´s 
		/// 


		void SetPixelShader(CShaders& _pixelShader)override;

		void SetVertexShader(CShaders& _vertexShader)override;

		void SetVertexBuffer(CVertexBuffer& _vertexBuffer)override;

		void SetIndexBuffer(CIndexBuffer& _indexBuffer)override;

		void SetConstantBuffer(bool _isVertex,
			CConstantBuffer & _constantBuffer,
			const unsigned int _startSlot,
			const unsigned int _numBuffers)override;

		void SetSamplerState(const unsigned int _startSlot,
			std::vector<CSamplerState*>& _samplerState,
			CTexture & _texture)override;

		void SetShaderResourceView(CTexture * _shaderResourceView,
			const unsigned int _startSlot,
			const unsigned int _numViews)override;

		void SetRenderTarget(CTexture* _renderTarget,
			CTexture* _depthStencil)override;

		void SetDepthStencil(CTexture& _depthStencil,
			const unsigned int _stencilRef)override;

		void SetInputLayout(CInputLayout& _vertexLayout)override;

		void SetViewport(const unsigned int _numViewports,
			const unsigned int _width, const unsigned int _heigth)override;

		void SetPrimitiveTopology(const unsigned int _topology)override;

		void SetYourVS(CShaders& _vertexShader)override;

		void SetYourVSConstantBuffers(CConstantBuffer* _constantBuffer,
			const unsigned int _startSlot,
			const unsigned int _numBuffers)override;

		void SetYourPS(CShaders& _pixelShader)override;

		void SetYourPSConstantBuffers(CConstantBuffer* _constantBuffer,
			const unsigned int _startSlot,
			const unsigned int _numBuffers)override;

		void SetYourPSSampler(CSamplerState& _sampler,
			const unsigned int _startSlot,
			const unsigned int _numSamplers)override;

		void SetShaders(CShaders& _shaders)override;
};