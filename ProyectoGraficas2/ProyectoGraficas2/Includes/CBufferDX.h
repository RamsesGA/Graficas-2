#pragma once
#include "CBuffer.h"
#include <d3d11.h>

class CBufferDX : public CBuffer{

	public:
		///
		/// Miembros
		/// 
		UINT m_byteWidth;
		D3D11_USAGE m_usage;
		UINT m_bindFlags;
		UINT m_cpuAccessFlags;
		UINT m_miscFlags;
		UINT m_structureByteStride;

		const void* m_pSysMem;

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