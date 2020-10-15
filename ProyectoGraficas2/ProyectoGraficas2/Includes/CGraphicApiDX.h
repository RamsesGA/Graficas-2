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

		UINT m_width;
		UINT m_height;

		HINSTANCE m_hInst;
		HWND m_hWnd;

		ID3D11DeviceContext* m_pImmediateContext;
		ID3D11SamplerState* m_pSamplerLinear;
		ID3D11ShaderResourceView* m_pTextureRV;
		ID3D11Buffer* m_pCBNeverChanges;
		ID3D11Buffer* m_pCBChangeOnResize;
		ID3D11Buffer* m_pCBChangesEveryFrame;
		ID3D11Buffer* m_pVertexBuffer;
		ID3D11Buffer* m_pIndexBuffer;
		ID3D11InputLayout* m_pVertexLayout;
		ID3D11VertexShader* m_pVertexShader;
		ID3D11PixelShader* m_pPixelShader;
		ID3D11Texture2D* m_pDepthStencil;
		ID3D11DepthStencilView* m_pDepthStencilView;
		ID3D11RenderTargetView* m_pRenderTargetView;
		IDXGISwapChain* m_pSwapChain;
		ID3D11Device* m_pd3dDevice;

		D3D_DRIVER_TYPE                     g_driverType
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
		/// Función para inicializar los miembros
		/// de la clase predeterminada
		/// </summary>
		void Init();
		/// <summary>
		/// Función para actualizar los datos
		/// necesarios y poder mostrarlos
		/// </summary>
		void Update() {};
		/// <summary>
		/// Función para terminar con los procesos
		/// </summary>
		void Exit() {};
		/// <summary>
		/// Con esta función generaremos todo
		/// lo necesario para la creación de una venta
		/// </summary>
		/// <returns></returns>
		bool InitWindow();

		///
		/// Propios de DX
		/// 
		
		/// <summary>
		/// Limpia los objetos que hemos creado
		/// </summary>
		void CleanupDevice();
		/// <summary>
		/// Crear dispositivo Direct3D 
		/// y cadena de intercambio
		/// </summary>
		/// <returns></returns>
		HRESULT InitDevice();
		/// <summary>
		/// Registrar clase y crear ventana
		/// </summary>
		/// <param name="_hInstance"></param>
		/// <param name="_cmdShow"></param>
		/// <returns></returns>
		HRESULT WindowDX(HINSTANCE _hInstance, 
						 int _cmdShow);
};