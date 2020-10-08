#pragma once

class CVertexBuffer {

	public:
		///
		/// M�todos
		/// 
		CVertexBuffer() = default;
		~CVertexBuffer() = default;

		virtual void Init(const char* vertexPath, const char* fragmentPath,
						  const char* geometryPath) = 0;
};