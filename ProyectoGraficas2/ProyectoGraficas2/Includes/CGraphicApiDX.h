#pragma once
#include "CGraphicApi.h"
#include "CPixelShaderDX.h"
#include "CVertexShaderDX.h"
#include "CBufferDX.h"


#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>

class CGraphicApiDX : public CGraphicApi{

	public:
		///
		/// Miembros
		/// 

		///
		/// Mi abstracción 
		/// 
		
		CPixelShaderDX m_ps;
		CVertexShaderDX m_vs;
		CBufferDX m_IB;
		CBufferDX m_VB;
		CBufferDX m_cbNeverChangesBuffer;
		CBufferDX m_cbChangeOnResizeBuffer;
		CBufferDX m_cbChangesEveryFrameBuffer;


		///
		/// Propios de DX
		/// 
		 
		UINT m_width;
		UINT m_height;

		HWND m_hWnd;
		HINSTANCE m_hInst;

		ID3DBlob* m_pPSBlob;
		ID3DBlob* m_pVSBlob;
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
		bool CreatePixelShader(std::wstring _namePS)override;
		/// <summary>
		/// Función para generar el
		/// vertex shader de DX
		/// </summary>
		/// <returns></returns>
		bool CreateVertexShader(std::wstring _nameVS)override;
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

		///
		/// S E T´s 
		/// 

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