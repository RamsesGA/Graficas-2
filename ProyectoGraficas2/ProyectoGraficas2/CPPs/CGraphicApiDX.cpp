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
bool CGraphicApiDX::InitDevice() {

    HRESULT hr = S_OK;

    RECT rc;

    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

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

        return true;
    }
}

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
    hr = CompileShaderFromFile(_namePS, _entryPointDX, "ps_4_0", &pixelShader->m_pPSBlob);

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
CVertexBuffer* CGraphicApiDX::CreateVertexBuffer(const std::vector <SimpleVertex*>& _simpleVertexDX){

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
CIndexBuffer* CGraphicApiDX::CreateIndexBuffer(const std::vector <unsigned int*>& _simpleIndexDX){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    auto indexBuffer = new CIndexBufferDX();

    ///Asignamos datos a la variable
    HRESULT hr = S_OK;

    ///Rellenamos el descriptor de buffer
    CD3D11_BUFFER_DESC bd(sizeof(unsigned int) * _simpleIndexDX.size(),
                          D3D11_BIND_INDEX_BUFFER);

    ///Generamos una variable descriptor
    D3D11_SUBRESOURCE_DATA InitData;

    ///Limpiamos la memoria y dejamos
    ///definido todo en 0
    ZeroMemory(&InitData, sizeof(InitData));

    ///Asignamos datos a las variables
    InitData.pSysMem = _simpleIndexDX.data();

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
CTexture* CGraphicApiDX::CreateTexture(const unsigned int _widthDX, 
    const unsigned int _heightDX, 
    const unsigned int _bindFlagsDX, 
    TEXTURE_FORMAT _textureFormatDX){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    auto texture = new CTextureDX();

    ///Asignamos datos a la variable
    HRESULT hr = S_OK;

    ///Rellenamos el descriptor de buffer
    CD3D11_TEXTURE2D_DESC textureDesc((DXGI_FORMAT)_textureFormatDX, _widthDX,
                                      _heightDX, _bindFlagsDX);

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
    
    ///ShaderResourceView
    if (_bindFlagsDX & D3D11_BIND_SHADER_RESOURCE) {

        CD3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc(D3D11_SRV_DIMENSION_TEXTURE2D);

        hr = m_pd3dDevice->CreateShaderResourceView(texture->m_pTexture,
            &shaderResourceViewDesc,
            &texture->m_pShaderResourceView);
    }
    ///DepthStencilView
    if (_bindFlagsDX & D3D11_BIND_DEPTH_STENCIL) {

        CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilDesc(D3D11_DSV_DIMENSION_TEXTURE2D);

        hr = m_pd3dDevice->CreateDepthStencilView(texture->m_pTexture,
            &depthStencilDesc,
            &texture->m_pDepthStencilView);
    }
    ///RenderTargetView
    if (_bindFlagsDX & D3D11_BIND_RENDER_TARGET) {

        CD3D11_RENDER_TARGET_VIEW_DESC renderTargetDesc(D3D11_RTV_DIMENSION_TEXTURE2D);

        hr = m_pd3dDevice->CreateRenderTargetView(texture->m_pTexture,
            &renderTargetDesc,
            &texture->m_pRenderTargetView);
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

//Function Creates an input layout from the vertex shader, after compilation.
//Input layout can be reused with any vertex shaders that use the same input layout.
CInputLayout* CGraphicApiDX::CreateInputLayout(CVertexShader& _vertexShaderDX){

    ///Asignamos datos a la variable
    HRESULT hr = S_OK;

    auto inputLayout = new CInputLayoutDX();
    auto vertexShader = reinterpret_cast<CVertexShaderDX&>(_vertexShaderDX);

    ///Generamos la información del shader
    ID3D11ShaderReflection* pVertexShaderReflection = nullptr;

    hr = D3DReflect(vertexShader.m_pVSBlob->GetBufferPointer(),
        vertexShader.m_pVSBlob->GetBufferSize(),
        IID_ID3D11ShaderReflection,
        (void**)pVertexShaderReflection);

    if (FAILED(hr)){

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

        ///Checamos que todo salga bien, si no mandamos un error
        if (FAILED(hr)) {

            MessageBox(
                NULL,
                L"hr nulo",
                L"Error",
                MB_OK);
            return nullptr;
        }
        else {

            ///Liberamos el puntero blob
            vertexShader.m_pVSBlob->Release();

            ///Liberación de memoria de reflexión de shader de asignación
            pVertexShaderReflection->Release();

            ///Registro de longitud de bytes
            *inputLayout->inputLayoutByteLength = byteOffset;

            return inputLayout;
        }
    }
}

///
/// Funciones de herencia
/// 

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

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    ///Y hacemos un casteo reinterprete para convertir el puntero
    auto vertexShader = reinterpret_cast<CVertexShaderDX&>(_vertexShaderDX);

    m_pImmediateContext->VSSetShader(vertexShader.m_pVertexShader, NULL, 0);
}

/// 
void CGraphicApiDX::SetVertexBuffer(CVertexBuffer& _vertexBufferDX){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    ///Y hacemos un casteo reinterprete para convertir el puntero
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

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    ///Y hacemos un casteo reinterprete para convertir el puntero
    auto indexBuffer = reinterpret_cast<CIndexBufferDX&>(_indexBufferDX);

    m_pImmediateContext->IASetIndexBuffer(indexBuffer.m_pIndexBuffer,
                                          DXGI_FORMAT_R16_UINT, 
                                          0);
}

/// 
void CGraphicApiDX::SetConstantBuffer(CConstantBuffer& _constantBufferDX,
    const unsigned int _startSlotDX,
    const unsigned int _numBuffersDX){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    ///Y hacemos un casteo reinterprete para convertir el puntero
    auto constantBuffer = reinterpret_cast<CConstantBufferDX&>(_constantBufferDX);

    m_pImmediateContext->VSSetConstantBuffers(_startSlotDX, _numBuffersDX,
                                              &constantBuffer.m_pConstantBuffer);
}

/// 
void CGraphicApiDX::SetSamplerState(const unsigned int _startSlotDX,
    std::vector<CSamplerState*>& _samplerStateDX) {

    for (unsigned int i = 0; i < _samplerStateDX.size(); i++) {

        ///Generamos una variable auto
        ///para adaptar el tipo de dato que ocupamos
        ///Y hacemos un casteo reinterprete para convertir el puntero
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

        ///Generamos una variable auto
        ///para adaptar el tipo de dato que ocupamos
        ///Y hacemos un casteo reinterprete para convertir el puntero
        auto shaderResource = reinterpret_cast<CTextureDX&>(_shaderResourceViewDX[i]);

        m_pImmediateContext->PSSetShaderResources(_startSlotDX, _numViewsDX,
            &shaderResource.m_pShaderResourceView);
    }
}

///
void CGraphicApiDX::SetRenderTarget(std::vector<CTexture*>& _renderTargetDX,
    CTexture& _depthStencilDX,
    const unsigned int _numViewsDX){

    auto depthStencil = reinterpret_cast<CTextureDX&>(_depthStencilDX);

    for (unsigned int i = 0; i < _renderTargetDX.size(); i++) {

        ///Generamos una variable auto
        ///para adaptar el tipo de dato que ocupamos
        ///Y hacemos un casteo reinterprete para convertir el puntero
        auto renderTarget = reinterpret_cast<CTextureDX&>(_renderTargetDX[i]);

        m_pImmediateContext->OMSetRenderTargets(_numViewsDX, &renderTarget.m_pRenderTargetView,
            depthStencil.m_pDepthStencilView);
    }
}

///
void CGraphicApiDX::SetDepthStencil(CTexture& _depthStencilDX,
    const unsigned int _stencilRefDX){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    ///Y hacemos un casteo reinterprete para convertir el puntero
    auto depthStencil = reinterpret_cast<CTextureDX&>(_depthStencilDX);

    m_pImmediateContext->OMSetDepthStencilState(depthStencil.m_pDepthStencilState, 
        _stencilRefDX);
}

///
void CGraphicApiDX::SetInputLayout(CInputLayout& _vertexLayoutDX){

    ///Generamos una variable auto
    ///para adaptar el tipo de dato que ocupamos
    ///Y hacemos un casteo reinterprete para convertir el puntero
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
