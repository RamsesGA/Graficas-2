#include "..\Includes\CGraphicApiDX.h"
#include "..\Includes\CConstantBufferDX.h"
#include "..\Includes\CTextureDX.h"
#include "..\Includes\CSamplerStateDX.h"
#include "..\Includes\CInputLayoutDX.h"
#include "..\Includes\CShadersDX.h"
#include "..\Includes\CVertexBufferDX.h"
#include "..\Includes\CIndexBufferDX.h"
#include "..\Includes\stb_image.h"

#include <iostream>
#include <vector>

///
/// Funciones fuera de herencia
/// 

HRESULT CompileShaderFromFile(const std::wstring& szFileName, const std::string& szEntryPoint,
    const std::string& szShaderModel, ID3DBlob** ppBlobOut){
   
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DCompileFromFile(szFileName.c_str(), 
        nullptr, nullptr, 
        szEntryPoint.c_str(), 
        szShaderModel.c_str(),
        dwShaderFlags, 0, ppBlobOut, 
        &pErrorBlob);
    
    if (FAILED(hr)){

        if (pErrorBlob != nullptr)
            OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
        if (pErrorBlob) pErrorBlob->Release();
        return hr;
    }

    if (pErrorBlob) pErrorBlob->Release();

    return S_OK;
}

bool AnalyzeVertexShaderDX(const std::wstring& _nameVS){

    std::string bufferAnalyze;

    for (unsigned int i = 0; i < _nameVS.size(); i++) {

        bufferAnalyze += _nameVS[i];

        if (('_' == bufferAnalyze[i]) &&
            ("DX_" != bufferAnalyze)) {

            return false;
        }
        else if (('_' == bufferAnalyze[i]) &&
                ("DX_" == bufferAnalyze)) {

                return true;
        }
    }

    return false;
}

bool AnalyzePixelShaderDX(const std::wstring& _namePS) {

    std::string bufferAnalyze;

    for (unsigned int i = 0; i < _namePS.size(); i++) {

        bufferAnalyze += _namePS[i];

        if (('_' == bufferAnalyze[i]) &&
            ("DX_" != bufferAnalyze)) {

            return false;
        }
        else if (('_' == bufferAnalyze[i]) &&
                ("DX_" == bufferAnalyze)) {

                return true;
        }
    }

    return false;
}

///
/// D E S T R U C T O R
/// 

CGraphicApiDX::~CGraphicApiDX(){

    ///Liberar mis miembros del API
    /// (SON LOS QUE TENGO DOMINIO PROPIO)
    delete m_pd3dDevice;

    delete m_pSwapChain;
    
    delete m_pImmediateContext;
    
    delete m_pDepthStencil;
    
    delete m_pBackBuffer;
}


///
/// H E R E N C I A
///

bool CGraphicApiDX::InitDevice(HWND _hWnd) {

    HRESULT hr = S_OK;

    RECT rc;

    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

    m_hWnd = _hWnd;

    GetClientRect(m_hWnd, &rc);

    m_width = rc.right - rc.left;
    m_height = rc.bottom - rc.top;

    unsigned int createDeviceFlags = 0;
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

        hr = D3D11CreateDeviceAndSwapChain(nullptr, driverTypes[driverTypeIndex],
                                           nullptr, createDeviceFlags, 
                                           featureLevels.data(), featureLevels.size(),
                                           D3D11_SDK_VERSION, &sd, 
                                           &m_pSwapChain, &m_pd3dDevice,
                                           &featureLevel, &m_pImmediateContext);
        if (SUCCEEDED(hr)) {

            break;
        }
    }

    if (FAILED(hr)) {

        return false;
    }

    auto* backBuffer = new CTextureDX();

    hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
        (LPVOID*)&backBuffer->m_pTexture);

    ///Checamos que todo salga bien, si no mandamos un error
    if (FAILED(hr)) {

        delete backBuffer;
        return false;
    }

    hr = m_pd3dDevice->CreateRenderTargetView(backBuffer->m_pTexture,
        nullptr,
        &backBuffer->m_pRenderTargetView);

    if (FAILED(hr)) {

        delete backBuffer;
        return false;
    }

    m_pBackBuffer = backBuffer;

    auto* depthStencil = new CTextureDX();

    //Textura del depth y hago el depth
    D3D11_TEXTURE2D_DESC textureDesc;
    ZeroMemory(&textureDesc, sizeof(textureDesc));
    textureDesc.Width = m_width;
    textureDesc.Height = m_height;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    textureDesc.CPUAccessFlags = 0;
    textureDesc.MiscFlags = 0;

    ///Creamos la textura
    hr = m_pd3dDevice->CreateTexture2D(&textureDesc, 
        nullptr, &depthStencil->m_pTexture);

    if (FAILED(hr)) {

        delete backBuffer;
        delete depthStencil;
        return false;
    }
    
    D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
    depthStencilDesc.Format = textureDesc.Format;
    depthStencilDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    depthStencilDesc.Texture2D.MipSlice = 0;

    hr = m_pd3dDevice->CreateDepthStencilView(depthStencil->m_pTexture,
        &depthStencilDesc,
        &depthStencil->m_pDepthStencilView);

    ///Checamos que todo salga bien, si no mandamos un error
    if (FAILED(hr)) {

        delete backBuffer;
        delete depthStencil;
        return false;
    }

    m_pImmediateContext->OMSetRenderTargets(1,
        &backBuffer->m_pRenderTargetView,
        depthStencil->m_pDepthStencilView);

    m_pDepthStencil = depthStencil;

    return true;
}

void CGraphicApiDX::DrawIndex(unsigned int _indexCountDX, 
    unsigned int _startIndexLocationDX, 
    unsigned int _baseVertexLocationDX){

    m_pImmediateContext->DrawIndexed(_indexCountDX, _startIndexLocationDX,
        _baseVertexLocationDX);
}

void CGraphicApiDX::SwapChainPresent(unsigned int _syncIntervalDX, 
    unsigned int _flagsDX){

    m_pSwapChain->Present(_syncIntervalDX, _flagsDX);
}

CTexture* CGraphicApiDX::LoadTextureFromFile(std::string _srcFile){

    int width;
    int height;
    int components;

    unsigned char* data = stbi_load(_srcFile.c_str(), 
        &width, &height, &components, 0);

    if (!data){

        return nullptr;
    }

    auto* texture = new CTextureDX();

    D3D11_TEXTURE2D_DESC desc;
    ZeroMemory(&desc, sizeof(desc));
    desc.Width = width;
    desc.Height = height;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.SampleDesc.Count = 1;
    desc.SampleDesc.Quality = 0;
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.MiscFlags = 0;

    if (1 == components){

        desc.Format = DXGI_FORMAT_R16_FLOAT;
    }
    else if (2 == components){

        desc.Format = DXGI_FORMAT_R16G16_FLOAT;
    }
    else if (3 == components){

        desc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
    }
    else if (4 == components){

        desc.Format = DXGI_FORMAT_R16G16B16A16_FLOAT;
    }

    //Texture data
    D3D11_SUBRESOURCE_DATA initData;
    ZeroMemory(&initData, sizeof(initData));
    initData.pSysMem = data;
    initData.SysMemPitch = 1;

    if (FAILED(m_pd3dDevice->CreateTexture2D(&desc,
        &initData,
        &texture->m_pTexture))){

        delete texture;
        stbi_image_free(data);
        return nullptr;
    }

    //Shader resource data
    D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
    ZeroMemory(&viewDesc, sizeof(viewDesc));
    viewDesc.Format = desc.Format;
    viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
    viewDesc.Texture2D.MostDetailedMip = 0;
    viewDesc.Texture2D.MipLevels = 1;

    if (FAILED(m_pd3dDevice->CreateShaderResourceView(texture->m_pTexture,
        &viewDesc,
        &texture->m_pShaderResourceView))){

        delete texture;
        stbi_image_free(data);
        return nullptr;
    }

    return texture;
}

CTexture* CGraphicApiDX::GetDefaultBackBuffer(){

    return m_pBackBuffer;
}

CTexture* CGraphicApiDX::GetDefaultDepthStencil(){

    return m_pDepthStencil;
}

void CGraphicApiDX::UnbindOGL(){}

///
/// U P D A T E�s
/// 

void CGraphicApiDX::UpdateConstantBuffer(const void* _srcData, 
    CConstantBuffer& _updateDataCB){

    auto& constantBuffer = reinterpret_cast<CConstantBufferDX&>(_updateDataCB);

    m_pImmediateContext->UpdateSubresource(constantBuffer.m_pConstantBuffer, 0,
        nullptr, _srcData,
        0, 0);
}

///
/// C L E A R�s
/// 

void CGraphicApiDX::ClearYourRenderTargetView(CTexture* _renderTarget,
    float _r, float _g, float _b, float _a){

    float ClearColor[4] = { _r, _g, _b, _a };

    auto* renderTarget = reinterpret_cast<CTextureDX*>(_renderTarget);

    m_pImmediateContext->ClearRenderTargetView(renderTarget->m_pRenderTargetView,
        ClearColor);
}

void CGraphicApiDX::ClearYourDepthStencilView(CTexture* _depthStencilDX){

    auto* depthStencil = reinterpret_cast<CTextureDX*>(_depthStencilDX);

    m_pImmediateContext->ClearDepthStencilView(depthStencil->m_pDepthStencilView,
        D3D11_CLEAR_DEPTH, 1.0f, 0);
}

///
/// C R E A T E�s 
/// 

CShaders* CGraphicApiDX::CreateShadersProgram(const std::wstring& _nameVS,
    const std::string& _entryPointVS, const std::wstring& _namePS,
    const std::string& _entryPointPS){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    auto* shaders = new CShadersDX();

    if (!(AnalyzeVertexShaderDX(_nameVS))) {

        delete shaders;
        return nullptr;
    }
    if (!(AnalyzePixelShaderDX(_namePS))) {

        delete shaders;
        return nullptr;
    }

    ///Asignamos datos a las variables
    shaders->m_pPSBlob = NULL;
    HRESULT hr = S_OK;

    ///Compilamos el shader recibido
    hr = CompileShaderFromFile(_namePS, _entryPointPS.c_str(), "ps_4_0", &shaders->m_pPSBlob);

    ///Checamos que todo salga bien, si no mandamos un error
    if (FAILED(hr)) {

        delete shaders;
        return nullptr;
    }
    
    ///Creamos el pixel shader con la funci�n de DX
    hr = m_pd3dDevice->CreatePixelShader(shaders->m_pPSBlob->GetBufferPointer(),
        shaders->m_pPSBlob->GetBufferSize(),
        nullptr, &shaders->m_pPixelShader);

    shaders->m_pPSBlob->Release();

    ///Finalmente regresamos el dato en caso
    ///de no obtener un error
    if (FAILED(hr)) {

        delete shaders;
        return nullptr;
    }

    ///Asignamos datos a las variables
    shaders->m_pVSBlob = NULL;

    ///Compilamos el shader recibido
    hr = CompileShaderFromFile(_nameVS, _entryPointVS.c_str(), "vs_4_0", &shaders->m_pVSBlob);

    ///Checamos que todo salga bien, si no mandamos un error
    if (FAILED(hr)) {

        delete shaders;
        return nullptr;
    }
    
    ///Creamos el vertex shader con la funci�n de DX
    hr = m_pd3dDevice->CreateVertexShader(shaders->m_pVSBlob->GetBufferPointer(),
        shaders->m_pVSBlob->GetBufferSize(),
        nullptr, &shaders->m_pVertexShader);

    ///Finalmente regresamos el dato en caso
    ///de no obtener un error
    if (FAILED(hr)) {

        shaders->m_pVSBlob->Release();
        delete shaders;
        return nullptr;
    }

    return shaders;
}

CVertexBuffer* CGraphicApiDX::CreateVertexBuffer(const void* _data,
    const unsigned int _size){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    auto* VB = new CVertexBufferDX();

    ///Asignamos datos a la variable
    HRESULT hr = S_OK;

    if (0 != _size) {

        ///Rellenamos el descriptor de buffer
        CD3D11_BUFFER_DESC bd(_size, D3D11_BIND_VERTEX_BUFFER);

        if (nullptr != _data) {

            ///Generamos una variable descriptor
            D3D11_SUBRESOURCE_DATA InitData;
            ///Limpiamos la memoria y dejamos
            ///definido todo en 0
            ZeroMemory(&InitData, sizeof(InitData));
            ///Asignamos datos a las variables
            InitData.pSysMem = _data;

            ///Creamos el buffer
            hr = m_pd3dDevice->CreateBuffer(&bd, &InitData,
                &VB->m_pVertexBuffer);

            if (FAILED(hr)) {

                delete VB;
                return nullptr;
            }

            return VB;
        }
        else {

            hr = m_pd3dDevice->CreateBuffer(&bd, nullptr, &VB->m_pVertexBuffer);

            if (FAILED(hr)) {

                delete VB;
                return nullptr;
            }

            return VB;
        }
    }

    delete VB;
    return nullptr;
}

CIndexBuffer* CGraphicApiDX::CreateIndexBuffer(const void* _data,
    const unsigned int _size){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    auto* IB = new CIndexBufferDX();

    ///Asignamos datos a la variable
    HRESULT hr = S_OK;

    if (0 != _size) {

        ///Rellenamos el descriptor de buffer
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DEFAULT;
        bd.ByteWidth = _size;
        bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
        bd.CPUAccessFlags = 0;
        bd.MiscFlags = 0;

        if (nullptr != _data) {

            ///Generamos una variable descriptor
            D3D11_SUBRESOURCE_DATA InitData;
            ///Limpiamos la memoria y dejamos
            ///definido todo en 0
            ZeroMemory(&InitData, sizeof(InitData));
            ///Asignamos datos a las variables
            InitData.pSysMem = _data;
            InitData.SysMemPitch = 0;
            InitData.SysMemSlicePitch = 0;

            ///Creamos el buffer
            hr = m_pd3dDevice->CreateBuffer(&bd, &InitData,
                &IB->m_pIndexBuffer);

            if (FAILED(hr)) {

                delete IB;
                return nullptr;
            }

            return IB;
        }
        else {

            hr = m_pd3dDevice->CreateBuffer(&bd, nullptr, &IB->m_pIndexBuffer);

            if (FAILED(hr)) {

                delete IB;
                return nullptr;
            }

            return IB;
        }
    }

    delete IB;
    return nullptr;
}

CConstantBuffer* CGraphicApiDX::CreateConstantBuffer(const unsigned int _bufferSize){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    auto* constantBuffer = new CConstantBufferDX();

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

        delete constantBuffer;
        return nullptr;
    }

    return constantBuffer;
}

CTexture* CGraphicApiDX::CreateTexture(const unsigned int _width,
    const unsigned int _height,
    const unsigned int _bindFlags,
    TEXTURE_FORMAT _textureFormat,
    const std::string _fileName){

    ///Asignamos datos a la variable
    HRESULT hr = S_OK;
    
    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    auto* texture = new CTextureDX();

    ///Rellenamos el descriptor
    D3D11_TEXTURE2D_DESC textureDesc;
    ZeroMemory(&textureDesc, sizeof(textureDesc));
    textureDesc.Width = _width;
    textureDesc.Height = _height;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = (DXGI_FORMAT)_textureFormat;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = _bindFlags;
    textureDesc.CPUAccessFlags = 0;
    textureDesc.MiscFlags = 0;

    ///Creamos la textura
    hr = m_pd3dDevice->CreateTexture2D(&textureDesc, nullptr, &texture->m_pTexture);
    
    if (FAILED(hr)) {

        delete texture;
        return nullptr;
    }

    ///RenderTargetView
    if (_bindFlags & D3D11_BIND_RENDER_TARGET) {

        hr = m_pd3dDevice->CreateRenderTargetView(texture->m_pTexture,
            nullptr,
            &texture->m_pRenderTargetView);

        if (FAILED(hr)) {

            delete texture;
            return nullptr;
        }

        return texture;
    }

    ///DepthStencilView
    if (_bindFlags & D3D11_BIND_DEPTH_STENCIL) {
        
        D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilDesc;
        ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
        depthStencilDesc.Format = textureDesc.Format;
        depthStencilDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
        depthStencilDesc.Texture2D.MipSlice = 0;

        hr = m_pd3dDevice->CreateDepthStencilView(texture->m_pTexture,
            &depthStencilDesc,
            &texture->m_pDepthStencilView);

        ///Checamos que todo salga bien, si no mandamos un error
        if (FAILED(hr)) {

            delete texture;
            return nullptr;
        }
        
        return texture;
    }

    ///ShaderResourceView
    if (_bindFlags & D3D11_BIND_SHADER_RESOURCE) {

        CD3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc(D3D11_SRV_DIMENSION_TEXTURE2D);

        hr = m_pd3dDevice->CreateShaderResourceView(texture->m_pTexture,
            &shaderResourceViewDesc,
            &texture->m_pShaderResourceView);

        ///Checamos que todo salga bien, si no mandamos un error
        if (FAILED(hr)) {

            delete texture;
            return nullptr;
        }

        return texture;
    }
}

CSamplerState* CGraphicApiDX::CreateSamplerState() {

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    auto* samplerState = new CSamplerStateDX();

    ///Asignamos datos a la variable
    HRESULT hr = S_OK;

    ///Definimos el sampler state
    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    hr = m_pd3dDevice->CreateSamplerState(&sampDesc,
                                          &samplerState->m_pSamplerState);

    ///Finalmente regresamos el dato en caso
    ///de no obtener un error
    if (FAILED(hr)) {
        
        delete samplerState;
        return nullptr;
    }

    return samplerState;
}

//Function Creates an input layout from the vertex shader, after compilation.
//Input layout can be reused with any vertex shaders that use the same input layout.
CInputLayout* CGraphicApiDX::CreateInputLayout(CShaders& _vertexShaderDX){

    ///Asignamos datos a la variable
    HRESULT hr = S_OK;

    auto* inputLayout = new CInputLayoutDX();
    auto& vertexShader = reinterpret_cast<CShadersDX&>(_vertexShaderDX);

    ///Generamos la informaci�n del shader
    ID3D11ShaderReflection* pVertexShaderReflection = nullptr;

    if (FAILED(D3DReflect(vertexShader.m_pVSBlob->GetBufferPointer(),
        vertexShader.m_pVSBlob->GetBufferSize(),
        IID_ID3D11ShaderReflection,
        (void**)&pVertexShaderReflection))){

        delete inputLayout;
        pVertexShaderReflection->Release();
        delete pVertexShaderReflection;
        return nullptr;
    }

     ///Generamos una descriptor del shader
     D3D11_SHADER_DESC shaderDesc;

     ///Obtenemos la informaci�n de nuestro
     ///descriptor del shader
     pVertexShaderReflection->GetDesc(&shaderDesc);

     ///Leer la descripci�n del input layout de 
     /// la informaci�n del sombreador
     unsigned int byteOffset = 0;
     std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;

     for (unsigned int i = 0; i < shaderDesc.InputParameters; i++) {

         D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
         pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

         ///Creamos y guardamos la informaci�n
         ///para input element
         D3D11_INPUT_ELEMENT_DESC elementDesc;

         ///Rellenamos 6 datos de 7 el formato es
         ///lo que sigue
         elementDesc.SemanticName = paramDesc.SemanticName;
         elementDesc.SemanticIndex = paramDesc.SemanticIndex;
         elementDesc.InputSlot = 0;
         elementDesc.AlignedByteOffset = byteOffset;
         elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
         elementDesc.InstanceDataStepRate = 0;

         ///Determinamos el formato DXGI
         /// DXGI_FORMAT_R32_UINT
         /// DXGI_FORMAT_R32_SINT
         /// DXGI_FORMAT_R32_FLOAT
         if (paramDesc.Mask == 1) {

                if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) {

                    elementDesc.Format = DXGI_FORMAT_R32_UINT;
                }
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) {

                    elementDesc.Format = DXGI_FORMAT_R32_SINT;
                }
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) {

                    elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
                }
                byteOffset += 4;
            }
         /// DXGI_FORMAT_R32G32_UINT
         /// DXGI_FORMAT_R32G32_SINT
         /// DXGI_FORMAT_R32G32_FLOAT
         else if (paramDesc.Mask <= 3) {

                if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) {

                    elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
                }
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) {

                    elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
                }
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) {

                    elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
                }
                byteOffset += 8;
            }
         /// DXGI_FORMAT_R32G32B32_UINT
         /// DXGI_FORMAT_R32G32B32_SINT
         /// DXGI_FORMAT_R32G32B32_FLOAT
         else if (paramDesc.Mask <= 7) {

                if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) {

                    elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
                }
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) {

                    elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
                }
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) {

                    elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
                }
                byteOffset += 12;
            }
         /// DXGI_FORMAT_R32G32B32A32_UINT
         /// DXGI_FORMAT_R32G32B32A32_SINT
         /// DXGI_FORMAT_R32G32B32A32_FLOAT
         else if (paramDesc.Mask <= 15) {

                if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) {

                    elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
                }
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) {

                    elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
                }
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) {

                    elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
                }
                byteOffset += 16;
            }

         ///Guardamos el element desc
         inputLayoutDesc.push_back(elementDesc);
     }

     ///Creamos el input layout
     hr = m_pd3dDevice->CreateInputLayout(&inputLayoutDesc[0],
         inputLayoutDesc.size(), vertexShader.m_pVSBlob->GetBufferPointer(),
         vertexShader.m_pVSBlob->GetBufferSize(), &inputLayout->m_pVertexLayout);

     ///Liberamos el puntero blob
     vertexShader.m_pVSBlob->Release();

     ///Liberaci�n de memoria de reflexi�n de shader de asignaci�n
     pVertexShaderReflection->Release();

     ///Checamos que todo salga bien, si no mandamos un error
     if (FAILED(hr)) {

         delete inputLayout;
         delete pVertexShaderReflection;
         return nullptr;
     }

     ///Registro de longitud de bytes
     inputLayout->inputLayoutByteLength = &byteOffset;

     return inputLayout;
}

/// 
/// S E T�s
///

void CGraphicApiDX::SetPixelShader(CShaders& _pixelShaderDX) {

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    ///Y hacemos un casteo reinterprete para convertir el puntero
    auto& pixelShader = reinterpret_cast<CShadersDX&> (_pixelShaderDX);

    m_pImmediateContext->PSSetShader(pixelShader.m_pPixelShader, NULL, 0);
}

void CGraphicApiDX::SetVertexShader(CShaders& _vertexShaderDX){

    auto& vertexShader = reinterpret_cast<CShadersDX&>(_vertexShaderDX);

    m_pImmediateContext->VSSetShader(vertexShader.m_pVertexShader, NULL, 0);
}

void CGraphicApiDX::SetVertexBuffer(CVertexBuffer& _vertexBufferDX){

    auto& vertexBuffer = reinterpret_cast<CVertexBufferDX&>(_vertexBufferDX);

    UINT stride = sizeof(Vertex);
    UINT offset = 0;

    m_pImmediateContext->IASetVertexBuffers(0, 
                                            1, 
                                            &vertexBuffer.m_pVertexBuffer,
                                            &stride, 
                                            &offset);
}

void CGraphicApiDX::SetIndexBuffer(CIndexBuffer& _indexBufferDX){

    auto& indexBuffer = reinterpret_cast<CIndexBufferDX&>(_indexBufferDX);

    m_pImmediateContext->IASetIndexBuffer(indexBuffer.m_pIndexBuffer,
                                          DXGI_FORMAT_R32_UINT, 
                                          0);
}

void CGraphicApiDX::SetConstantBuffer(bool _isVertex,
    CConstantBuffer& _constantBuffer,
    const unsigned int _startSlot,
    const unsigned int _numBuffers){

    auto& constantBuffer = reinterpret_cast<CConstantBufferDX&>(_constantBuffer);

    if (true == _isVertex) {

        m_pImmediateContext->VSSetConstantBuffers(_startSlot, _numBuffers,
            &constantBuffer.m_pConstantBuffer);
    }
    else {

        m_pImmediateContext->PSSetConstantBuffers(_startSlot, _numBuffers,
            &constantBuffer.m_pConstantBuffer);
    }
}

void CGraphicApiDX::SetSamplerState(const unsigned int _startSlotDX,
    std::vector<CSamplerState*>& _samplerStateDX,
    CTexture& _texture) {

    for (unsigned int i = 0; i < _samplerStateDX.size(); i++) {

        auto* samplerState = reinterpret_cast<CSamplerStateDX*>(_samplerStateDX[i]);

        m_pImmediateContext->PSSetSamplers(_startSlotDX,
                                           _samplerStateDX.size(),
                                           &samplerState->m_pSamplerState);
    }
}

void CGraphicApiDX::SetShaderResourceView(CTexture* _shaderResourceViewDX,
    const unsigned int _startSlotDX,
    const unsigned int _numViewsDX){

    auto* shaderResource = reinterpret_cast<CTextureDX*>(_shaderResourceViewDX);

    m_pImmediateContext->PSSetShaderResources(_startSlotDX, _numViewsDX,
        &shaderResource->m_pShaderResourceView);
}

void CGraphicApiDX::SetRenderTarget(CTexture* _renderTargetDX,
    CTexture* _depthStencilDX) {

    auto* depthStencil = reinterpret_cast<CTextureDX*>(_depthStencilDX);
    auto* renderTarget = reinterpret_cast<CTextureDX*>(_renderTargetDX);

    m_pImmediateContext->OMSetRenderTargets(1, &renderTarget->m_pRenderTargetView,
        depthStencil->m_pDepthStencilView);
}

void CGraphicApiDX::SetDepthStencil(CTexture& _depthStencilDX,
    const unsigned int _stencilRefDX){

    auto& depthStencil = reinterpret_cast<CTextureDX&>(_depthStencilDX);

    m_pImmediateContext->OMSetDepthStencilState(depthStencil.m_pDepthStencilState, 
        _stencilRefDX);
}

void CGraphicApiDX::SetInputLayout(CInputLayout& _vertexLayoutDX){

    auto& inputLayout = reinterpret_cast<CInputLayoutDX&>(_vertexLayoutDX);

    m_pImmediateContext->IASetInputLayout(inputLayout.m_pVertexLayout);
}

void CGraphicApiDX::SetViewport(const unsigned int _numViewportsDX, 
    const unsigned int _widthDX, const unsigned int _heigthDX){

    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)_widthDX;
    vp.Height = (FLOAT)_heigthDX;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;

    m_pImmediateContext->RSSetViewports(_numViewportsDX, &vp);
}

void CGraphicApiDX::SetPrimitiveTopology(const unsigned int _topologyDX){

    m_pImmediateContext->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)_topologyDX);
}

void CGraphicApiDX::SetYourVS(CShaders& _vertexShaderDX){

    auto& vertexShader = reinterpret_cast<CShadersDX&>(_vertexShaderDX);

    m_pImmediateContext->VSSetShader(vertexShader.m_pVertexShader,
        nullptr, 0);
}

void CGraphicApiDX::SetYourVSConstantBuffers(CConstantBuffer* _constantBufferDX,
    const unsigned int _startSlotDX,
    const unsigned int _numBuffersDX){

    auto* constantBuffer = reinterpret_cast<CConstantBufferDX*>(_constantBufferDX);

    m_pImmediateContext->VSSetConstantBuffers(_startSlotDX, _numBuffersDX,
        &constantBuffer->m_pConstantBuffer);
}

void CGraphicApiDX::SetYourPS(CShaders& _pixelShaderDX){

    auto& pixelShader = reinterpret_cast<CShadersDX&>(_pixelShaderDX);

    m_pImmediateContext->PSSetShader(pixelShader.m_pPixelShader,
        nullptr, 0);
}

void CGraphicApiDX::SetYourPSConstantBuffers(CConstantBuffer* _constantBufferDX,
    const unsigned int _startSlotDX, 
    const unsigned int _numBuffersDX){

    auto* constantBuffer = reinterpret_cast<CConstantBufferDX*>(_constantBufferDX);

    m_pImmediateContext->PSSetConstantBuffers(_startSlotDX, _numBuffersDX,
        &constantBuffer->m_pConstantBuffer);
}

void CGraphicApiDX::SetYourPSSampler(CSamplerState& _samplerDX, 
    const unsigned int _startSlotDX, 
    const unsigned int _numSamplersDX){

    auto& sampler = reinterpret_cast<CSamplerStateDX&>(_samplerDX);

    m_pImmediateContext->PSSetSamplers(_startSlotDX, _numSamplersDX,
        &sampler.m_pSamplerState);
}

void CGraphicApiDX::SetShaders(CShaders& _shaders){

    auto& shaders = reinterpret_cast<CShadersDX&>(_shaders);

    m_pImmediateContext->VSSetShader(shaders.m_pVertexShader, 
        0, 0);
    m_pImmediateContext->PSSetShader(shaders.m_pPixelShader,
        0, 0);
}