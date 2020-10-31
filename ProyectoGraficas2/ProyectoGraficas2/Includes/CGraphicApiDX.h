#pragma once
#include "CGraphicApi.h"
#include "CPixelShader.h"
#include "CVertexShader.h"
#include "CConstantBuffer.h"
#include "CTexture.h"


#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>

class CGraphicApiDX : public CGraphicApi{

	public:
		///
		/// Miembros
		/// 
		
		///
		/// Propios de DX
		/// 
		 
		UINT m_width;
		UINT m_height;

		HWND m_hWnd;

		HINSTANCE m_hInst;

		ID3D11Device* m_pd3dDevice;
		IDXGISwapChain* m_pSwapChain;
		D3D_FEATURE_LEVEL m_featureLevel;
		ID3D11DeviceContext* m_pImmediateContext;
		std::vector<D3D_DRIVER_TYPE> m_driverType;



		
		ID3D11Texture2D* m_pDepthStenciloverride;
		ID3D11InputLayout* m_pVertexLayoutoverride;
		ID3D11SamplerState* m_pSamplerLinearoverride;
		

		ID3D11ShaderResourceView* m_pTextureRVoverride;
		ID3D11DepthStencilView* m_pDepthStencilViewoverride;
		ID3D11RenderTargetView* m_pRenderTargetViewoverride;
		
		///
		/// Métodos
		/// 

		///Constructor
		CGraphicApiDX() = default;
		///Destructor
		~CGraphicApiDX() = default;

		HRESULT CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint,
									  LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

		///
		/// H E R E N C I A
		/// 
		
		/// <summary>
		/// Función principal, aquí mandaré a crear
		/// el init window y el device
		/// </summary>
		/// <returns></returns>
		bool MainInit()override;
		/// <summary>
		/// Función para generar una 
		/// ventana para DX
		/// </summary>
		/// <returns></returns>
		bool InitWindow()override;
		/// <summary>
		/// Función para generar el
		/// device de DX
		/// </summary>
		/// <returns></returns>
		bool InitDevice()override;
		/// <summary>
		/// Función para generar el
		/// pixel shader de DX
		/// </summary>
		/// <returns></returns>
		CPixelShader* CreatePixelShader(std::wstring _namePS,
										std::string _entryPoint)override;
		/// <summary>
		/// Función para generar el
		/// vertex shader de DX
		/// </summary>
		/// <returns></returns>
		CVertexShader* CreateVertexShader(std::wstring _nameVS, 
										  std::string _entryPoint)override;
		/// <summary>
		/// Función para generar el
		/// vertex buffer de DX
		/// </summary>
		/// <returns></returns>
		CVertexBuffer* CreateVertexBuffer(unsigned int _bufferSize,
										  std::vector <SimpleVertex> _simpleVertex)override;
		/// <summary>
		/// Función para generar el
		/// Index buffer de DX
		/// </summary>
		/// <returns></returns>
		CIndexBuffer* CreateIndexBuffer(unsigned int _bufferSize,
										std::vector <unsigned int> _simpleIndex)override;
		/// <summary>
		/// Función para generar los
		/// Constant Buffer de DX
		/// </summary>
		/// <returns></returns>
		CConstantBuffer* CreateConstantBuffer(unsigned int _bufferSize)override;
		/// <summary>
		/// Función para generar la
		/// textura 2D de DX
		/// </summary>
		/// <returns></returns>
		CTexture* CreateTexture(unsigned int _width,
								unsigned int _height,
								unsigned int _bindFlags,
								TEXTURE_FORMAT _textureFormat)override;
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
		bool CreateInputLayout()override;

		///
		/// S E T´s 
		/// 

		/// <summary>
		/// Función para guardar la
		/// información del pixel shader de DX
		/// </summary>
		/// <returns></returns>
		void SetPixelShader(CPixelShader * _pixelShader)override;
		/// <summary>
		/// Función para guardar la
		/// información del vertex shader de DX
		/// </summary>
		/// <returns></returns>
		void SetVertexShader(CVertexShader * _vertexShader)override;
		/// <summary>
		/// Función para guardar la
		/// información del vertex buffer de DX
		/// </summary>
		/// <returns></returns>
		void SetVertexBuffer(CVertexBuffer* _vertexBuffer)override;
		/// <summary>
		/// Función para guardar la
		/// información del index buffer de DX
		/// </summary>
		/// <returns></returns>
		void SetIndexBuffer(CIndexBuffer* _indexBuffer)override;
		/// <summary>
		/// Función para guardar la
		/// información de los Constant Buffers de DX
		/// </summary>
		/// <returns></returns>
		void SetConstantBuffer(CConstantBuffer* _constantBuffer,
							   unsigned int _startSlot,
							   unsigned int _numBuffers)override;
		/// <summary>
		/// Función para guardar la
		/// información de la textura 2D de DX
		/// </summary>
		/// <returns></returns>
		void SetTexture(CTexture* _texture)override;
		/// <summary>
		/// Función para guardar la
		/// información del sampler state de DX
		/// </summary>
		/// <returns></returns>
		void SetSamplerState(unsigned int _startSlot,
							 std::vector<CSamplerState*>& _samplerState)override;
		/// <summary>
		/// Función para guardar la
		/// información del input layout de DX
		/// </summary>
		/// <returns></returns>
		void SetInputLayout()override;
};