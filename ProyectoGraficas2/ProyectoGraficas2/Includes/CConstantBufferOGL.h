#pragma once
#include "CConstantBuffer.h"

class CConstantBufferOGL : public CConstantBuffer {

	protected:
		///
		/// Miembros
		/// 

		unsigned int m_uniformBufferObject;
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