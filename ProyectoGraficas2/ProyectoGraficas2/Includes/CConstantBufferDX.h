#pragma once
#include <d3d11.h>
#include "CConstantBuffer.h"

class CConstantBufferDX : public CConstantBuffer {

	protected:
		///
		/// Miembros
		/// 

		ID3D11Buffer* m_pConstantBuffer;

	public:
		///
		/// Métodos
		/// 

		///Constructor
		CConstantBufferDX() = default;
		///Destructor
		~CConstantBufferDX() = default;

friend class CGraphicApiDX;
};