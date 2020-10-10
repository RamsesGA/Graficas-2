#pragma once
#include "CSampleState.h"
#include "glew-2.1.0/include/GL/glew.h"

class CSampleStateOGL : public CSampleState {

	public:
		///
		/// Miembros
		/// 
		GLuint* m_samplers;

		///
		/// Métodos
		/// 
		CSampleStateOGL() = default;
		~CSampleStateOGL() = default;

		void Init(unsigned int* _sampler,
				  unsigned int _filter, unsigned int _addresU,
				  unsigned int _addressV, unsigned int _addressW,
				  unsigned int _camparisionFunc, float _minLOD,
				  float _maxLOD)override;
};