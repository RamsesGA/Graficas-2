#pragma once
#include "CSamplerState.h"
#include <d3d11.h>

class CSamplerStateDX : public CSamplerState {

	protected:
		///
		/// Miembros
		/// 

		ID3D11SamplerState* m_pSamplerState;

	public:
		///
		/// Métodos
		/// 

		///Constructor
		CSamplerStateDX() = default;
		///Destructor
		~CSamplerStateDX() = default;

friend class CGraphicApiDX;
};