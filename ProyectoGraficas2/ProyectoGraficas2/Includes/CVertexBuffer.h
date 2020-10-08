#pragma once

class CVertexBuffer {

	public:
		///
		/// Métodos
		/// 
		CVertexBuffer() = default;
		~CVertexBuffer() = default;

		virtual void Init(const char* vertexPath, const char* fragmentPath,
						  const char* geometryPath) = 0;
};