#include "..\Includes\CGraphicApiOGL.h"
#include "..\Includes\CVertexBufferOGL.h"
#include "..\Includes\CVertexShaderOGL.h"
#include "..\Includes\CPixelShaderOGL.h"
#include "..\Includes\CIndexBufferOGL.h"
#include "..\Includes\CTextureOGL.h"
#include "..\Includes\CSamplerStateOGL.h"

#include <iostream>

///
/// H E R E N C I A
///

bool CGraphicApiOGL::InitDevice(HWND& _hWnd){

	return false;
}

void CGraphicApiOGL::DrawIndex(unsigned int _indexCountDX, 
	unsigned int _startIndexLocationDX, 
	unsigned int _baseVertexLocationDX){}

void CGraphicApiOGL::SwapChainPresent(unsigned int _syncIntervalDX, 
	unsigned int _flagsDX){}

CTexture* CGraphicApiOGL::LoadTextureFromFile(const std::string _srcFile){return nullptr;}

CTexture* CGraphicApiOGL::GetDefaultBackBuffer(){return nullptr;}

void CGraphicApiOGL::BindOGL(){

	glUseProgram(m_rendererID);
}

void CGraphicApiOGL::UnbindOGL(){

	glUseProgram(0);
}

///
/// U P D A T E´s
/// 

void CGraphicApiOGL::UpdateConstantBuffer(const void* _srcDataDX, 
	CConstantBuffer& _updateDataCBDX){}

///
/// C L E A R´s
/// 

CTexture* CGraphicApiOGL::ClearYourRenderTargetView(CTexture* _renderTargetDX){


	return nullptr;
}

CTexture* CGraphicApiOGL::ClearYourDepthStencilView(CTexture* _depthStencilDX){


	return nullptr;
}

void CGraphicApiOGL::CleanUpDevices(std::vector<CTexture*> _renderTargetView, 
	CTexture* _depthStencilView, CVertexShader* _vertexShaderDX, 
	CInputLayout* _vertexLayoutDX, CPixelShader* _pixelShaderDX, 
	CVertexBuffer* _vertexBufferDX, CIndexBuffer* _indexBufferDX, 
	CConstantBuffer* _neverChangesDX, CConstantBuffer* _changeOnResizeDX, 
	CConstantBuffer* _changesEveryFrameDX, CSamplerState* _samplerDX){}

///
/// C R E A T E´s 
///

CPixelShader* CGraphicApiOGL::CreatePixelShader(const std::wstring& _namePSDX,
	const std::string& _entryPointDX,
	const std::string& _fragmentSrcOGL) {

	auto PS = new CPixelShaderOGL();

	// Create an empty fragment shader handle
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Send the fragment shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	const GLchar* source = _fragmentSrcOGL.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	// Compile the fragment shader
	glCompileShader(fragmentShader);

	GLint isCompiled = 0;
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);

	if (GL_FALSE == isCompiled) {

		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(fragmentShader);

		std::cout << "ERROR: compilación del fragment shader\n";

		// Use the infoLog as you see fit.
		return nullptr;
	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	m_rendererID = glCreateProgram();
	GLuint program = m_rendererID;

	// Attach our shaders to our program
	glAttachShader(program, fragmentShader);

	// Link our program
	glLinkProgram(program);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);

	if (GL_FALSE == isLinked) {

		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(program);
		// Don't leak shaders either.
		glDeleteShader(fragmentShader);

		std::cout << "ERROR: compilación del link shader\n";

		// Use the infoLog as you see fit.
		return nullptr;
	}

	PS->m_fragmentShader = &fragmentShader;

	// Always detach shaders after a successful link.
	glDetachShader(program, fragmentShader);

	return PS;
}

CVertexShader* CGraphicApiOGL::CreateVertexShader(const std::wstring& _nameVSDX, 
	const std::string& _entryPointDX,
	const std::string& _vertexSrcOGL){

	auto VS = new CVertexShaderOGL();

	// Create an empty vertex shader handle
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Send the vertex shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	const GLchar* source = _vertexSrcOGL.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	// Compile the vertex shader
	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);

	if (GL_FALSE == isCompiled){

		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(vertexShader);

		std::cout << "ERROR: compilación del vertex shader\n";

		// Use the infoLog as you see fit.
		return nullptr;
	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	m_rendererID = glCreateProgram();
	GLuint program = m_rendererID;

	// Attach our shaders to our program
	glAttachShader(program, vertexShader);

	// Link our program
	glLinkProgram(program);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);

	if (GL_FALSE == isLinked){

		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(program);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);

		std::cout << "ERROR: compilación del link shader\n";

		// Use the infoLog as you see fit.
		return nullptr;
	}

	VS->m_vertexShader = &vertexShader;

	// Always detach shaders after a successful link.
	glDetachShader(program, vertexShader);

	return VS;
}

CVertexBuffer* CGraphicApiOGL::CreateVertexBuffer(const std::vector<SimpleVertex>& _simpleVertexDX,
	const unsigned int _numBufferObjectsOGL, unsigned int _vertexBufferObjectOGL){

	auto VBO = new CVertexBufferOGL();
	VBO->m_vertexBufferObject = &_vertexBufferObjectOGL;

	///Creamos objetos de búfer y devolvemos los identificadores de los objetos de búfer
	glGenBuffers(_numBufferObjectsOGL, VBO->m_vertexBufferObject);

	///Enlazamos VBO para la matriz de vértices
	glBindBuffer(GL_ARRAY_BUFFER, *VBO->m_vertexBufferObject);

	///Copiamos los datos en el objeto de búfer
	glBufferData(GL_ARRAY_BUFFER, sizeof(_simpleVertexDX), &_simpleVertexDX, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	return VBO;
}

CIndexBuffer* CGraphicApiOGL::CreateIndexBuffer(const std::vector<uint32_t>& _simpleIndexDX,
	const unsigned int _numBufferObjectsOGL, unsigned int _indexBufferObjectOGL){

	auto PBO = new CIndexBufferOGL();
	PBO->m_indexBufferObject = &_indexBufferObjectOGL;

	///Creamos objetos de búfer y devolvemos los identificadores de los objetos de búfer
	glGenBuffers(_numBufferObjectsOGL, PBO->m_indexBufferObject);

	///Enlazamos VBO para la matriz de vértices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *PBO->m_indexBufferObject);

	///Copiamos los datos en el objeto de búfer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_simpleIndexDX), &_simpleIndexDX, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return PBO;
}

CConstantBuffer* CGraphicApiOGL::CreateConstantBuffer(const unsigned int _bufferSizeDX){


	return nullptr;
}

CTexture* CGraphicApiOGL::CreateTexture(const unsigned int _widthDX, 
	const unsigned int _heightDX, const unsigned int _bindFlagsDX, 
	TEXTURE_FORMAT _textureFormatDX,
	const std::string _fileNameOGL){

	auto tex = new CTextureOGL();

	unsigned int texture;

	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load and generate the texture
	int width, height, nrChannels;

	unsigned char* data = stbi_load(_fileNameOGL.c_str(), &width, &height, &nrChannels, 0);

	if (data){

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		tex->m_texture = &texture;
		tex->m_data = data;
	}
	else{

		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);
	return tex;
}

CSamplerState* CGraphicApiOGL::CreateSamplerState() {

	auto samplerState = new CSamplerStateOGL();

	GLuint sampler_state = 0;
	glGenSamplers(1, &sampler_state);
	glSamplerParameteri(sampler_state, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(sampler_state, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glSamplerParameteri(sampler_state, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler_state, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	GLuint texture_unit = 0;
	glBindSampler(texture_unit, sampler_state);

	samplerState->m_samplerState = &sampler_state;
	samplerState->m_textureUnit = &texture_unit;

	glBindSampler(texture_unit, 0);

	glDeleteSamplers(1, &sampler_state);

	return samplerState;
}

CInputLayout* CGraphicApiOGL::CreateInputLayout(CVertexShader& _vertexShaderDX){


	return nullptr;
}

///
/// S E T´s 
///

void CGraphicApiOGL::SetPixelShader(CPixelShader& _pixelShaderDX){


}

void CGraphicApiOGL::SetVertexShader(CVertexShader& _vertexShaderDX){


}

void CGraphicApiOGL::SetVertexBuffer(CVertexBuffer& _vertexBufferDX){


}

void CGraphicApiOGL::SetIndexBuffer(CIndexBuffer& _indexBufferDX){


}

void CGraphicApiOGL::SetConstantBuffer(CConstantBuffer& _constantBufferDX, 
	const unsigned int _startSlotDX, const unsigned int _numBuffersDX){


}

void CGraphicApiOGL::SetSamplerState(const unsigned int _startSlotDX, 
	std::vector<CSamplerState*>& _samplerStateDX){


}

void CGraphicApiOGL::SetShaderResourceView(std::vector<CTexture*>& _shaderResourceViewDX, 
	const unsigned int _startSlotDX, const unsigned int _numViewsDX){


}

void CGraphicApiOGL::SetRenderTarget(CTexture& _renderTargetDX, 
	CTexture& _depthStencilDX){


}

void CGraphicApiOGL::SetDepthStencil(CTexture& _depthStencilDX, 
	const unsigned int _stencilRefDX){


}

void CGraphicApiOGL::SetInputLayout(CInputLayout& _vertexLayoutDX){


}

void CGraphicApiOGL::SetViewport(const unsigned int _numViewportsDX, 
	const unsigned int _widthDX, const unsigned int _heigthDX){


}

void CGraphicApiOGL::SetPrimitiveTopology(const unsigned int _topologyDX){


}

void CGraphicApiOGL::SetYourVS(CVertexShader& _vertexShaderDX){


}

void CGraphicApiOGL::SetYourVSConstantBuffers(CConstantBuffer* _constantBufferDX, 
	const unsigned int _startSlotDX, const unsigned int _numBuffersDX){


}

void CGraphicApiOGL::SetYourPS(CPixelShader& _pixelShaderDX){


}

void CGraphicApiOGL::SetYourPSConstantBuffers(CConstantBuffer* _constantBufferDX, 
	const unsigned int _startSlotDX, const unsigned int _numBuffersDX){


}

void CGraphicApiOGL::SetYourPSSampler(CSamplerState& _samplerDX, 
	const unsigned int _startSlotDX, const unsigned int _numSamplersDX){


}