#include "..\Includes\CGraphicApiDX.h"
#include "..\Includes\CPixelShaderDX.h"
#include "..\Includes\CVertexShaderDX.h"
#include "..\Includes\CVertexBufferDX.h"
#include "..\Includes\CIndexBufferDX.h"
#include "..\Includes\CConstantBufferDX.h"
#include "..\Includes\CTextureDX.h"
#include "..\Includes\CSamplerStateDX.h"
#include "..\Includes\CInputLayoutDX.h"

#include <iostream>
#include <vector>

///
/// Funciones fuera de herencia
/// 

///
HRESULT CompileShaderFromFile(const std::wstring& szFileName, const std::string& szEntryPoint,
    const std::string& szShaderModel, ID3DBlob** ppBlobOut){
   
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DCompileFromFile(szFileName.c_str(), nullptr, nullptr, szEntryPoint.c_str(), szShaderModel.c_str(),
        dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
    
    if (FAILED(hr)){

        if (pErrorBlob != nullptr)
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

/// 
bool CGraphicApiDX::InitDevice(HWND& _hWnd) {

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

        hr = D3D11CreateDeviceAndSwapChain(NULL, driverTypes[driverTypeIndex],
                                           NULL, createDeviceFlags, 
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
    else {

        auto backBuffer = new CTextureDX();

        hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
            (LPVOID*)&backBuffer->m_pTexture);

        ///Checamos que todo salga bien, si no mandamos un error
        if (FAILED(hr)) {

            delete backBuffer;
            return false;
        }
        else {

            hr = m_pd3dDevice->CreateRenderTargetView(backBuffer->m_pTexture,
                nullptr,
                &backBuffer->m_pRenderTargetView);

            if (FAILED(hr)) {

                delete backBuffer;
                return false;
            }
            else {

                m_pBackBuffer = backBuffer;

                return true;
            }
        }
    }
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

CTexture* CGraphicApiDX::LoadTextureFromFile(const std::wstring _srcFile){

    HRESULT hr = S_OK;

    return nullptr;
}

///
/// U P D A T E´s
/// 

void CGraphicApiDX::UpdateConstantBuffer(const void* _srcData, 
    CConstantBuffer& _updateDataCB){

    auto constantBuffer = reinterpret_cast<CConstantBufferDX&>(_updateDataCB);
    m_pImmediateContext->UpdateSubresource(constantBuffer.m_pConstantBuffer, 0,
        nullptr, _srcData,
        0, 0);
}

///
/// C L E A R´s
/// 

CTexture* CGraphicApiDX::ClearYourRenderTargetView(CTexture* _renderTargetDX){

    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f };
    auto renderTarget = reinterpret_cast<CTextureDX*>(_renderTargetDX);

    m_pImmediateContext->ClearRenderTargetView(renderTarget->m_pRenderTargetView,
        ClearColor);

    return renderTarget;
}

CTexture* CGraphicApiDX::ClearYourDepthStencilView(CTexture* _depthStencilDX){

    auto depthStencil = reinterpret_cast<CTextureDX*>(_depthStencilDX);

    m_pImmediateContext->ClearDepthStencilView(depthStencil->m_pDepthStencilView,
        D3D11_CLEAR_DEPTH, 1.0f, 0);

    return depthStencil;
}

void CGraphicApiDX::CleanUpDevices(std::vector<CTexture*> _renderTargetView, CTexture* _depthStencilView,
    CVertexShader* _vertexShaderDX, CInputLayout* _vertexLayoutDX, 
    CPixelShader* _pixelShaderDX, CVertexBuffer* _vertexBufferDX, 
    CIndexBuffer* _indexBufferDX, CConstantBuffer* _neverChangesDX,
    CConstantBuffer* _changeOnResizeDX, CConstantBuffer* _changesEveryFrameDX, 
    CSamplerState* _samplerDX){

    auto sampler = reinterpret_cast<CSamplerStateDX*>(_samplerDX);
    auto neverChanges = reinterpret_cast<CConstantBufferDX*>(_neverChangesDX);
    auto changeOnResize = reinterpret_cast<CConstantBufferDX*>(_changeOnResizeDX);
    auto changeEveryFrame = reinterpret_cast<CConstantBufferDX*>(_changesEveryFrameDX);
    auto vertexBuffer = reinterpret_cast<CVertexBufferDX*>(_vertexBufferDX);
    auto indexBuffer = reinterpret_cast<CIndexBufferDX*>(_indexBufferDX);
    auto vertexLayout = reinterpret_cast<CInputLayoutDX*>(_vertexLayoutDX);
    auto vertexShader = reinterpret_cast<CVertexShaderDX*>(_vertexShaderDX);
    auto pixelShader = reinterpret_cast<CPixelShaderDX*>(_pixelShaderDX);
    auto depthStencilView = reinterpret_cast<CTextureDX*>(_depthStencilView);
    auto depthStencil = reinterpret_cast<CTextureDX*>(m_pDepthStencil);


    for (unsigned int i = 0; i < _renderTargetView.size(); i++) {

        auto renderTargetView = reinterpret_cast<CTextureDX*>(_renderTargetView[i]);
        //if (renderTargetView) { renderTargetView->m_pRenderTargetView->Release(); }
    }


    if (m_pImmediateContext) { m_pImmediateContext->ClearState(); }

    if (sampler) { sampler->m_pSamplerState->Release(); }
    if (neverChanges) { neverChanges->m_pConstantBuffer->Release(); }
    if (changeOnResize) {changeOnResize->m_pConstantBuffer->Release();}
    if (changeEveryFrame) {changeEveryFrame->m_pConstantBuffer->Release();}
    if (vertexBuffer) {vertexBuffer->m_pVertexBuffer->Release();}
    if (indexBuffer) {indexBuffer->m_pIndexBuffer->Release();}
    if (vertexLayout) {vertexLayout->m_pVertexLayout->Release();}
    if (vertexShader) {vertexShader->m_pVertexShader->Release();}
    if (pixelShader) {pixelShader->m_pPixelShader->Release();}
    if (depthStencil) {depthStencil->m_pDepthStencilState->Release();}
    if (depthStencilView) {depthStencilView->m_pDepthStencilView->Release();}
    if (m_pSwapChain) { m_pSwapChain->Release(); }
    if (m_pImmediateContext) { m_pImmediateContext->Release(); }
    if (m_pd3dDevice) { m_pd3dDevice->Release(); }
}

///
/// C R E A T E´s 
/// 

/// 
CPixelShader* CGraphicApiDX::CreatePixelShader(const std::wstring& _namePS, 
    const std::string& _entryPointDX){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    auto pixelShader = new CPixelShaderDX();

    ///Asignamos datos a las variables
    pixelShader->m_pPSBlob = NULL;
    HRESULT hr = S_OK;

    ///Compilamos el shader recibido
    hr = CompileShaderFromFile(_namePS, _entryPointDX.c_str(), "ps_4_0", &pixelShader->m_pPSBlob);

    ///Checamos que todo salga bien, si no mandamos un error
    if (FAILED(hr)){

        return nullptr;
    }
    else {

        ///Creamos el pixel shader con la función de DX
        hr = m_pd3dDevice->CreatePixelShader(pixelShader->m_pPSBlob->GetBufferPointer(),
            pixelShader->m_pPSBlob->GetBufferSize(),
            nullptr, &pixelShader->m_pPixelShader);

        pixelShader->m_pPSBlob->Release();

        ///Finalmente regresamos el dato en caso
        ///de no obtener un error
        if (FAILED(hr)) {

            return nullptr;
        }
        else {

            return pixelShader;
        }
    }
}

/// 
CVertexShader* CGraphicApiDX::CreateVertexShader(const std::wstring& _nameVSDX, 
    const std::string& _entryPointDX){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    auto vertexShader = new CVertexShaderDX();

    ///Asignamos datos a las variables
    vertexShader->m_pVSBlob = NULL;
    HRESULT hr = S_OK;

    ///Compilamos el shader recibido
    hr = CompileShaderFromFile(_nameVSDX, _entryPointDX.c_str(), "vs_4_0", &vertexShader->m_pVSBlob);

    ///Checamos que todo salga bien, si no mandamos un error
    if (FAILED(hr)){

        return nullptr;
    }
    else {

        ///Creamos el vertex shader con la función de DX
        hr = m_pd3dDevice->CreateVertexShader(vertexShader->m_pVSBlob->GetBufferPointer(),
            vertexShader->m_pVSBlob->GetBufferSize(),
            nullptr, &vertexShader->m_pVertexShader);

        ///Finalmente regresamos el dato en caso
        ///de no obtener un error
        if (FAILED(hr)) {

            vertexShader->m_pVSBlob->Release();
            return nullptr;
        }
        else {

            return vertexShader;
        }
    }
}

///
CVertexBuffer* CGraphicApiDX::CreateVertexBuffer(const std::vector <SimpleVertex>& _simpleVertexDX){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    auto vertexBuffer = new CVertexBufferDX();

    ///Asignamos datos a la variable
    HRESULT hr = S_OK;
    
    ///Rellenamos el descriptor de buffer
    CD3D11_BUFFER_DESC bd(_simpleVertexDX.size() * sizeof(SimpleVertex),
                          D3D11_BIND_VERTEX_BUFFER);

    ///Generamos una variable descriptor
    D3D11_SUBRESOURCE_DATA InitData;

    ///Limpiamos la memoria y dejamos
    ///definido todo en 0
    ZeroMemory(&InitData, sizeof(InitData));

    ///Asignamos datos a las variables
    InitData.pSysMem = _simpleVertexDX.data();

    ///Creamos el buffer
    hr = m_pd3dDevice->CreateBuffer(&bd, &InitData, 
                                    &vertexBuffer->m_pVertexBuffer);

    ///Finalmente regresamos el dato en caso
    ///de no obtener un error
    if (FAILED(hr)) {

        return nullptr;
    }
    else {

        return vertexBuffer;
    }
}

///
CIndexBuffer* CGraphicApiDX::CreateIndexBuffer(const std::vector <uint32_t>& _simpleIndexDX){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    auto indexBuffer = new CIndexBufferDX();

    ///Asignamos datos a la variable
    HRESULT hr = S_OK;

    ///Rellenamos el descriptor de buffer
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(uint32_t) * _simpleIndexDX.size();
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    bd.CPUAccessFlags = 0;
    bd.MiscFlags = 0;

    ///Generamos una variable descriptor
    D3D11_SUBRESOURCE_DATA InitData;
    ///Limpiamos la memoria y dejamos
    ///definido todo en 0
    ZeroMemory(&InitData, sizeof(InitData));
    ///Asignamos datos a las variables
    InitData.pSysMem = &_simpleIndexDX[0];
    InitData.SysMemPitch = 0;
    InitData.SysMemSlicePitch = 0;

    ///Creamos el buffer
    hr = m_pd3dDevice->CreateBuffer(&bd, &InitData, 
                                    &indexBuffer->m_pIndexBuffer);

    ///Finalmente regresamos el dato en caso
    ///de no obtener un error
    if (FAILED(hr)) {

        return nullptr;
    }
    else {

        return indexBuffer;
    }
}

///
CConstantBuffer* CGraphicApiDX::CreateConstantBuffer(const unsigned int _bufferSizeDX){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    auto constantBuffer = new CConstantBufferDX();

    ///Asignamos datos a la variable
    HRESULT hr = S_OK;

    ///Rellenamos el descriptor de buffer
    CD3D11_BUFFER_DESC bd(_bufferSizeDX, D3D11_BIND_CONSTANT_BUFFER);

    ///Creamos el buffer
    hr = m_pd3dDevice->CreateBuffer(&bd, nullptr,
                                    &constantBuffer->m_pConstantBuffer);

    ///Finalmente regresamos el dato en caso
    ///de no obtener un error
    if (FAILED(hr)) {

        return nullptr;
    }
    else {

        return constantBuffer;
    }
}

///
CTexture* CGraphicApiDX::CreateTexture(const unsigned int _widthDX, 
    const unsigned int _heightDX, 
    const unsigned int _bindFlagsDX, 
    TEXTURE_FORMAT _textureFormatDX){

    ///Asignamos datos a la variable
    HRESULT hr = S_OK;
    
    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    auto texture = new CTextureDX();

    ///Rellenamos el descriptor
    D3D11_TEXTURE2D_DESC textureDesc;
    ZeroMemory(&textureDesc, sizeof(textureDesc));
    textureDesc.Width = _widthDX;
    textureDesc.Height = _heightDX;
    textureDesc.MipLevels = 1;
    textureDesc.ArraySize = 1;
    textureDesc.Format = (DXGI_FORMAT)_textureFormatDX;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.SampleDesc.Quality = 0;
    textureDesc.Usage = D3D11_USAGE_DEFAULT;
    textureDesc.BindFlags = _bindFlagsDX;
    textureDesc.CPUAccessFlags = 0;
    textureDesc.MiscFlags = 0;

    ///Creamos la textura
    hr = m_pd3dDevice->CreateTexture2D(&textureDesc, nullptr, &texture->m_pTexture);
    
    if (FAILED(hr)) {

        return nullptr;
    }

    ///RenderTargetView
    if (_bindFlagsDX & D3D11_BIND_RENDER_TARGET) {

        
    }
    ///DepthStencilView
    if (_bindFlagsDX & D3D11_BIND_DEPTH_STENCIL) {
        
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

            return nullptr;
        }
        else {

            return texture;
        }
    }
    ///ShaderResourceView
    if (_bindFlagsDX & D3D11_BIND_SHADER_RESOURCE) {

        CD3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc(D3D11_SRV_DIMENSION_TEXTURE2D);

        hr = m_pd3dDevice->CreateShaderResourceView(texture->m_pTexture,
            &shaderResourceViewDesc,
            &texture->m_pShaderResourceView);

        ///Checamos que todo salga bien, si no mandamos un error
        if (FAILED(hr)) {

            return nullptr;
        }
        else {

            return texture;
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

        return nullptr;
    }
    else {

        return samplerState;
    }
}

//Function Creates an input layout from the vertex shader, after compilation.
//Input layout can be reused with any vertex shaders that use the same input layout.
CInputLayout* CGraphicApiDX::CreateInputLayout(CVertexShader& _vertexShaderDX){

    ///Asignamos datos a la variable
    HRESULT hr = S_OK;

    auto inputLayout = new CInputLayoutDX();
    auto vertexShader = reinterpret_cast<CVertexShaderDX&>(_vertexShaderDX);

    ///Generamos la información del shader
    ID3D11ShaderReflection* pVertexShaderReflection = nullptr;

    if (FAILED(D3DReflect(vertexShader.m_pVSBlob->GetBufferPointer(),
        vertexShader.m_pVSBlob->GetBufferSize(),
        IID_ID3D11ShaderReflection,
        (void**)&pVertexShaderReflection))){

        return nullptr;
    }
    else {

        ///Generamos una descriptor del shader
        D3D11_SHADER_DESC shaderDesc;

        ///Obtenemos la información de nuestro
        ///descriptor del shader
        pVertexShaderReflection->GetDesc(&shaderDesc);

        ///Leer la descripción del input layout de 
        /// la información del sombreador
        unsigned int byteOffset = 0;
        std::vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;

        for (unsigned int i = 0; i < shaderDesc.InputParameters; i++) {

            D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
            pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

            ///Creamos y guardamos la información
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

        ///Liberación de memoria de reflexión de shader de asignación
        pVertexShaderReflection->Release();

        ///Checamos que todo salga bien, si no mandamos un error
        if (FAILED(hr)) {

            return nullptr;
        }
        else {

            ///Registro de longitud de bytes
            inputLayout->inputLayoutByteLength = &byteOffset;

            return inputLayout;
        }
    }
}

/// 
/// S E T´s
///

/// Punteros constantes
void CGraphicApiDX::SetPixelShader(CPixelShader& _pixelShaderDX) {

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    ///Y hacemos un casteo reinterprete para convertir el puntero
    auto pixelShader = reinterpret_cast<CPixelShaderDX&> (_pixelShaderDX);

    m_pImmediateContext->PSSetShader(pixelShader.m_pPixelShader, NULL, 0);
}

/// 
void CGraphicApiDX::SetVertexShader(CVertexShader& _vertexShaderDX){

    auto vertexShader = reinterpret_cast<CVertexShaderDX&>(_vertexShaderDX);

    m_pImmediateContext->VSSetShader(vertexShader.m_pVertexShader, NULL, 0);
}

/// 
void CGraphicApiDX::SetVertexBuffer(CVertexBuffer& _vertexBufferDX){

    auto vertexBuffer = reinterpret_cast<CVertexBufferDX&>(_vertexBufferDX);

    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;
    m_pImmediateContext->IASetVertexBuffers(0, 
                                            1, 
                                            &vertexBuffer.m_pVertexBuffer,
                                            &stride, 
                                            &offset);
}

/// 
void CGraphicApiDX::SetIndexBuffer(CIndexBuffer& _indexBufferDX){

    auto indexBuffer = reinterpret_cast<CIndexBufferDX&>(_indexBufferDX);

    m_pImmediateContext->IASetIndexBuffer(indexBuffer.m_pIndexBuffer,
                                          DXGI_FORMAT_R32_UINT, 
                                          0);
}

/// 
void CGraphicApiDX::SetConstantBuffer(CConstantBuffer& _constantBufferDX,
    const unsigned int _startSlotDX,
    const unsigned int _numBuffersDX){

    auto constantBuffer = reinterpret_cast<CConstantBufferDX&>(_constantBufferDX);

    m_pImmediateContext->VSSetConstantBuffers(_startSlotDX, _numBuffersDX,
                                              &constantBuffer.m_pConstantBuffer);
}

/// 
void CGraphicApiDX::SetSamplerState(const unsigned int _startSlotDX,
    std::vector<CSamplerState*>& _samplerStateDX) {

    for (unsigned int i = 0; i < _samplerStateDX.size(); i++) {

        auto samplerState = reinterpret_cast<CSamplerStateDX*>(_samplerStateDX[i]);

        m_pImmediateContext->PSSetSamplers(_startSlotDX,
                                           _samplerStateDX.size(),
                                           &samplerState->m_pSamplerState);
    }
}

///
void CGraphicApiDX::SetShaderResourceView(std::vector <CTexture*>& _shaderResourceViewDX,
    const unsigned int _startSlotDX,
    const unsigned int _numViewsDX){

    for (unsigned int i = 0; i < _shaderResourceViewDX.size(); i++) {

        auto shaderResource = reinterpret_cast<CTextureDX&>(_shaderResourceViewDX[i]);

        m_pImmediateContext->PSSetShaderResources(_startSlotDX, _numViewsDX,
            &shaderResource.m_pShaderResourceView);
    }
}

///
void CGraphicApiDX::SetRenderTarget(CTexture& _renderTargetDX,
    CTexture& _depthStencilDX) {

    auto depthStencil = reinterpret_cast<CTextureDX&>(_depthStencilDX);
    auto renderTarget = reinterpret_cast<CTextureDX&>(_renderTargetDX);
    m_pImmediateContext->OMSetRenderTargets(1, &renderTarget.m_pRenderTargetView,
        depthStencil.m_pDepthStencilView);
}

///
void CGraphicApiDX::SetDepthStencil(CTexture& _depthStencilDX,
    const unsigned int _stencilRefDX){

    auto depthStencil = reinterpret_cast<CTextureDX&>(_depthStencilDX);

    m_pImmediateContext->OMSetDepthStencilState(depthStencil.m_pDepthStencilState, 
        _stencilRefDX);
}

///
void CGraphicApiDX::SetInputLayout(CInputLayout& _vertexLayoutDX){

    auto inputLayout = reinterpret_cast<CInputLayoutDX&>(_vertexLayoutDX);

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

void CGraphicApiDX::SetYourVS(CVertexShader& _vertexShaderDX){

    auto vertexShader = reinterpret_cast<CVertexShaderDX&>(_vertexShaderDX);

    m_pImmediateContext->VSSetShader(vertexShader.m_pVertexShader,
        nullptr, 0);
}

void CGraphicApiDX::SetYourVSConstantBuffers(CConstantBuffer* _constantBufferDX,
    const unsigned int _startSlotDX,
    const unsigned int _numBuffersDX){

    auto constantBuffer = reinterpret_cast<CConstantBufferDX*>(_constantBufferDX);

    m_pImmediateContext->VSSetConstantBuffers(_startSlotDX, _numBuffersDX,
        &constantBuffer->m_pConstantBuffer);
}

void CGraphicApiDX::SetYourPS(CPixelShader& _pixelShaderDX){

    auto pixelShader = reinterpret_cast<CPixelShaderDX&>(_pixelShaderDX);

    m_pImmediateContext->PSSetShader(pixelShader.m_pPixelShader,
        nullptr, 0);
}

void CGraphicApiDX::SetYourPSConstantBuffers(CConstantBuffer* _constantBufferDX,
    const unsigned int _startSlotDX, 
    const unsigned int _numBuffersDX){

    auto constantBuffer = reinterpret_cast<CConstantBufferDX*>(_constantBufferDX);

    m_pImmediateContext->PSSetConstantBuffers(_startSlotDX, _numBuffersDX,
        &constantBuffer->m_pConstantBuffer);
}

void CGraphicApiDX::SetYourPSSampler(CSamplerState& _samplerDX, 
    const unsigned int _startSlotDX, 
    const unsigned int _numSamplersDX){

    auto sampler = reinterpret_cast<CSamplerStateDX&>(_samplerDX);

    m_pImmediateContext->PSSetSamplers(_startSlotDX, _numSamplersDX,
        &sampler.m_pSamplerState);
}
