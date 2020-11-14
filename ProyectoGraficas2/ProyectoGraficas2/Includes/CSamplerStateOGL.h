#pragma once
#include "CSamplerState.h"

class CSamplerStateOGL : public CSamplerState {

	protected:
		///
		/// Miembros
		/// 

		unsigned int* m_samplerState;
		unsigned int* m_textureUnit;

	public:
		///
		/// M�todos
		///

		///Constructor
		CSamplerStateOGL() = default;
		///Destructor
		~CSamplerStateOGL() = default;
friend class CGraphicApiOGL;
};