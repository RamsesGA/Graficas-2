#pragma once

class CVertexBuffer {

	public:
		///
		/// M�todos
		/// 
		CVertexBuffer() = default;
		~CVertexBuffer() = default;

		virtual void Init(unsigned int _shaderType) = 0;
};