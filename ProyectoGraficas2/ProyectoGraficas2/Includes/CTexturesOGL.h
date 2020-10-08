#pragma once
#include "CTextures.h"

class CTexturesOGL : public CTextures {

	public:
		///
		/// Miembros 
		/// 
		unsigned int m_texture;

		///
		/// Métodos
		/// 
		CTexturesOGL() = default;
		~CTexturesOGL() = default;
	
		//Falta el target de OGL, este lo defino yo


		void Init(unsigned int _texture,
				  unsigned int _width, unsigned int _height,
				  unsigned int _mipLevels, unsigned int _arraySize,
				  unsigned int _format, unsigned int _sampleDescCount,
				  unsigned int _sampleDescQuality, unsigned int _usage,
				  unsigned int _bindFlags, unsigned int _cpuAccessFlags,
				  unsigned int _miscFlags, const void* _pSysMem)override;
};