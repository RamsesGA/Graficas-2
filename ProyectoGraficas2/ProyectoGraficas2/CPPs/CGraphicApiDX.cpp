#include "..\Includes\CGraphicApiDX.h"
#include <iostream>
#include <vector>

LRESULT CALLBACK WndProc(HWND hWnd,
                         UINT message,
                         WPARAM wParam,
                         LPARAM lParam) {

    PAINTSTRUCT ps;
    HDC hdc;

    switch (message)
    {
        case WM_PAINT:
            hdc = BeginPaint(hWnd, &ps);
            EndPaint(hWnd, &ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

bool CGraphicApiDX::MainInit(){

    if (!InitWindow()) {

        std::cout << "Error, MainInit, no se inicializo la ventana\n";
        return false;
    }

    if (!InitDevice()) {

        std::cout << "Error, MainInit, no se inicializo el device\n";
        return false;
    }

    return true;
}

bool CGraphicApiDX::InitWindow(){

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = NULL;
    wcex.hIcon = NULL;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"WindowClass";
    wcex.hIconSm = NULL;

    if (!RegisterClassEx(&wcex)) {

        return false;
    }

    // Create window
    RECT rc = { 0, 0, 640, 480 };
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

    m_hInst = NULL;
    m_hWnd = CreateWindow(L"WindowClass", L"Direct3D 11",
                          WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                          CW_USEDEFAULT, (rc.right - rc.left),
                          (rc.bottom - rc.top),
                          NULL, NULL,
                          NULL, NULL);

    if (!m_hWnd) {

        return false;
    }

    ShowWindow(m_hWnd, 100);

    return true;
}

bool CGraphicApiDX::InitDevice() {

    HRESULT hr = S_OK;

    RECT rc;

    GetClientRect(m_hWnd, &rc);

    m_width = rc.right - rc.left;
    m_height = rc.bottom - rc.top;

    UINT createDeviceFlags = 0;
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;

    std::vector<D3D_DRIVER_TYPE> driverTypes =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };

    std::vector<D3D_FEATURE_LEVEL> featureLevels =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = m_width;
    sd.BufferDesc.Height = m_height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = m_hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE;

    for (UINT driverTypeIndex = 0; driverTypeIndex < driverTypes.size(); driverTypeIndex++) {

        hr = D3D11CreateDeviceAndSwapChain(NULL, driverTypes[driverTypeIndex],
                                           NULL, createDeviceFlags, 
                                           featureLevels.data(), featureLevels.size(),
                                           D3D11_SDK_VERSION, &sd, 
                                           &m_pSwapChain, &m_pd3dDevice,
                                           &m_featureLevel, &m_pImmediateContext);

        if (SUCCEEDED(hr)) {

            break;
        }
    }

    if (FAILED(hr)) {

        return false;
    }
    else {

        return true;
    }
}

bool CGraphicApiDX::CreatePixelShader(){

    return false;
}

bool CGraphicApiDX::CreateVertexShader(){

    return false;
}

bool CGraphicApiDX::CreateVertexBuffer(){

    return false;
}

bool CGraphicApiDX::CreateIndexBuffer(){

    return false;
}

bool CGraphicApiDX::CreateConstBuffNeverChanges(){

    return false;
}

bool CGraphicApiDX::CreateConstBuffChangeOnResize(){

    return false;
}

bool CGraphicApiDX::CreateConstBuffChangeEveryFrame(){

    return false;
}

bool CGraphicApiDX::CreateTexture2D(){

    return false;
}

bool CGraphicApiDX::CreateInputLayout(){

    return false;
}

bool CGraphicApiDX::CreateSamplerState(){

    return false;
}

bool CGraphicApiDX::SetPixelShader(){

    return false;
}

bool CGraphicApiDX::SetVertexShader(){

    return false;
}

bool CGraphicApiDX::SetVertexBuffer(){

    return false;
}

bool CGraphicApiDX::SetIndexBuffer(){

    return false;
}

bool CGraphicApiDX::SetConstBuffNeverChanges(){

    return false;
}

bool CGraphicApiDX::SetConstBuffChangeOnResize(){

    return false;
}

bool CGraphicApiDX::SetConstBuffChangeEveryFrame(){

    return false;
}

bool CGraphicApiDX::SetTexture2D(){

    return false;
}

bool CGraphicApiDX::SetInputLayout(){

    return false;
}

bool CGraphicApiDX::SetSamplerState(){

    return false;
}