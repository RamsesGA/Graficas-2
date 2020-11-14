#pragma once
#include <string>
#include <vector>
#include <windows.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

/// <summary>
/// Enum con todos los números
/// con el tipo de bind flag
/// para DX
/// </summary>
using TEXTURE_BIND_FLAG = enum
{
    TEXTURE_BIND_SHADER_RESOURCE = 0x8L,
    TEXTURE_BIND_RENDER_TARGET = 0x20L,
    TEXTURE_BIND_DEPTH_STENCIL = 0x40L,
    TEXTURE_BIND_UNORDERED_ACCESS = 0x80L,
};
/// <summary>
/// Enum con todos los números
/// con el tipo de formato
/// para DX
/// </summary>
using TEXTURE_FORMAT = enum
{
    TEXTURE_FORMAT_UNKNOWN = 0,
    TEXTURE_FORMAT_R32G32B32A32_TYPELESS = 1,
    TEXTURE_FORMAT_R32G32B32A32_FLOAT = 2,
    TEXTURE_FORMAT_R32G32B32A32_UINT = 3,
    TEXTURE_FORMAT_R32G32B32A32_SINT = 4,
    TEXTURE_FORMAT_R32G32B32_TYPELESS = 5,
    TEXTURE_FORMAT_R32G32B32_FLOAT = 6,
    TEXTURE_FORMAT_R32G32B32_UINT = 7,
    TEXTURE_FORMAT_R32G32B32_SINT = 8,
    TEXTURE_FORMAT_R16G16B16A16_TYPELESS = 9,
    TEXTURE_FORMAT_R16G16B16A16_FLOAT = 10,
    TEXTURE_FORMAT_R16G16B16A16_UNORM = 11,
    TEXTURE_FORMAT_R16G16B16A16_UINT = 12,
    TEXTURE_FORMAT_R16G16B16A16_SNORM = 13,
    TEXTURE_FORMAT_R16G16B16A16_SINT = 14,
    TEXTURE_FORMAT_R32G32_TYPELESS = 15,
    TEXTURE_FORMAT_R32G32_FLOAT = 16,
    TEXTURE_FORMAT_R32G32_UINT = 17,
    TEXTURE_FORMAT_R32G32_SINT = 18,
    TEXTURE_FORMAT_R32G8X24_TYPELESS = 19,
    TEXTURE_FORMAT_D32_FLOAT_S8X24_UINT = 20,
    TEXTURE_FORMAT_R32_FLOAT_X8X24_TYPELESS = 21,
    TEXTURE_FORMAT_X32_TYPELESS_G8X24_UINT = 22,
    TEXTURE_FORMAT_R10G10B10A2_TYPELESS = 23,
    TEXTURE_FORMAT_R10G10B10A2_UNORM = 24,
    TEXTURE_FORMAT_R10G10B10A2_UINT = 25,
    TEXTURE_FORMAT_R11G11B10_FLOAT = 26,
    TEXTURE_FORMAT_R8G8B8A8_TYPELESS = 27,
    TEXTURE_FORMAT_R8G8B8A8_UNORM = 28,
    TEXTURE_FORMAT_R8G8B8A8_UNORM_SRGB = 29,
    TEXTURE_FORMAT_R8G8B8A8_UINT = 30,
    TEXTURE_FORMAT_R8G8B8A8_SNORM = 31,
    TEXTURE_FORMAT_R8G8B8A8_SINT = 32,
    TEXTURE_FORMAT_R16G16_TYPELESS = 33,
    TEXTURE_FORMAT_R16G16_FLOAT = 34,
    TEXTURE_FORMAT_R16G16_UNORM = 35,
    TEXTURE_FORMAT_R16G16_UINT = 36,
    TEXTURE_FORMAT_R16G16_SNORM = 37,
    TEXTURE_FORMAT_R16G16_SINT = 38,
    TEXTURE_FORMAT_R32_TYPELESS = 39,
    TEXTURE_FORMAT_D32_FLOAT = 40,
    TEXTURE_FORMAT_R32_FLOAT = 41,
    TEXTURE_FORMAT_R32_UINT = 42,
    TEXTURE_FORMAT_R32_SINT = 43,
    TEXTURE_FORMAT_R24G8_TYPELESS = 44,
    TEXTURE_FORMAT_D24_UNORM_S8_UINT = 45,
    TEXTURE_FORMAT_R24_UNORM_X8_TYPELESS = 46,
    TEXTURE_FORMAT_X24_TYPELESS_G8_UINT = 47,
    TEXTURE_FORMAT_R8G8_TYPELESS = 48,
    TEXTURE_FORMAT_R8G8_UNORM = 49,
    TEXTURE_FORMAT_R8G8_UINT = 50,
    TEXTURE_FORMAT_R8G8_SNORM = 51,
    TEXTURE_FORMAT_R8G8_SINT = 52,
    TEXTURE_FORMAT_R16_TYPELESS = 53,
    TEXTURE_FORMAT_R16_FLOAT = 54,
    TEXTURE_FORMAT_D16_UNORM = 55,
    TEXTURE_FORMAT_R16_UNORM = 56,
    TEXTURE_FORMAT_R16_UINT = 57,
    TEXTURE_FORMAT_R16_SNORM = 58,
    TEXTURE_FORMAT_R16_SINT = 59,
    TEXTURE_FORMAT_R8_TYPELESS = 60,
    TEXTURE_FORMAT_R8_UNORM = 61,
    TEXTURE_FORMAT_R8_UINT = 62,
    TEXTURE_FORMAT_R8_SNORM = 63,
    TEXTURE_FORMAT_R8_SINT = 64,
    TEXTURE_FORMAT_A8_UNORM = 65,
    TEXTURE_FORMAT_R1_UNORM = 66,
    TEXTURE_FORMAT_R9G9B9E5_SHAREDEXP = 67,
    TEXTURE_FORMAT_R8G8_B8G8_UNORM = 68,
    TEXTURE_FORMAT_G8R8_G8B8_UNORM = 69,
    TEXTURE_FORMAT_BC1_TYPELESS = 70,
    TEXTURE_FORMAT_BC1_UNORM = 71,
    TEXTURE_FORMAT_BC1_UNORM_SRGB = 72,
    TEXTURE_FORMAT_BC2_TYPELESS = 73,
    TEXTURE_FORMAT_BC2_UNORM = 74,
    TEXTURE_FORMAT_BC2_UNORM_SRGB = 75,
    TEXTURE_FORMAT_BC3_TYPELESS = 76,
    TEXTURE_FORMAT_BC3_UNORM = 77,
    TEXTURE_FORMAT_BC3_UNORM_SRGB = 78,
    TEXTURE_FORMAT_BC4_TYPELESS = 79,
    TEXTURE_FORMAT_BC4_UNORM = 80,
    TEXTURE_FORMAT_BC4_SNORM = 81,
    TEXTURE_FORMAT_BC5_TYPELESS = 82,
    TEXTURE_FORMAT_BC5_UNORM = 83,
    TEXTURE_FORMAT_BC5_SNORM = 84,
    TEXTURE_FORMAT_B5G6R5_UNORM = 85,
    TEXTURE_FORMAT_B5G5R5A1_UNORM = 86,
    TEXTURE_FORMAT_B8G8R8A8_UNORM = 87,
    TEXTURE_FORMAT_B8G8R8X8_UNORM = 88,
    TEXTURE_FORMAT_R10G10B10_XR_BIAS_A2_UNORM = 89,
    TEXTURE_FORMAT_B8G8R8A8_TYPELESS = 90,
    TEXTURE_FORMAT_B8G8R8A8_UNORM_SRGB = 91,
    TEXTURE_FORMAT_B8G8R8X8_TYPELESS = 92,
    TEXTURE_FORMAT_B8G8R8X8_UNORM_SRGB = 93,
    TEXTURE_FORMAT_BC6H_TYPELESS = 94,
    TEXTURE_FORMAT_BC6H_UF16 = 95,
    TEXTURE_FORMAT_BC6H_SF16 = 96,
    TEXTURE_FORMAT_BC7_TYPELESS = 97,
    TEXTURE_FORMAT_BC7_UNORM = 98,
    TEXTURE_FORMAT_BC7_UNORM_SRGB = 99,
    TEXTURE_FORMAT_FORCE_UINT = 0xffffffff
};
/// <summary>
/// Enum con todas los números
/// con el tipo de topología
/// para DX
/// </summary>
using PRIMITIVE_TOPOLOGY = enum
{
    PRIMITIVE_TOPOLOGY_UNDEFINED = 0,
    PRIMITIVE_TOPOLOGY_POINTLIST = 1,
    PRIMITIVE_TOPOLOGY_LINELIST = 2,
    PRIMITIVE_TOPOLOGY_LINESTRIP = 3,
    PRIMITIVE_TOPOLOGY_TRIANGLELIST = 4,
    PRIMITIVE_TOPOLOGY_TRIANGLESTRIP = 5,
    PRIMITIVE_TOPOLOGY_LINELIST_ADJ = 10,
    PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ = 11,
    PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ = 12,
    PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ = 13,
    PRIMITIVE_TOPOLOGY_1_CONTROL_POINT_PATCHLIST = 33,
    PRIMITIVE_TOPOLOGY_2_CONTROL_POINT_PATCHLIST = 34,
    PRIMITIVE_TOPOLOGY_3_CONTROL_POINT_PATCHLIST = 35,
    PRIMITIVE_TOPOLOGY_4_CONTROL_POINT_PATCHLIST = 36,
    PRIMITIVE_TOPOLOGY_5_CONTROL_POINT_PATCHLIST = 37,
    PRIMITIVE_TOPOLOGY_6_CONTROL_POINT_PATCHLIST = 38,
    PRIMITIVE_TOPOLOGY_7_CONTROL_POINT_PATCHLIST = 39,
    PRIMITIVE_TOPOLOGY_8_CONTROL_POINT_PATCHLIST = 40,
    PRIMITIVE_TOPOLOGY_9_CONTROL_POINT_PATCHLIST = 41,
    PRIMITIVE_TOPOLOGY_10_CONTROL_POINT_PATCHLIST = 42,
    PRIMITIVE_TOPOLOGY_11_CONTROL_POINT_PATCHLIST = 43,
    PRIMITIVE_TOPOLOGY_12_CONTROL_POINT_PATCHLIST = 44,
    PRIMITIVE_TOPOLOGY_13_CONTROL_POINT_PATCHLIST = 45,
    PRIMITIVE_TOPOLOGY_14_CONTROL_POINT_PATCHLIST = 46,
    PRIMITIVE_TOPOLOGY_15_CONTROL_POINT_PATCHLIST = 47,
    PRIMITIVE_TOPOLOGY_16_CONTROL_POINT_PATCHLIST = 48,
    PRIMITIVE_TOPOLOGY_17_CONTROL_POINT_PATCHLIST = 49,
    PRIMITIVE_TOPOLOGY_18_CONTROL_POINT_PATCHLIST = 50,
    PRIMITIVE_TOPOLOGY_19_CONTROL_POINT_PATCHLIST = 51,
    PRIMITIVE_TOPOLOGY_20_CONTROL_POINT_PATCHLIST = 52,
    PRIMITIVE_TOPOLOGY_21_CONTROL_POINT_PATCHLIST = 53,
    PRIMITIVE_TOPOLOGY_22_CONTROL_POINT_PATCHLIST = 54,
    PRIMITIVE_TOPOLOGY_23_CONTROL_POINT_PATCHLIST = 55,
    PRIMITIVE_TOPOLOGY_24_CONTROL_POINT_PATCHLIST = 56,
    PRIMITIVE_TOPOLOGY_25_CONTROL_POINT_PATCHLIST = 57,
    PRIMITIVE_TOPOLOGY_26_CONTROL_POINT_PATCHLIST = 58,
    PRIMITIVE_TOPOLOGY_27_CONTROL_POINT_PATCHLIST = 59,
    PRIMITIVE_TOPOLOGY_28_CONTROL_POINT_PATCHLIST = 60,
    PRIMITIVE_TOPOLOGY_29_CONTROL_POINT_PATCHLIST = 61,
    PRIMITIVE_TOPOLOGY_30_CONTROL_POINT_PATCHLIST = 62,
    PRIMITIVE_TOPOLOGY_31_CONTROL_POINT_PATCHLIST = 63,
    PRIMITIVE_TOPOLOGY_32_CONTROL_POINT_PATCHLIST = 64
};
/// <summary>
/// Estructura con los datos
/// para el vertex buffer
/// </summary>
struct SimpleVertex{

	glm::vec4 Pos;
	glm::vec2 Tex;
};
/// <summary>
/// Estructura con los datos
/// para la creación de una camara
/// </summary>
struct CameraDescriptor {

    float s_width;
    float s_height;
    float s_near;
    float s_far;
    float s_foV;
    glm::vec3 s_eye;
    glm::vec3 s_lookAt;
    glm::vec3 s_up;
};

/// <summary>
/// Instancias de las clases
/// abstraidas
/// </summary>
class CConstantBuffer;
class CTexture;
class CSamplerState;
class CInputLayout;
class CShaders;
class CVertexBuffer;
class CIndexBuffer;

/// <summary>
/// Clase padre donde podremos añadir 
/// nuevas funciones para generalizar
/// una api gráfica
/// </summary>
class CGraphicApi {

	protected:
		///
		/// M I E M B R O S
		/// 

        /// <summary>
        /// Miembro para guardar la
        /// anchura de la pantalla
        /// </summary>
        unsigned int m_width;
        /// <summary>
        /// Miembro para guarda la
        /// altura de la pantalla
        /// </summary>
        unsigned int m_height;

	public:
		///
		/// M É T O D O S
		/// 
		
        ///Constructor
		CGraphicApi() = default;
		///Destructor
		~CGraphicApi() = default;

        virtual bool InitDevice(HWND& _hWnd) = 0;

        virtual void DrawIndex(unsigned int _indexCount,
            unsigned int _startIndexLocation,
            unsigned int _baseVertexLocation ) = 0;

        virtual void SwapChainPresent(unsigned int _syncInterval ,
            unsigned int _flags ) = 0;

        virtual CTexture* LoadTextureFromFile(const std::string _srcFile) = 0;

        virtual CTexture* GetDefaultBackBuffer() = 0;

        virtual void UnbindOGL() = 0;

        ///
        /// U P D A T E´s
        /// 

        virtual void UpdateConstantBuffer(const void* _srcData , 
            CConstantBuffer& _updateDataCB ) = 0;

        ///
        /// C L E A R´s
        /// 

        virtual CTexture* ClearYourRenderTargetView(CTexture* _renderTarget ) = 0;

        virtual CTexture* ClearYourDepthStencilView(CTexture* _depthStencil ) = 0;

        virtual void CleanUpDevices() = 0;

		///
		/// C R E A T E´s
		/// 

        /// <summary>
        /// Función para generar el
        /// vertex shader o vertex resource
        /// Función para generar el
        /// pixel shader o fragment shader 
        /// </summary>
        /// <param name="_nameVS"></param>
        /// <param name="_vertexSrc"></param>
        /// <param name="_namePS"></param>
        /// <param name="_entryPoint"></param>
        /// <param name="_fragmentSrc"></param>
        /// <returns></returns>
        virtual CShaders* CreateVertexAndPixelShader(const std::wstring& _nameVS,
            const std::string& _entryPointVS,
            const std::string& _vertexSrc,
            const std::wstring& _namePS,
            const std::string& _entryPointPS,
            const std::string& _fragmentSrc) = 0;
        /// <summary>
        /// Función para generar el
        /// vertex buffer
        /// </summary>
        /// <param name="_simpleVertex"></param>
        /// <param name="_vertexBufferObject"></param>
        /// <returns></returns>
        virtual CVertexBuffer* CreateVertexBuffer(const std::vector <SimpleVertex>& _simpleVertex,
            unsigned int _vertexBufferObject) = 0;
        /// <summary>
        /// Función para generar el
        /// index buffer
        /// </summary>
        /// <param name="_simpleIndex"></param>
        /// <param name="_indexBufferObject"></param>
        /// <returns></returns>
        virtual CIndexBuffer* CreateIndexBuffer(const std::vector <uint32_t> & _simpleIndex,
            unsigned int _indexBufferObject) = 0;
		/// <summary>
        /// Función para generar los
        /// constant buffer
		/// </summary>
		/// <param name="_bufferSize "></param>
		/// <returns></returns>
		virtual CConstantBuffer* CreateConstantBuffer(const unsigned int _bufferSize ) = 0;
		/// <summary>
        /// Función para generar lo siguiente:
        /// °ShaderResourceView
        /// °DepthStencilView
        /// °RenderTargetView
		/// </summary>
		/// <param name="_width "></param>
		/// <param name="_height "></param>
		/// <param name="_bindFlags "></param>
		/// <param name="_textureFormat "></param>
		/// <returns></returns>
        virtual CTexture* CreateTexture(const unsigned int _width ,
            const unsigned int _height ,
            const unsigned int _bindFlags ,
            TEXTURE_FORMAT _textureFormat ,
            const std::string _fileName ) = 0;
        /// <summary>
        /// Función para generar el
        /// sampler state
        /// </summary>
        /// <returns></returns>
        virtual CSamplerState* CreateSamplerState() = 0;
		/// <summary>
        /// Función para generar el
        /// input layout
		/// </summary>
		/// <param name="_vertexShader "></param>
		/// <returns></returns>
		virtual CInputLayout* CreateInputLayout(CShaders& _vertexShader ) = 0;

		///
		/// S E T´s
		/// 

		/// <summary>
        /// Función para guardar la
        /// información del pixel shader
		/// </summary>
		/// <param name="_pixelShader "></param>
		virtual void SetPixelShader(CShaders& _pixelShader ) = 0;
		/// <summary>
        /// Función para guardar la
        /// información del vertex shader
		/// </summary>
		/// <param name="_vertexShader "></param>
		virtual void SetVertexShader(CShaders& _vertexShader ) = 0;
		/// <summary>
        /// Función para guardar la
        /// información del vertex buffer
		/// </summary>
		/// <param name="_vertexBuffer "></param>
		virtual void SetVertexBuffer(CVertexBuffer& _vertexBuffer ) = 0;
		/// <summary>
        /// Función para guardar la
        /// información del index buffer
		/// </summary>
		/// <param name="_indexBuffer "></param>
		virtual void SetIndexBuffer(CIndexBuffer& _indexBuffer ) = 0;
		/// <summary>
        /// Función para guardar la
        /// información de los constant buffers
		/// </summary>
		/// <param name="_constantBuffer "></param>
		/// <param name="_startSlot "></param>
		/// <param name="_numBuffers "></param>
		virtual void SetConstantBuffer(CConstantBuffer& _constantBuffer , 
            const unsigned int _startSlot , 
            const unsigned int _numBuffers ) = 0;
        /// <summary>
        /// Función para guardar la
        /// información del sampler state
        /// </summary>
        /// <param name="_startSlot "></param>
        /// <param name="_samplerState "></param>
        virtual void SetSamplerState(const unsigned int _startSlot ,
            std::vector<CSamplerState*>& _samplerState ) = 0;
        /// <summary>
        /// Función para guardar la información
        /// del shader resource view
        /// </summary>
        /// <param name="_shaderResourceView "></param>
        /// <param name="_startSlot "></param>
        /// <param name="_numViews "></param>
        virtual void SetShaderResourceView(std::vector <CTexture*>& _shaderResourceView ,
            const unsigned int _startSlot ,
            const unsigned int _numViews ) = 0;
        /// <summary>
        /// Función para guardar la información
        /// del render target
        /// </summary>
        /// <param name="_renderTarget "></param>
        /// <param name="_depthStencil "></param>
        virtual void SetRenderTarget(CTexture& _renderTarget ,
            CTexture& _depthStencil ) = 0;
        /// <summary>
        /// Función para gaurdar la información
        /// del depth stencil
        /// </summary>
        /// <param name="_depthStencil "></param>
        /// <param name="_stencilRef "></param>
        virtual void SetDepthStencil(CTexture& _depthStencil ,
            const unsigned int _stencilRef ) = 0;
		/// <summary>
        /// Función para guardar la
        /// información del input layout
		/// </summary>
		/// <param name="_vertexLayout "></param>
		virtual void SetInputLayout(CInputLayout& _vertexLayout ) = 0;
        /// <summary>
        /// Función para guardar la
        /// información del viewport
        /// </summary>
        /// <param name="_numViewports "></param>
        /// <param name="_width "></param>
        /// <param name="_heigth "></param>
        virtual void SetViewport(const unsigned int _numViewports ,
            const unsigned int _width , const unsigned int _heigth ) = 0;
        /// <summary>
        /// Función para guardar la información
        /// de la topología
        /// </summary>
        /// <param name="_topology "></param>
        virtual void SetPrimitiveTopology(const unsigned int _topology ) = 0;
        /// <summary>
        /// Función para mandar a llamar
        /// VSSetShader
        /// </summary>
        /// <param name="_vertexShader "></param>
        virtual void SetYourVS(CShaders& _vertexShader ) = 0;
        /// <summary>
        /// Función para mandar a llamar
        /// VSSetConstantBuffers
        /// </summary>
        /// <param name="_constantBuffer "></param>
        /// <param name="_startSlot "></param>
        /// <param name="_numBuffers "></param>
        virtual void SetYourVSConstantBuffers(CConstantBuffer* _constantBuffer ,
            const unsigned int _startSlot ,
            const unsigned int _numBuffers ) = 0;
        /// <summary>
        /// Función para mandar a llamar
        /// PSSetShader
        /// </summary>
        /// <param name="_pixelShader "></param>
        virtual void SetYourPS(CShaders& _pixelShader ) = 0;
        /// <summary>
        /// Función para mandar a llamar
        /// PSSetConstantBuffers
        /// </summary>
        /// <param name="_constantBuffer "></param>
        /// <param name="_startSlot "></param>
        /// <param name="_numBuffers "></param>
        virtual void SetYourPSConstantBuffers(CConstantBuffer* _constantBuffer ,
            const unsigned int _startSlot ,
            const unsigned int _numBuffers ) = 0;
        /// <summary>
        /// Función para mandar a llamar
        /// PSSetSamplers
        /// </summary>
        /// <param name="_sampler "></param>
        /// <param name="_startSlot "></param>
        /// <param name="_numSamplers "></param>
        virtual void SetYourPSSampler(CSamplerState& _sampler ,
            const unsigned int _startSlot ,
            const unsigned int _numSamplers ) = 0;
};