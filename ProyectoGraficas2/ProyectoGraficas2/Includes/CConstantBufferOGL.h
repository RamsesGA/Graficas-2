#pragma once
#include "CConstantBuffer.h"

class CConstantBufferOGL : public CConstantBuffer {

	protected:
		///
		/// Miembros
		/// 

		unsigned int m_uniformBufferObject;
		const unsigned int m_bufferSize;

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