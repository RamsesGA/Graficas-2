#pragma once
#include "CGraphicApi.h"
#include "glew-2.1.0/include/GL/glew.h"

/// <summary>
/// Clase donde manejaremos la lógica
/// gráfica de OpenGl
/// </summary>
class CGraphicApiOGL : public CGraphicApi{

	public:
		///
		///Métodos
		/// 
		CGraphicApiOGL() = default;
		~CGraphicApiOGL() = default;

		virtual void Init() = 0;

		virtual void Update() = 0;

		virtual void Delete() = 0;

		///
		/// Create
		///
		
		/// <summary>
		/// Creates a buffer (vertex buffer, 
		/// index buffer, or shader-constant buffer).
		/// </summary>
		/// <returns></returns>
		int GACreateBuffer(unsigned int _bufferOGL,
						   unsigned int _byteWidth, unsigned int _usage,
						   unsigned int _bindFlags, unsigned int _CPUAccessFlags,
						   unsigned int _miscFlags, unsigned int _structureByteStride,
						   const void* _pSysMem, CBuffer* _pBuffer)override;

		/// <summary>
		/// Create an array of 3D textures.
		/// </summary>
		/// <returns></returns>
		int GACreateTexture2D(unsigned int _texture,
							  unsigned int _width, unsigned int _height,
							  unsigned int _mipLevels, unsigned int _arraySize,
							  unsigned int _format, unsigned int _sampleDescCount,
							  unsigned int _sampleDescQuality, unsigned int _usage,
							  unsigned int _bindFlags, unsigned int _cpuAccessFlags,
							  unsigned int _miscFlags, const void* _pSysMem,
							  CTextures* _pTexture)override;
		/// <summary>
		/// Create a vertex-shader object from a compiled shader.
		/// </summary>
		/// <returns></returns>
		int GACreateVertexShader(const char* _vertexPath, const char* _fragmentPath,
								 const char* _geometryPath)override;
};
