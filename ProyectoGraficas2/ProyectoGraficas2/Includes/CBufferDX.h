#pragma once
#include "CBuffer.h"
#include <d3d11.h>

class CBufferDX : public CBuffer{

	public:
		///
		/// Miembros
		/// 
		unsigned int m_byteWidth;
		unsigned int m_usage;
		unsigned int m_bindFlags;
		unsigned int m_cpuAccessFlags;
		unsigned int m_miscFlags;
		unsigned int m_structureByteStride;

		ID3D11Buffer* m_pVertexBuffer;

		///
		/// Métodos
		/// 
		CBufferDX() = default;
		~CBufferDX() = default;

		void Init(unsigned int _bufferOGL,
				  unsigned int _byteWidth, unsigned int _usage,
				  unsigned int _bindFlags, unsigned int _CPUAccessFlags,
				  unsigned int _miscFlags, unsigned int _structureByteStride,
			      const void* _pSysMem)override;
};