#pragma once
#include "CShaders.h"

class CShadersOGL : public CShaders {

	protected:
		///
		/// Miembros
		/// 
	
		/// <summary>
		/// Miembro para linkear
		/// el programa
		/// </summary>
		uint32_t m_rendererID;
		/// <summary>
		/// Miembro para guardar la posici�n
		/// de la informaci�n
		/// </summary>
		unsigned int m_vertexShader;
		/// <summary>
		/// Miembro para guardar la posici�n
		/// de la informaci�n
		/// </summary>
		unsigned int m_fragmentShader;
	
	public:
		///
		/// M�todos
		/// 
	
		///Constructor
		CShadersOGL() = default;
		///Destyructor
		~CShadersOGL() = default;
friend class CGraphicApiOGL;
};