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
		/// M�todos
		/// 

		///Constructor
		CGraphicApiDX() = default;
		///Destructor
		~CGraphicApiDX() = default;

		///
		/// Herencia 
		/// 
		
		/// <summary>
		/// Funci�n principal, aqu� mandar� a crear
		/// el init window y el device
		/// </summary>
		/// <returns></returns>
		bool MainInit()override;
		/// <summary>
		/// Funci�n para generar una 
		/// ventana para DX
		/// </summary>
		/// <returns></returns>
		bool InitWindow()override;
		/// <summary>
		/// Funci�n para generar el
		/// device de DX
		/// </summary>
		/// <returns></returns>
		bool InitDevice()override;
		/// <summary>
		/// Funci�n para generar el
		/// pixel shader de DX
		/// </summary>
		/// <returns></returns>
		bool CreatePixelShader()override;
		/// <summary>
		/// Funci�n para generar el
		/// vertex shader de DX
		/// </summary>
		/// <returns></returns>
		bool CreateVertexShader()override;
		/// <summary>
		/// Funci�n para generar el
		/// vertex buffer de DX
		/// </summary>
		/// <returns></returns>
		bool CreateVertexBuffer()override;
		/// <summary>
		/// Funci�n para generar el
		/// Index buffer de DX
		/// </summary>
		/// <returns></returns>
		bool CreateIndexBuffer()override;
		/// <summary>
		/// Funci�n para generar el
		/// buffer never changes de DX
		/// </summary>
		/// <returns></returns>
		bool CreateConstBuffNeverChanges()override;
		/// <summary>
		/// Funci�n para generar el
		/// buffer Change on resize de DX
		/// </summary>
		/// <returns></returns>
		bool CreateConstBuffChangeOnResize()override;
		/// <summary>
		/// Funci�n para generar el
		/// buffer de change every frame de DX
		/// </summary>
		/// <returns></returns>
		bool CreateConstBuffChangeEveryFrame()override;
		/// <summary>
		/// Funci�n para generar la
		/// textura 2D de DX
		/// </summary>
		/// <returns></returns>
		bool CreateTexture2D()override;
		/// <summary>
		/// Funci�n para generar el
		/// Input layout de DX
		/// </summary>
		/// <returns></returns>
		bool CreateInputLayout()override;
		/// <summary>
		/// Funci�n para generar el
		/// sampler state de DX
		/// </summary>
		/// <returns></returns>
		bool CreateSamplerState()override;

		/// <summary>
		/// Funci�n para guardar la
		/// informaci�n del pixel shader de DX
		/// </summary>
		/// <returns></returns>
		bool SetPixelShader()override;
		/// <summary>
		/// Funci�n para guardar la
		/// informaci�n del vertex shader de DX
		/// </summary>
		/// <returns></returns>
		bool SetVertexShader()override;
		/// <summary>
		/// Funci�n para guardar la
		/// informaci�n del vertex buffer de DX
		/// </summary>
		/// <returns></returns>
		bool SetVertexBuffer()override;
		/// <summary>
		/// Funci�n para guardar la
		/// informaci�n del index buffer de DX
		/// </summary>
		/// <returns></returns>
		bool SetIndexBuffer()override;
		/// <summary>
		/// Funci�n para guardar la
		/// informaci�n del buffer never changes de DX
		/// </summary>
		/// <returns></returns>
		bool SetConstBuffNeverChanges()override;
		/// <summary>
		/// Funci�n para guardar la
		/// informaci�n del buffer change on resize de DX
		/// </summary>
		/// <returns></returns>
		bool SetConstBuffChangeOnResize()override;
		/// <summary>
		/// Funci�n para guardar la
		/// informaci�n del buffer change every frame de DX
		/// </summary>
		/// <returns></returns>
		bool SetConstBuffChangeEveryFrame()override;
		/// <summary>
		/// Funci�n para guardar la
		/// informaci�n de la textura 2D de DX
		/// </summary>
		/// <returns></returns>
		bool SetTexture2D()override;
		/// <summary>
		/// Funci�n para guardar la
		/// informaci�n del input layout de DX
		/// </summary>
		/// <returns></returns>
		bool SetInputLayout()override;
		/// <summary>
		/// Funci�n para guardar la
		/// informaci�n del sampler state de DX
		/// </summary>
		/// <returns></returns>
		bool SetSamplerState()override;
		

		

		
};