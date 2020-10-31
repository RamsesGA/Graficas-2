#pragma once
#include "CSamplerState.h"
#include <d3d11.h>

class CSamplerStateDX : public CSamplerState {

	public:
		///
		/// Miembros
		/// 

		ID3D11SamplerState* m_pSamplerState;

		///
		/// M�todos
		/// 

		///Constructor
		CSamplerStateDX() = default;
		///Destructor
		~CSamplerStateDX() = default;
};