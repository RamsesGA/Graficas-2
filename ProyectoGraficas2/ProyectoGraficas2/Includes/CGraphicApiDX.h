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
		/// Mi abstracci�n 
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
		/// M�todos
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
		bool CreatePixelShader(std::wstring _namePS)override;
		/// <summary>
		/// Funci�n para generar el
		/// vertex shader de DX
		/// </summary>
		/// <returns></returns>
		bool CreateVertexShader(std::wstring _nameVS)override;
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

		///
		/// S E T�s 
		/// 

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