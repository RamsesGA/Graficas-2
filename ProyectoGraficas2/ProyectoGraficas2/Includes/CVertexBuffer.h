#pragma once

class CVertexBuffer {

	public:
		///
		/// Métodos
		/// 
		CVertexBuffer() = default;
		~CVertexBuffer() = default;

		virtual void Init(unsigned int _shaderType) = 0;
};