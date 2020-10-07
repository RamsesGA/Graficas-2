#pragma once
#include "CGraphicApi.h"

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
};
