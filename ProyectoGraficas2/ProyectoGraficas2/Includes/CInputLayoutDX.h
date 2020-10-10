#pragma once
#include "CInputLayout.h"
#include <d3d11.h>

class CInputLayoutDX : public CInputLayout{

	public:
		///
		/// Miembros
		/// 
		ID3D11InputLayout* m_pVertexLayout;
		LPCSTR m_semanticName;
		UINT m_semanticIndex;
		DXGI_FORMAT m_format;
		UINT m_inputSlot;
		UINT m_alignedByteOffset;
		D3D11_INPUT_CLASSIFICATION m_inputSlotClass;
		UINT m_instanceDataStepRate;
		unsigned int m_numElements;

		///
		/// Métodos
		/// 
		CInputLayoutDX() = default;
		~CInputLayoutDX() = default;

		void Init(char* _semanticName, unsigned int _semanticIndex,
				  unsigned int _format, unsigned int _inputSlot,
				  unsigned int _alignedByteOffset, unsigned int _inputSlotClass,
				  unsigned int _instanceDataStepRate, unsigned int _numElements)override;

};