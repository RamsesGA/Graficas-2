#pragma once
#include "CInputLayout.h"

class CInputLayoutOGL : public CInputLayout {

	public:
		///
		/// Miembros
		/// 
		
		///
		/// Métodos
		/// 
		CInputLayoutOGL() = default;
		~CInputLayoutOGL() = default;

		void Init(char* _semanticName, unsigned int _semanticIndex,
				  unsigned int _format, unsigned int _inputSlot,
				  unsigned int _alignedByteOffset, unsigned int _inputSlotClass,
				  unsigned int _instanceDataStepRate, unsigned int _numElements)override;
};