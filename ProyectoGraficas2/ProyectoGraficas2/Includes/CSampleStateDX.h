#pragma once
#include "CSampleState.h"
#include <d3d11.h>

class CSampleStateDX : public CSampleState {

	public:
		///
		/// Miembros
		/// 
		ID3D11SamplerState* m_pSamplerLinear;
		D3D11_FILTER m_filter;
		D3D11_TEXTURE_ADDRESS_MODE m_addressU;
		D3D11_TEXTURE_ADDRESS_MODE m_addressV;
		D3D11_TEXTURE_ADDRESS_MODE m_addressW;
		D3D11_COMPARISON_FUNC m_comparissionFunc;
		FLOAT m_minLOD;
		FLOAT m_maxLOD;

		///
		/// Métodos
		///
		CSampleStateDX() = default;
		~CSampleStateDX() = default;
		
		void Init(unsigned int* _sampler,
				  unsigned int _filter, unsigned int _addresU,
				  unsigned int _addressV, unsigned int _addressW,
				  unsigned int _camparisionFunc, float _minLOD,
				  float _maxLOD)override;
};