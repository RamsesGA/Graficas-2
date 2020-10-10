#include "..\Includes\CInputLayoutDX.h"

void CInputLayoutDX::Init(char* _semanticName, unsigned int _semanticIndex, 
						  unsigned int _format, unsigned int _inputSlot, 
						  unsigned int _alignedByteOffset, unsigned int _inputSlotClass, 
						  unsigned int _instanceDataStepRate, unsigned int _numElements){

	m_semanticName = _semanticName;
	m_semanticIndex = _semanticIndex;
	m_format = (DXGI_FORMAT) _format;
	m_inputSlot = _inputSlot;
	m_alignedByteOffset = _alignedByteOffset;
	m_inputSlotClass = (D3D11_INPUT_CLASSIFICATION)_inputSlotClass;
	m_instanceDataStepRate = _instanceDataStepRate;
	m_numElements = _numElements;
}
