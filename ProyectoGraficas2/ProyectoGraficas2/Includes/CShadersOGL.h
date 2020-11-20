#pragma once
#include "CShaders.h"

class CShadersOGL : public CShaders {

	protected:
		///
		/// Miembros
		/// 
	
		/// <summary>
		/// 
		/// </summary>
		uint32_t m_rendererID;
		/// <summary>
		/// 
		/// </summary>
		unsigned int m_vertexShader;
		/// <summary>
		/// 
		/// </summary>
		unsigned int m_fragmentShader;
	
	public:
		///
		/// Métodos
		/// 
	
		///Constructor
		CShadersOGL() = default;
		///Destyructor
		~CShadersOGL() = default;
friend class CGraphicApiOGL;
};