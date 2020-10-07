#include "../Includes/CGraphicApiDX.h"
#include "../Includes/CBufferDX.h"

void CGraphicApiDX::Init(){

    m_pDevice = NULL;
    m_pDeviceContext = NULL;
}

int CGraphicApiDX::GACreateDeviceAndSwapChain(){


    return 0;
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

    D3D11_BUFFER_DESC pepe;
    pepe.ByteWidth = 

    m_pDevice->CreateBuffer(, ,_pBuffer);
    return 0;
}

int CGraphicApiDX::GACreateTexture3D(const D3D11_TEXTURE3D_DESC* _pDesc, const D3D11_SUBRESOURCE_DATA* _pInitialData, 
                                     ID3D11Texture3D** _ppTexture3D){

    return 0;
}

int CGraphicApiDX::GACreatePixelShader(const void* _pShaderBytecode, SIZE_T _bytecodeLength, 
                                       ID3D11ClassLinkage* _pClassLinkage, ID3D11PixelShader** _ppPixelShader){

    return 0;
}

int CGraphicApiDX::GACreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* _pInputElementDescs, unsigned int _numElements, 
                                       const void* _pShaderBytecodeWithInputSignature, SIZE_T _bytecodeLength, 
                                       ID3D11InputLayout** _ppInputLayout){

    return 0;
}

int CGraphicApiDX::GACreateVertexShader(const void* _pShaderBytecode, SIZE_T _bytecodeLength, 
                                        ID3D11ClassLinkage* _pClassLinkage, ID3D11VertexShader** _ppVertexShader){

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

int CGraphicApiDX::GASetTexture3D(){

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