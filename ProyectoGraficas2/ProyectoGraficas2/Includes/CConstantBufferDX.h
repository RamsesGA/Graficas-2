#pragma once
#include <d3d11.h>
#include "CConstantBuffer.h"

class CConstantBufferDX : public CConstantBuffer {

	public:
		///
		/// Miembros
		/// 

		/// <summary>
		/// Miembro de DX para guardar
		/// el buffer
		/// </summary>
		ID3D11Buffer* m_pConstantBuffer;

		///
		/// Métodos
		/// 

		///Constructor
		CConstantBufferDX() = default;
		///Destructor
		~CConstantBufferDX() = default;

friend class CGraphicApiDX;
};