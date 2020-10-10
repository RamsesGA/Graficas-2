#include "..\Includes\CSampleStateDX.h"

void CSampleStateDX::Init(unsigned int* _sampler, 
						  unsigned int _filter, unsigned int _addresU, 
						  unsigned int _addressV, unsigned int _addressW, 
						  unsigned int _camparisionFunc, float _minLOD, 
						  float _maxLOD){

	m_filter = (D3D11_FILTER)_filter;
	m_addressU = (D3D11_TEXTURE_ADDRESS_MODE)_addresU;
	m_addressV = (D3D11_TEXTURE_ADDRESS_MODE)_addressV;
	m_addressW = (D3D11_TEXTURE_ADDRESS_MODE)_addressW;
	m_comparissionFunc = (D3D11_COMPARISON_FUNC)_camparisionFunc;
	m_minLOD = _minLOD;
	m_maxLOD = _maxLOD;

}