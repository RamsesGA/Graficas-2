#include "..\Includes\CSampleStateOGL.h"

void CSampleStateOGL::Init(unsigned int* _sampler, 
						   unsigned int _filter, unsigned int _addresU, 
						   unsigned int _addressV, unsigned int _addressW, 
						   unsigned int _camparisionFunc, float _minLOD, 
						   float _maxLOD){

	m_samplers = _sampler;
}