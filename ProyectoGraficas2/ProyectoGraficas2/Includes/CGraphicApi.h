#pragma once
#include <string>
#include <vector>
#include "glm/glm.hpp"

enum TEXTURE_FORMAT
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

struct SimpleVertex{

	glm::vec3 Pos;
	glm::vec2 Tex;
};

class CPixelShader;
class CVertexShader;
class CVertexBuffer;
class CIndexBuffer;
class CConstantBuffer;
class CTexture;
class CSamplerState;

/// <summary>
/// Clase padre donde podremos añadir 
/// nuevas funciones para generalizar
/// una api gráfica
/// </summary>
class CGraphicApi {

	private:
		///
		///Métodos
		/// 

		///
		/// Funciones internas
		/// 

		virtual bool MainInit() = 0;

		virtual bool InitWindow() = 0;

		virtual bool InitDevice() = 0;

	public:
		///
		///Métodos
		/// 
		
		///Constructor
		CGraphicApi() = default;
		///Destructor
		~CGraphicApi() = default;

		///
		/// Funciones para el usuario
		/// 
		
		///
		/// C R E A T E
		/// 

		/// Cambiar el tipo de dato que regresan, un puntero
		/// a ese tipo de clases


		virtual CPixelShader* CreatePixelShader(std::wstring _namePS,
												std::string _entryPoint) = 0;

		virtual CVertexShader* CreateVertexShader(std::wstring _nameVS, 
												  std::string _entryPoint) = 0;

		virtual CVertexBuffer* CreateVertexBuffer(unsigned int _bufferSize,
												  std::vector <SimpleVertex> _simpleVertex) = 0;

		virtual CIndexBuffer* CreateIndexBuffer(unsigned int _bufferSize,
											   std::vector <unsigned int> _simpleIndex) = 0;

		virtual CConstantBuffer* CreateConstantBuffer(unsigned int _bufferSize) = 0;

		virtual CTexture* CreateTexture(unsigned int _width,
										unsigned int _height,
										unsigned int _bindFlags,
										TEXTURE_FORMAT _textureFormat) = 0;

        virtual CSamplerState* CreateSamplerState() = 0;

		virtual bool CreateInputLayout() = 0;
		

		///
		/// S E T´s
		/// 

		virtual void SetPixelShader(CPixelShader* _pixelShader) = 0;

		virtual void SetVertexShader(CVertexShader* _vertexShader) = 0;

		virtual void SetVertexBuffer(CVertexBuffer* _vertexBuffer) = 0;

		virtual void SetIndexBuffer(CIndexBuffer* _indexBuffer) = 0;
	
		virtual void SetConstantBuffer(CConstantBuffer* _constantBuffer,
                                       unsigned int _startSlot,
                                       unsigned int _numBuffers);

		virtual void SetTexture(CTexture* _texture) = 0;

        virtual void SetSamplerState(unsigned int _startSlot,
                                     std::vector<CSamplerState*>& _samplerState) = 0;

		virtual void SetInputLayout() = 0;
};