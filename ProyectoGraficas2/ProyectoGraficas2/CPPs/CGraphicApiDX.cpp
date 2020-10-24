#include "..\Includes\CGraphicApiDX.h"
#include <iostream>
#include <vector>

///
/// Funciones fuera de herencia
/// 

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

HRESULT CGraphicApiDX::CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint,
                                             LPCSTR szShaderModel, ID3DBlob** ppBlobOut){
   
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
        dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);
    if (FAILED(hr))
    {
        if (pErrorBlob != NULL)
            OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
        if (pErrorBlob) pErrorBlob->Release();
        return hr;
    }
    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}

///
/// Funciones de herencia
/// 
/// C R E A T E S
/// 

/// 
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

/// 
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

/// 
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

/// 
bool CGraphicApiDX::CreatePixelShader(std::wstring _namePS){

    m_pPSBlob = NULL;
    HRESULT hr = S_OK;
    const WCHAR* namePS = _namePS.c_str();

    hr = CompileShaderFromFile(namePS, "PS", "ps_4_0", &m_pPSBlob);

    if (FAILED(hr)){

        MessageBox(NULL,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", 
            L"Error", 
            MB_OK);
        return false;
    }

    hr = m_pd3dDevice->CreatePixelShader(m_pPSBlob->GetBufferPointer(), m_pPSBlob->GetBufferSize(),
                                         NULL, &m_ps.m_pPixelShader);
    m_pPSBlob->Release();

    if (FAILED(hr)) {

        return false;
    }
    else {

        return true;
    }
}

/// 
bool CGraphicApiDX::CreateVertexShader(std::wstring _nameVS){

    m_pVSBlob = NULL;
    HRESULT hr = S_OK;
    const WCHAR* nameVS = _nameVS.c_str();

    // Compile the vertex shader
    hr = CompileShaderFromFile(nameVS, "VS", "vs_4_0", &m_pVSBlob);
    if (FAILED(hr)){

        MessageBox
        (   NULL,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", 
            L"Error", 
            MB_OK);
        return false;
    }

    // Create the vertex shader
    hr = m_pd3dDevice->CreateVertexShader(m_pVSBlob->GetBufferPointer(), m_pVSBlob->GetBufferSize(), 
                                          NULL, &m_vs.m_pVertexShader);
    if (FAILED(hr)){

        m_pVSBlob->Release();
        return false;
    }
    else {

        return true;
    }
}

/// /// 
bool CGraphicApiDX::CreateVertexBuffer(){

    HRESULT hr = S_OK;

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(SimpleVertex) * 24;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    ///TODO: Pasar a vector
    InitData.pSysMem;

    hr = m_pd3dDevice->CreateBuffer(&bd, &InitData, 
                                    &m_VB.m_pVertexBuffer);

    if (FAILED(hr)) {

        return false;
    }
    else {

        return true;
    }
}

/// /// 
bool CGraphicApiDX::CreateIndexBuffer(){

    HRESULT hr = S_OK;

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(WORD) * 36;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    ///TODO: Pasar a vector
    InitData.pSysMem;

    hr = m_pd3dDevice->CreateBuffer(&bd, &InitData, 
                                    &m_IB.m_pIndexBuffer);

    if (FAILED(hr)) {

        return false;
    }
    else {

        return true;
    }
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

///
/// Funciones de herencia
/// 
/// S E T´s
///

/// 
bool CGraphicApiDX::SetPixelShader(){

    m_pImmediateContext->PSSetShader(m_ps.m_pPixelShader, NULL, 0);
}

/// 
bool CGraphicApiDX::SetVertexShader(){

    m_pImmediateContext->VSSetShader(m_vs.m_pVertexShader, NULL, 0);
}

/// 
bool CGraphicApiDX::SetVertexBuffer(){

    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;
    m_pImmediateContext->IASetVertexBuffers(0, 
                                            1, &m_VB.m_pVertexBuffer, 
                                            &stride, &offset);
}

/// 
bool CGraphicApiDX::SetIndexBuffer(){

    m_pImmediateContext->IASetIndexBuffer(m_IB.m_pIndexBuffer, DXGI_FORMAT_R16_UINT, 
                                          0);
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