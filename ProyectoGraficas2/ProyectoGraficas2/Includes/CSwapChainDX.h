#pragma once
#include "CSwapChain.h"
#include <d3d11.h>

class CSwapChainDX : public CSwapChain{

	public:
		///
		/// Miembros
		/// 
		IDXGISwapChain* g_pSwapChain;


		///
		/// M�todos
		/// 
		CSwapChainDX() = default;
		~CSwapChainDX() = default;

		void Init()override;
};