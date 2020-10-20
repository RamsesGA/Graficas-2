#pragma once
#include "CGraphicApi.h"
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

		HINSTANCE m_hInst;
		HWND m_hWnd;

		std::vector<D3D_DRIVER_TYPE> m_driverType;
		D3D_FEATURE_LEVEL m_featureLevel;
		IDXGISwapChain* m_pSwapChain;
		ID3D11Device* m_pd3dDevice;


		ID3D11Buffer* m_pCBNeverChangesoverride;
		ID3D11Buffer* m_pCBChangeOnResizeoverride;
		ID3D11Buffer* m_pCBChangesEveryFrameoverride;
		ID3D11Buffer* m_pVertexBufferoverride;
		ID3D11Buffer* m_pIndexBufferoverride;
		ID3D11Texture2D* m_pDepthStenciloverride;
		ID3D11InputLayout* m_pVertexLayoutoverride;
		ID3D11SamplerState* m_pSamplerLinearoverride;
		ID3D11VertexShader* m_pVertexShaderoverride;
		ID3D11PixelShader* m_pPixelShaderoverride;

		ID3D11DeviceContext* m_pImmediateContext;
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

		///
		/// Herencia 
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
		bool CreatePixelShader()override;
		/// <summary>
		/// Función para generar el
		/// vertex shader de DX
		/// </summary>
		/// <returns></returns>
		bool CreateVertexShader()override;
		/// <summary>
		/// Función para generar el
		/// vertex buffer de DX
		/// </summary>
		/// <returns></returns>
		bool CreateVertexBuffer()override;
		/// <summary>
		/// Función para generar el
		/// Index buffer de DX
		/// </summary>
		/// <returns></returns>
		bool CreateIndexBuffer()override;
		/// <summary>
		/// Función para generar el
		/// buffer never changes de DX
		/// </summary>
		/// <returns></returns>
		bool CreateConstBuffNeverChanges()override;
		/// <summary>
		/// Función para generar el
		/// buffer Change on resize de DX
		/// </summary>
		/// <returns></returns>
		bool CreateConstBuffChangeOnResize()override;
		/// <summary>
		/// Función para generar el
		/// buffer de change every frame de DX
		/// </summary>
		/// <returns></returns>
		bool CreateConstBuffChangeEveryFrame()override;
		/// <summary>
		/// Función para generar la
		/// textura 2D de DX
		/// </summary>
		/// <returns></returns>
		bool CreateTexture2D()override;
		/// <summary>
		/// Función para generar el
		/// Input layout de DX
		/// </summary>
		/// <returns></returns>
		bool CreateInputLayout()override;
		/// <summary>
		/// Función para generar el
		/// sampler state de DX
		/// </summary>
		/// <returns></returns>
		bool CreateSamplerState()override;

		/// <summary>
		/// Función para guardar la
		/// información del pixel shader de DX
		/// </summary>
		/// <returns></returns>
		bool SetPixelShader()override;
		/// <summary>
		/// Función para guardar la
		/// información del vertex shader de DX
		/// </summary>
		/// <returns></returns>
		bool SetVertexShader()override;
		/// <summary>
		/// Función para guardar la
		/// información del vertex buffer de DX
		/// </summary>
		/// <returns></returns>
		bool SetVertexBuffer()override;
		/// <summary>
		/// Función para guardar la
		/// información del index buffer de DX
		/// </summary>
		/// <returns></returns>
		bool SetIndexBuffer()override;
		/// <summary>
		/// Función para guardar la
		/// información del buffer never changes de DX
		/// </summary>
		/// <returns></returns>
		bool SetConstBuffNeverChanges()override;
		/// <summary>
		/// Función para guardar la
		/// información del buffer change on resize de DX
		/// </summary>
		/// <returns></returns>
		bool SetConstBuffChangeOnResize()override;
		/// <summary>
		/// Función para guardar la
		/// información del buffer change every frame de DX
		/// </summary>
		/// <returns></returns>
		bool SetConstBuffChangeEveryFrame()override;
		/// <summary>
		/// Función para guardar la
		/// información de la textura 2D de DX
		/// </summary>
		/// <returns></returns>
		bool SetTexture2D()override;
		/// <summary>
		/// Función para guardar la
		/// información del input layout de DX
		/// </summary>
		/// <returns></returns>
		bool SetInputLayout()override;
		/// <summary>
		/// Función para guardar la
		/// información del sampler state de DX
		/// </summary>
		/// <returns></returns>
		bool SetSamplerState()override;
		

		

		
};