#pragma once

class CSampleState {

	public:
		///
		/// Métodos
		/// 
		CSampleState() = default;
		~CSampleState() = default;

		virtual void Init(unsigned int* _sampler,
						  unsigned int _filter, unsigned int _addresU,
						  unsigned int _addressV, unsigned int _addressW,
						  unsigned int _camparisionFunc, float _minLOD,
						  float _maxLOD) = 0;
};