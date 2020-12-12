#pragma once
#include "CConstantBuffer.h"

class CConstantBufferOGL : public CConstantBuffer {

	protected:
		///
		/// Miembros
		/// 

		/// <summary>
		/// Miembro para almacenar el
		/// índice
		/// </summary>
		unsigned int m_uniformBufferObject;
		/// <summary>
		/// Miembro para guardar el tamaño
		/// del buffer
		/// </summary>
		unsigned int m_bufferSize;

	public:
		///
		/// Métodos
		/// 

		///Constructor
		CConstantBufferOGL() = default;
		///Destructor
		~CConstantBufferOGL() = default;
friend class CGraphicApiOGL;
};