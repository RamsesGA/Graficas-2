#pragma once

class CInputLayout {

	public:
		///
		/// Métodos
		/// 
		CInputLayout() = default;
		~CInputLayout() = default;

		virtual void Init(char* _semanticName, unsigned int _semanticIndex,
						  unsigned int _format, unsigned int _inputSlot,
						  unsigned int _alignedByteOffset, unsigned int _inputSlotClass,
						  unsigned int _instanceDataStepRate, unsigned int _numElements) = 0;
};