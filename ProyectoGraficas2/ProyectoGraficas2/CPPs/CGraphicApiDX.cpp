#include "../Includes/CGraphicApiDX.h"
#include "../Includes/CBufferDX.h"
#include "../Includes/CTexturesDX.h"
#include "../Includes/CVertexBufferDX.h"

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
    ///Inicializamos el buffer
    _pBuffer->Init(_bufferOGL, _byteWidth, 
                   _usage, _bindFlags, 
                   _CPUAccessFlags, _miscFlags, 
                   _structureByteStride, _pSysMem);

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
    _pTexture->Init(_texture, _width, 
                    _height, _mipLevels, 
                    _arraySize, _format, 
                    _sampleDescCount, _sampleDescQuality, 
                    _usage, _bindFlags, 
                    _cpuAccessFlags, _miscFlags, 
                    _pSysMem);

    return 0;
}

int CGraphicApiDX::GACreateVertexShader(const char* _vertexPath, const char* _fragmentPath,
                                        const char* _geometryPath) {
    HRESULT hr = S_OK;
    ID3DBlob* pVSBlob = NULL;
    hr = CompileShaderFromFile(L"Tutorial07.fx", "VS", "vs_4_0", &pVSBlob);
    if (FAILED(hr)){
        MessageBox(NULL,
            L"The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", L"Error", MB_OK);
        return hr;
    }

    CVertexBufferDX vertexBuff;

    // Create the vertex shader
    hr = m_pDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &vertexBuff.m_pVertexShader);
    if (FAILED(hr)){
        pVSBlob->Release();
        return hr;
    }
    return 0;
}

int CGraphicApiDX::GACreatePixelShader(const void* _pShaderBytecode, SIZE_T _bytecodeLength, 
                                       ID3D11ClassLinkage* _pClassLinkage, ID3D11PixelShader** _ppPixelShader){

    return 0;
}














int CGraphicApiDX::GACreateDeviceAndSwapChain() {


    return 0;
}

int CGraphicApiDX::GACreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* _pInputElementDescs, unsigned int _numElements, 
                                       const void* _pShaderBytecodeWithInputSignature, SIZE_T _bytecodeLength, 
                                       ID3D11InputLayout** _ppInputLayout){

    return 0;
}



int CGraphicApiDX::GACreateSamplerState(const D3D11_SAMPLER_DESC* _pSamplerDesc, ID3D11SamplerState** _ppSamplerState){

    return 0;
}

int CGraphicApiDX::GACreateDepthStencil(const D3D11_DEPTH_STENCIL_DESC* _pDepthStencilDesc, ID3D11DepthStencilState** _ppDepthStencilState){

    return 0;
}

int CGraphicApiDX::GACreateRasterizerState(const D3D11_RASTERIZER_DESC* _pRasterizerDesc, ID3D11RasterizerState** _ppRasterizerState){

    return 0;
}

int CGraphicApiDX::GACreateDeferredContext(unsigned int _contextFlags, ID3D11DeviceContext** _ppDeferredContext){

    return 0;
}

int CGraphicApiDX::GACreateRenderTargetView(ID3D11Resource* _pResource, const D3D11_RENDER_TARGET_VIEW_DESC* _pDesc, 
                                            ID3D11RenderTargetView** _ppRTView){

    return 0;
}

int CGraphicApiDX::GACreateDepthStencilView(ID3D11Resource* _pResource, const D3D11_DEPTH_STENCIL_VIEW_DESC* _pDesc, 
                                            ID3D11DepthStencilView** _ppDepthStencilView){

    return 0;
}

int CGraphicApiDX::GACreateShaderResourceView(ID3D11Resource* _pResource, const D3D11_SHADER_RESOURCE_VIEW_DESC* _pDesc, 
                                              ID3D11ShaderResourceView** _ppSRView){

    return 0;
}

///
/// S E T
/// 

int CGraphicApiDX::GASetDeviceAndSwapChain(){

    return 0;
}

int CGraphicApiDX::GASetBuffer(){

    return 0;
}

int CGraphicApiDX::GASetTexture2D(){

    return 0;
}

int CGraphicApiDX::GASetPixelShader(){

    return 0;
}

int CGraphicApiDX::GASetInputLayout(){

    return 0;
}

int CGraphicApiDX::GASetVertexShader(){

    return 0;
}

int CGraphicApiDX::GASetSamplerState(){

    return 0;
}

int CGraphicApiDX::GASetDepthStencil(){

    return 0;
}

int CGraphicApiDX::GASetRenderTarget(){

    return 0;
}

int CGraphicApiDX::GASetRasterizerState(){

    return 0;
}

int CGraphicApiDX::GASetDeferredContext(){

    return 0;
}

int CGraphicApiDX::GASetRenderTargetView(){

    return 0;
}

int CGraphicApiDX::GASetDepthStencilView(){

    return 0;
}

int CGraphicApiDX::GASetShaderResourceView(){

    return 0;
}