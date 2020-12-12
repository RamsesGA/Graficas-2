#pragma once
#include "CConstantBuffer.h"

class CConstantBufferOGL : public CConstantBuffer {

	protected:
		///
		/// Miembros
		/// 

		/// <summary>
		/// Miembro para almacenar el
		/// �ndice
		/// </summary>
		unsigned int m_uniformBufferObject;
		/// <summary>
		/// Miembro para guardar el tama�o
		/// del buffer
		/// </summary>
		unsigned int m_bufferSize;

	public:
		///
		/// M�todos
		/// 

		///Constructor
		CConstantBufferOGL() = default;
		///Destructor
		~CConstantBufferOGL() = default;
friend class CGraphicApiOGL;
};