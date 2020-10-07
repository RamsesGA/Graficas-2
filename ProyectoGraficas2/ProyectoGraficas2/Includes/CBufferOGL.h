#pragma once
#include "CBuffer.h"

class CBufferOGL : public CBuffer {

	public:
		///
		/// Miembros
		/// 
		unsigned int m_bufferOGL;

		///
		/// Métodos
		///
		CBufferOGL() = default;
		~CBufferOGL() = default;

		void Init(unsigned int _bufferOGL,
				  unsigned int _byteWidth, unsigned int _usage,
				  unsigned int _bindFlags, unsigned int _CPUAccessFlags,
				  unsigned int _miscFlags, unsigned int _structureByteStride,
				  const void* _pSysMem)override;
};