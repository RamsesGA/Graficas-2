#pragma once
#include "CInputLayout.h"

class CInputLayoutOGL : public CInputLayout {

	protected:
		///
		/// Miembros
		/// 
		
		/// <summary>
		/// En OGL se conoce como
		/// vertex array object
		/// </summary>
		unsigned int m_inputLayout;

	public:
		///
		/// Métodos
		/// 
	
		///Constructor
		CInputLayoutOGL() = default;
		///Destructor
		~CInputLayoutOGL() = default;
	
friend class CGraphicApiOGL;
};