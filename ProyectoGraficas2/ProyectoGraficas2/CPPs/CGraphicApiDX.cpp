#include "../Includes/CGraphicApiDX.h"
#include "../Includes/CBufferDX.h"
#include "../Includes/CTexturesDX.h"
#include "../Includes/CVertexBufferDX.h"
#include "../Includes/CPixelShaderDX.h"
#include "../Includes/CInputLayoutDX.h"
#include "../Includes/CSampleStateDX.h"


void CGraphicApiDX::Init(){

    m_pDevice = NULL;
    m_pDeviceContext = NULL;
}

HRESULT CGraphicApiDX::CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, 
                                             LPCSTR szShaderModel, ID3DBlob** ppBlobOut){
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
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

int CGraphicApiDX::GACreateBuffer(unsigned int _bufferOGL,
                                  unsigned int _byteWidth, unsigned int _usage,
                                  unsigned int _bindFlags, unsigned int _CPUAccessFlags,
                                  unsigned int _miscFlags, unsigned int _structureByteStride,
                                  const void* _pSysMem, CBuffer* _pBuffer){
    HRESULT hr = S_OK;

    CBufferDX* newBuffer;
    newBuffer->Init(_bufferOGL,
                    _byteWidth, _usage,
                    _bindFlags, _CPUAccessFlags,
                    _miscFlags, _structureByteStride,
                    _pSysMem);

    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = newBuffer->m_usage;
    bd.ByteWidth = newBuffer->m_byteWidth;
    bd.BindFlags = newBuffer->m_bindFlags;
    bd.CPUAccessFlags = newBuffer->m_cpuAccessFlags;

    D3D11_SUBRESOURCE_DATA InitData;
    ZeroMemory(&InitData, sizeof(InitData));
    InitData.pSysMem = newBuffer->m_pSysMem;

    hr = m_pDevice->CreateBuffer(&bd, &InitData, &newBuffer->m_pVertexBuffer);
    if (FAILED(hr)) {
        return hr;
    }
    return 0;
}

int CGraphicApiDX::GACreateTexture2D(unsigned int _texture,
                                     unsigned int _width, unsigned int _height,
                                     unsigned int _mipLevels, unsigned int _arraySize,
                                     unsigned int _format, unsigned int _sampleDescCount,
                                     unsigned int _sampleDescQuality, unsigned int _usage,
                                     unsigned int _bindFlags, unsigned int _cpuAccessFlags,
                                     unsigned int _miscFlags, const void* _pSysMem,
                                     CTextures* _pTexture){
    HRESULT hr = S_OK;

    CTexturesDX* newTexture2D;
    newTexture2D->Init(_texture,
                       _width,
                       _height, _mipLevels, 
                       _arraySize, _format, 
                       _sampleDescCount, _sampleDescQuality, 
                       _usage, _bindFlags, 
                       _cpuAccessFlags, _miscFlags, 
                       _pSysMem);

    D3D11_TEXTURE2D_DESC descDepth;
    ZeroMemory(&descDepth, sizeof(descDepth));
    descDepth.Width = newTexture2D->m_width;
    descDepth.Height = newTexture2D->m_height;
    descDepth.MipLevels = newTexture2D->m_mipLevels;
    descDepth.ArraySize = newTexture2D->m_arraySize;
    descDepth.Format = newTexture2D->m_format;
    descDepth.SampleDesc.Count = newTexture2D->m_sampleDescCount;
    descDepth.SampleDesc.Quality = newTexture2D->m_sampleDescQuality;
    descDepth.Usage = newTexture2D->m_usage;
    descDepth.BindFlags = newTexture2D->m_bindFlags;
    descDepth.CPUAccessFlags = newTexture2D->m_cpuAccessFlags;
    descDepth.MiscFlags = newTexture2D->m_miscFlags;
    hr = m_pDevice->CreateTexture2D(&descDepth, NULL, &m_pDepthStencil);
    if (FAILED(hr)) {
        return hr;
    }
    m_descDepth = descDepth;

    return 0;
}

int CGraphicApiDX::GACreateVertexShader(unsigned int _shaderType) {

    HRESULT hr = S_OK;

    m_pVSBlob = NULL;
    hr = CompileShaderFromFile(L"Tutorial07.fx", "VS", "vs_4_0", &m_pVSBlob);
    if (FAILED(hr)){
        MessageBox(NULL,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    CVertexBufferDX vertexBuff;

    // Create the vertex shader
    hr = m_pDevice->CreateVertexShader(m_pVSBlob->GetBufferPointer(), m_pVSBlob->GetBufferSize(), NULL, &vertexBuff.m_pVertexShader);
    m_pVSBlob->Release();
    if (FAILED(hr)){
        
        return hr;
    }
    return 0;
}

int CGraphicApiDX::GACreatePixelShader(unsigned int _shaderType){

    HRESULT hr = S_OK;

    m_pPSBlob = NULL;
    hr = CompileShaderFromFile(L"Tutorial07.fx", "PS", "ps_4_0", &m_pPSBlob);
    if (FAILED(hr)){
        MessageBox(NULL,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    CPixelShaderDX newPixel;

    // Create the pixel shader
    hr = m_pDevice->CreatePixelShader(m_pPSBlob->GetBufferPointer(), m_pPSBlob->GetBufferSize(), NULL, &newPixel.m_pPixelShader);
    m_pPSBlob->Release();
    if (FAILED(hr)) {
        return hr;
    }
    return 0;
}

int CGraphicApiDX::GACreateInputLayout(char* _semanticName, unsigned int _semanticIndex,
                                       unsigned int _format, unsigned int _inputSlot,
                                       unsigned int _alignedByteOffset, unsigned int _inputSlotClass,
                                       unsigned int _instanceDataStepRate, unsigned int _numElements,
                                       CInputLayout** _ppInputLayout) {
    HRESULT hr = S_OK;

    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    UINT numElements = ARRAYSIZE(layout);

    CInputLayoutDX newInput;

    // Create the input layout
    hr = m_pDevice->CreateInputLayout(layout, numElements, m_pVSBlob->GetBufferPointer(),
                                      m_pVSBlob->GetBufferSize(), &newInput.m_pVertexLayout);
    m_pVSBlob->Release();
    if (FAILED(hr)) {
        return hr;
    }
    return 0;
}

int CGraphicApiDX::GACreateSamplerState(unsigned int* _sampler,
                                        unsigned int _filter, unsigned int _addresU,
                                        unsigned int _addressV, unsigned int _addressW,
                                        unsigned int _camparisionFunc, float _minLOD,
                                        float _maxLOD, CSampleState** _ppSamplerState) {
    HRESULT hr = S_OK;

    CSampleStateDX newSampler;

    newSampler.Init(_sampler,
                    _filter, _addresU,
                    _addressV, _addressW,
                    _camparisionFunc, _minLOD,
                    _maxLOD);

    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = newSampler.m_filter;
    sampDesc.AddressU = newSampler.m_addressU;
    sampDesc.AddressV = newSampler.m_addressV;
    sampDesc.AddressW = newSampler.m_addressW;
    sampDesc.ComparisonFunc = newSampler.m_comparissionFunc;
    sampDesc.MinLOD = newSampler.m_minLOD;
    sampDesc.MaxLOD = newSampler.m_maxLOD;

    hr = m_pDevice->CreateSamplerState(&sampDesc, &newSampler.m_pSamplerLinear);
    if (FAILED(hr)) {
        return hr;
    }
    return 0;
}

int CGraphicApiDX::GACreateDepthStencilView(unsigned int _mipSliceTex2D, 
                                            unsigned int _viewDimension,
                                            unsigned int _format) {
    HRESULT hr = S_OK;

    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    ZeroMemory(&descDSV, sizeof(descDSV));
    descDSV.Format = m_descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;
    hr = m_pDevice->CreateDepthStencilView(m_pDepthStencil, &descDSV, &m_pDepthStencilView);
    if (FAILED(hr)) {
        return hr;
    }
    return 0;
}

int CGraphicApiDX::GACreateRenderTargetView() {

    HRESULT hr = S_OK;

    hr = m_pDevice->CreateRenderTargetView(m_pBackBuffer, NULL, &m_pRenderTargetView);

    m_pBackBuffer->Release();
    if (FAILED(hr)) {
        return hr;
    }
    return 0;
}

int CGraphicApiDX::GACreateShaderResourceViewFromFile(const char _pSrcFile,
                                                      std::string _shaderNameOGL, 
                                                      unsigned int _idOGL) {
    HRESULT hr = S_OK;

    hr = D3DX11CreateShaderResourceViewFromFile(m_pDevice, L"seafloor.dds", NULL, NULL, &m_pTextureRV, NULL);
    if (FAILED(hr)) {
        return hr;
    }

    return 0;
}

int CGraphicApiDX::GACreateDeviceAndSwapChain(unsigned int _driverType, unsigned int _flags,
                                              unsigned int* _pFeatureLevels, unsigned int _featureLevels,
                                              unsigned int _sdkVersion, unsigned int _bufferCount,
                                              unsigned int _width, unsigned int _height,
                                              unsigned int _format, unsigned int _numerator,
                                              unsigned int _denominator, unsigned int _bufferUsage,
                                              int* _hwnd, unsigned int _count,
                                              unsigned int _quality, bool _windowed,
                                              CSwapChain** _ppSwapChain, unsigned int* _pFeatureLevel) {

    HRESULT hr = S_OK;

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = _width;
    sd.BufferDesc.Height = _height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = _numerator;
    sd.BufferDesc.RefreshRate.Denominator = _denominator;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = m_hWnd;
    sd.SampleDesc.Count = _count;
    sd.SampleDesc.Quality = _quality;
    sd.Windowed = _windowed;

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        m_driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDeviceAndSwapChain(NULL, m_driverType, 
                                           NULL, createDeviceFlags, 
                                           featureLevels, numFeatureLevels,
                                           D3D11_SDK_VERSION, &sd, 
                                           &m_pSwapChain, &m_pDevice,
                                           &m_featureLevel, &m_pImmediateContext);
        if (SUCCEEDED(hr)) {
            break;
        }
    }
    if (FAILED(hr)) {
        return hr;
    }
    return 0;
}



///
/// S E T
/// 

int CGraphicApiDX::GAIASetInputLayout(){

    m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
    return 0;
}