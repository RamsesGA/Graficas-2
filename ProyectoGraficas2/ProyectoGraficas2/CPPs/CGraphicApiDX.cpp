#include "..\Includes\CGraphicApiDX.h"
#include "..\Includes\CPixelShaderDX.h"
#include "..\Includes\CVertexShaderDX.h"
#include "..\Includes\CVertexBufferDX.h"
#include "..\Includes\CIndexBufferDX.h"
#include "..\Includes\CConstantBufferDX.h"
#include "..\Includes\CTextureDX.h"
#include "..\Includes\CSamplerStateDX.h"

#include <iostream>
#include <vector>

///
/// Funciones fuera de herencia
/// 

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

/// 
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
CPixelShader* CGraphicApiDX::CreatePixelShader(std::wstring _namePS,
                                               std::string _entryPoint){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    auto pixelShader = new CPixelShaderDX();

    ///Asignamos datos a las variables
    pixelShader->m_pPSBlob = NULL;
    HRESULT hr = S_OK;
    const WCHAR* namePS = _namePS.c_str();

    ///Compilamos el shader recibido
    hr = CompileShaderFromFile(namePS, _entryPoint.c_str(), "ps_4_0", &pixelShader->m_pPSBlob);

    ///Checamos que todo salga bien, si no mandamos un error
    if (FAILED(hr)){

        MessageBox(
            NULL,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", 
            L"Error", 
            MB_OK);
        return nullptr;
    }

    ///Creamos el pixel shader con la función de DX
    hr = m_pd3dDevice->CreatePixelShader(pixelShader->m_pPSBlob->GetBufferPointer(), 
                                         pixelShader->m_pPSBlob->GetBufferSize(),
                                         NULL, &pixelShader->m_pPixelShader);

    pixelShader->m_pPSBlob->Release();

    ///Finalmente regresamos el dato en caso
    ///de no obtener un error
    if (FAILED(hr)) {

        MessageBox(
            NULL,
            L"hr nulo",
            L"Error",
            MB_OK);
        return nullptr;
    }
    else {

        return pixelShader;
    }
}

/// 
CVertexShader* CGraphicApiDX::CreateVertexShader(std::wstring _nameVS, 
                                                 std::string _entryPoint){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    auto vertexShader = new CVertexShaderDX();

    ///Asignamos datos a las variables
    vertexShader->m_pVSBlob = NULL;
    HRESULT hr = S_OK;
    const WCHAR* nameVS = _nameVS.c_str();

    ///Compilamos el shader recibido
    hr = CompileShaderFromFile(nameVS, _entryPoint.c_str(), "vs_4_0", &vertexShader->m_pVSBlob);

    ///Checamos que todo salga bien, si no mandamos un error
    if (FAILED(hr)){

        MessageBox(   
            NULL,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", 
            L"Error", 
            MB_OK);
        return nullptr;
    }

    ///Creamos el vertex shader con la función de DX
    hr = m_pd3dDevice->CreateVertexShader(vertexShader->m_pVSBlob->GetBufferPointer(), 
                                          vertexShader->m_pVSBlob->GetBufferSize(),
                                          NULL, &vertexShader->m_pVertexShader);

    vertexShader->m_pVSBlob->Release();

    ///Finalmente regresamos el dato en caso
    ///de no obtener un error
    if (FAILED(hr)){

        MessageBox(
            NULL,
            L"hr nulo",
            L"Error",
            MB_OK);
        return nullptr;
    }
    else {

        return vertexShader;
    }
}

///
CVertexBuffer* CGraphicApiDX::CreateVertexBuffer(unsigned int _bufferSize,
                                                 std::vector <SimpleVertex> _simpleVertex){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    auto vertexBuffer = new CVertexBufferDX();

    ///Asignamos datos a la variable
    HRESULT hr = S_OK;
    
    ///Rellenamos el descriptor de buffer
    CD3D11_BUFFER_DESC bd(sizeof(unsigned int) * _bufferSize,
                          D3D11_BIND_VERTEX_BUFFER);

    ///Generamos una variable descriptor
    D3D11_SUBRESOURCE_DATA InitData;

    ///Limpiamos la memoria y dejamos
    ///definido todo en 0
    ZeroMemory(&InitData, sizeof(InitData));

    ///Asignamos datos a las variables
    InitData.pSysMem = _simpleVertex.data();

    ///Creamos el buffer
    hr = m_pd3dDevice->CreateBuffer(&bd, &InitData, 
                                    &vertexBuffer->m_pVertexBuffer);

    ///Finalmente regresamos el dato en caso
    ///de no obtener un error
    if (FAILED(hr)) {

        MessageBox(
            NULL,
            L"hr nulo",
            L"Error",
            MB_OK);
        return nullptr;
    }
    else {

        return vertexBuffer;
    }
}

///
CIndexBuffer* CGraphicApiDX::CreateIndexBuffer(unsigned int _bufferSize,
                                               std::vector <unsigned int> _simpleIndex){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    auto indexBuffer = new CIndexBufferDX();

    ///Asignamos datos a la variable
    HRESULT hr = S_OK;

    ///Rellenamos el descriptor de buffer
    CD3D11_BUFFER_DESC bd(sizeof(unsigned int) * _bufferSize,
                          D3D11_BIND_INDEX_BUFFER);

    ///Generamos una variable descriptor
    D3D11_SUBRESOURCE_DATA InitData;

    ///Limpiamos la memoria y dejamos
    ///definido todo en 0
    ZeroMemory(&InitData, sizeof(InitData));

    ///Asignamos datos a las variables
    InitData.pSysMem = _simpleIndex.data();

    ///Creamos el buffer
    hr = m_pd3dDevice->CreateBuffer(&bd, &InitData, 
                                    &indexBuffer->m_pIndexBuffer);

    ///Finalmente regresamos el dato en caso
    ///de no obtener un error
    if (FAILED(hr)) {

        MessageBox(
            NULL,
            L"hr nulo",
            L"Error",
            MB_OK);
        return nullptr;
    }
    else {

        return indexBuffer;
    }
}

///
CConstantBuffer* CGraphicApiDX::CreateConstantBuffer(unsigned int _bufferSize){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    auto constantBuffer = new CConstantBufferDX();

    ///Asignamos datos a la variable
    HRESULT hr = S_OK;

    ///Rellenamos el descriptor de buffer
    CD3D11_BUFFER_DESC bd(_bufferSize, D3D11_BIND_CONSTANT_BUFFER);

    ///Creamos el buffer
    hr = m_pd3dDevice->CreateBuffer(&bd, nullptr,
                                    &constantBuffer->m_pConstantBuffer);

    ///Finalmente regresamos el dato en caso
    ///de no obtener un error
    if (FAILED(hr)) {

        MessageBox(
            NULL,
            L"hr nulo",
            L"Error",
            MB_OK);
        return nullptr;
    }
    else {

        return constantBuffer;
    }
}

///
CTexture* CGraphicApiDX::CreateTexture(unsigned int _width,
                                       unsigned int _height,
                                       unsigned int _bindFlags,
                                       TEXTURE_FORMAT _textureFormat){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    auto texture = new CTextureDX();

    ///Asignamos datos a la variable
    HRESULT hr = S_OK;

    ///Rellenamos el descriptor de buffer
    CD3D11_TEXTURE2D_DESC textureDesc((DXGI_FORMAT)_textureFormat, _width,
                                      _height, _bindFlags);

    ///Creamos la textura
    hr = m_pd3dDevice->CreateTexture2D(&textureDesc, nullptr, &texture->m_pTexture);

    ///Checamos que todo salga bien, si no mandamos un error
    if (FAILED(hr)) {

        MessageBox(
            NULL,
            L"hr nulo",
            L"Error",
            MB_OK);
        return nullptr;
    }

    ///Finalmente checamos el tipo de
    ///bind flag que escogió el usuario
    ///y lo creamos
    switch (_bindFlags) {

        case D3D11_BIND_SHADER_RESOURCE:
        {
            CD3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc(D3D11_SRV_DIMENSION_TEXTURE2D);
            hr = m_pd3dDevice->CreateShaderResourceView(texture->m_pTexture,
                                                        &shaderResourceViewDesc,
                                                        &texture->m_pShaderResourceView);
            break;
        }
        case D3D11_BIND_DEPTH_STENCIL:
        {
            CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
            hr = m_pd3dDevice->CreateDepthStencilView(texture->m_pTexture,
                                                      &depthStencilDesc,
                                                      &texture->m_pDepthStencilView);
            break;
        }
        case D3D11_BIND_RENDER_TARGET:
        {
            CD3D11_RENDER_TARGET_VIEW_DESC renderTargetDesc(D3D11_RTV_DIMENSION_TEXTURE2D);
            hr = m_pd3dDevice->CreateRenderTargetView(texture->m_pTexture, 
                                                      &renderTargetDesc,
                                                      &texture->m_pRenderTargetView);
            break;
        }
    }
}

///
CSamplerState* CGraphicApiDX::CreateSamplerState() {

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    auto samplerState = new CSamplerStateDX();

    ///Asignamos datos a la variable
    HRESULT hr = S_OK;

    ///Obtenemos los datos creados
    ///del sampler state
    CD3D11_SAMPLER_DESC samplerDesc;

    hr = m_pd3dDevice->CreateSamplerState(&samplerDesc, 
                                          &samplerState->m_pSamplerState);

    ///Finalmente regresamos el dato en caso
    ///de no obtener un error
    if (FAILED(hr)) {

        MessageBox(
            NULL,
            L"hr nulo",
            L"Error",
            MB_OK);
        return nullptr;
    }
    else {

        return samplerState;
    }
}

bool CGraphicApiDX::CreateInputLayout(){

    return false;
}

///
/// Funciones de herencia
/// 

/// 
/// S E T´s
///

/// 
void CGraphicApiDX::SetPixelShader(CPixelShader* _pixelShader){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    ///Y hacemos un casteo reinterprete para convertir el puntero
    auto pixelShader = reinterpret_cast<CPixelShaderDX*>(_pixelShader);

    m_pImmediateContext->PSSetShader(pixelShader->m_pPixelShader, NULL, 0);
}

/// 
void CGraphicApiDX::SetVertexShader(CVertexShader* _vertexShader){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    ///Y hacemos un casteo reinterprete para convertir el puntero
    auto vertexShader = reinterpret_cast<CVertexShaderDX*>(_vertexShader);

    m_pImmediateContext->VSSetShader(vertexShader->m_pVertexShader, NULL, 0);
}

/// 
void CGraphicApiDX::SetVertexBuffer(CVertexBuffer* _vertexBuffer){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    ///Y hacemos un casteo reinterprete para convertir el puntero
    auto vertexBuffer = reinterpret_cast<CVertexBufferDX*>(_vertexBuffer);

    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;
    m_pImmediateContext->IASetVertexBuffers(0, 
                                            1, 
                                            &vertexBuffer->m_pVertexBuffer,
                                            &stride, 
                                            &offset);
}

/// 
void CGraphicApiDX::SetIndexBuffer(CIndexBuffer* _indexBuffer){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    ///Y hacemos un casteo reinterprete para convertir el puntero
    auto indexBuffer = reinterpret_cast<CIndexBufferDX*>(_indexBuffer);

    m_pImmediateContext->IASetIndexBuffer(indexBuffer->m_pIndexBuffer,
                                          DXGI_FORMAT_R16_UINT, 
                                          0);
}

void CGraphicApiDX::SetConstantBuffer(CConstantBuffer* _constantBuffer,
                                      unsigned int _startSlot,
                                      unsigned int _numBuffers){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    ///Y hacemos un casteo reinterprete para convertir el puntero
    auto constantBuffer = reinterpret_cast<CConstantBufferDX*>(_constantBuffer);

    m_pImmediateContext->VSSetConstantBuffers(_startSlot, _numBuffers,
                                              &constantBuffer->m_pConstantBuffer);
}

void CGraphicApiDX::SetTexture(CTexture* _texture){

    ///TODO: Cambiar los set
}

void CGraphicApiDX::SetSamplerState(unsigned int _startSlot,
                                    std::vector<CSamplerState*>& _samplerState) {

    for (unsigned int i = 0; i < _samplerState.size(); i++) {

        ///Generamos una variable auto
        ///para adaptar el tipo de dato que ocupamos
        ///Y hacemos un casteo reinterprete para convertir el puntero
        auto samplerState = reinterpret_cast<CSamplerStateDX*>(_samplerState[i]);

        m_pImmediateContext->PSSetSamplers(_startSlot, 
                                           _samplerState.size(), 
                                           &samplerState->m_pSamplerState);
    }
}

void CGraphicApiDX::SetInputLayout(){

}