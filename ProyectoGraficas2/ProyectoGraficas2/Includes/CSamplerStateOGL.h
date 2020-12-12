#pragma once
#include "CSamplerState.h"

class CSamplerStateOGL : public CSamplerState {

	protected:
		///
		/// Miembros
		/// 

		/// <summary>
		/// Miembro para almacenar el
		/// sampler state generado
		/// </summary>
		unsigned int m_samplerState;

	public:
		///
		/// Métodos
		///

		///Constructor
		CSamplerStateOGL() = default;
		///Destructor
		~CSamplerStateOGL() = default;
friend class CGraphicApiOGL;
};