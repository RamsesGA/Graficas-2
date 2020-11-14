#include "..\Includes\CGraphicApiOGL.h"
#include "..\Includes\CTextureOGL.h"
#include "..\Includes\CSamplerStateOGL.h"
#include "..\Includes\CConstantBufferOGL.h"
#include "..\Includes\CShadersOGL.h"
#include "..\Includes\CVertexBufferOGL.h"
#include "..\Includes\CIndexBufferOGL.h"
#include "..\Includes\stb_image.h"

#include <iostream>

///
/// H E R E N C I A
///

bool CGraphicApiOGL::InitDevice(HWND& _hWnd){

	PIXELFORMATDESCRIPTOR pfd = {

		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	m_HandleToDC = GetDC(_hWnd);

	int pixelFormat = ChoosePixelFormat(m_HandleToDC, &pfd);

	SetPixelFormat(m_HandleToDC, pixelFormat, &pfd);

	m_renderingContext = wglCreateContext(m_HandleToDC);

	wglMakeCurrent(m_HandleToDC, m_renderingContext);

	if (!gladLoadGL()){

		return false;
	}
	else {

		RECT rc;

		GetWindowRect(_hWnd, &rc);

		m_width = rc.right - rc.left;
		m_height = rc.bottom - rc.top;

		SetViewport(1, m_width, m_height);

		glEnable(GL_DEPTH_TEST);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return true;
	}
}

void CGraphicApiOGL::DrawIndex(unsigned int _indexCount , 
	unsigned int _startIndexLocation , 
	unsigned int _baseVertexLocation ){}

void CGraphicApiOGL::SwapChainPresent(unsigned int _syncInterval , 
	unsigned int _flags ){}

CTexture* CGraphicApiOGL::LoadTextureFromFile(const std::string _srcFile){return nullptr;}

CTexture* CGraphicApiOGL::GetDefaultBackBuffer(){return nullptr;}

void CGraphicApiOGL::UnbindOGL(){

	glUseProgram(0);
}

///
/// U P D A T E´s
/// 

void CGraphicApiOGL::UpdateConstantBuffer(const void* _srcData , 
	CConstantBuffer& _updateDataCB ){

	auto UBO = reinterpret_cast<CConstantBufferOGL&>(_updateDataCB);

	glBindBuffer(GL_UNIFORM_BUFFER, *UBO.m_uniformBufferObject);

	GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);

	memcpy(p, &UBO.m_bufferSize, sizeof(UBO.m_bufferSize));

	glUnmapBuffer(GL_UNIFORM_BUFFER);

	unsigned int block_index; 
	block_index = glGetUniformBlockIndex(*UBO.m_uniformBufferObject, "Shader data");

	glBindBufferBase(GL_UNIFORM_BUFFER, 0, *UBO.m_uniformBufferObject);

	glUniformBlockBinding(*UBO.m_uniformBufferObject, block_index, 0);
}

///
/// C L E A R´s
/// 

CTexture* CGraphicApiOGL::ClearYourRenderTargetView(CTexture* _renderTarget ){


	return nullptr;
}

CTexture* CGraphicApiOGL::ClearYourDepthStencilView(CTexture* _depthStencil ){


	return nullptr;
}

void CGraphicApiOGL::CleanUpDevices(){}

///
/// C R E A T E´s 
///

CShaders* CGraphicApiOGL::CreateVertexAndPixelShader(const std::wstring& _nameVS, 
	const std::string& _entryPointVS,
	const std::string& _vertexSrc, const std::wstring& _namePS, 
	const std::string& _entryPointPS, const std::string& _fragmentSrc){

	///Generamos el tipo de dato para ir guardando
	/// los datos necesarios y entregarlo al usuario
	auto shaders = new CShadersOGL();

	// Create an empty vertex shader handle
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Send the vertex shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	const GLchar* source = (const GLchar*)_vertexSrc.c_str();
	glShaderSource(vertexShader, 1, &source, 0);

	// Compile the vertex shader
	glCompileShader(vertexShader);

	GLint isCompiled = 0;

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE){

		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(vertexShader);

		return nullptr;
	}

	shaders->m_vertexShader = &vertexShader;

	// Create an empty fragment shader handle
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Send the fragment shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	source = (const GLchar*)_fragmentSrc.c_str();
	glShaderSource(fragmentShader, 1, &source, 0);

	// Compile the fragment shader
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_FALSE){

		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(fragmentShader);
		// Either of them. Don't leak shaders.
		glDeleteShader(vertexShader);

		return nullptr;
	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	shaders->m_rendererID = glCreateProgram();
	GLuint program = shaders->m_rendererID;

	// Attach our shaders to our program
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	// Link our program
	glLinkProgram(program);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);

	if (isLinked == GL_FALSE){

		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(program);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return nullptr;
	}

	shaders->m_fragmentShader = &fragmentShader;

	// Always detach shaders after a successful link.
	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);

	return shaders;
}

CVertexBuffer* CGraphicApiOGL::CreateVertexBuffer(const std::vector<SimpleVertex>& _simpleVertex, 
	unsigned int _vertexBufferObject){

	auto VBO = new CVertexBufferOGL();
	VBO->m_vertexBufferObject = &_vertexBufferObject;

	///Creamos objetos de búfer y devolvemos los identificadores de los objetos de búfer
	glGenBuffers(1, VBO->m_vertexBufferObject);

	///Enlazamos VBO para la matriz de vértices
	glBindBuffer(GL_ARRAY_BUFFER, *VBO->m_vertexBufferObject);

	///Copiamos los datos en el objeto de búfer
	glBufferData(GL_ARRAY_BUFFER, sizeof(_simpleVertex), &_simpleVertex, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return VBO;
}

CIndexBuffer* CGraphicApiOGL::CreateIndexBuffer(const std::vector<uint32_t>& _simpleIndex, 
	unsigned int _indexBufferObject){

	auto PBO = new CIndexBufferOGL();

	PBO->m_indexBufferObject = &_indexBufferObject;

	///Creamos objetos de búfer y devolvemos los identificadores de los objetos de búfer
	glGenBuffers(1, PBO->m_indexBufferObject);

	///Enlazamos VBO para la matriz de vértices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *PBO->m_indexBufferObject);

	///Copiamos los datos en el objeto de búfer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_simpleIndex), &_simpleIndex, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return PBO;
}

CConstantBuffer* CGraphicApiOGL::CreateConstantBuffer(const unsigned int _bufferSize ){

	auto UBO = new CConstantBufferOGL();
	UBO->m_bufferSize = &_bufferSize;
	
	///Generamos el buffer y lo inicializamos
	glGenBuffers(1, UBO->m_uniformBufferObject);
	glBindBuffer(GL_UNIFORM_BUFFER, *UBO->m_uniformBufferObject);
	glBufferData(GL_UNIFORM_BUFFER, *UBO->m_bufferSize, &UBO->m_bufferSize, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	return UBO;
}

CTexture* CGraphicApiOGL::CreateTexture(const unsigned int _width , 
	const unsigned int _height , const unsigned int _bindFlags , 
	TEXTURE_FORMAT _textureFormat ,
	const std::string _fileName){

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

	unsigned char* data = stbi_load(_fileName.c_str(), &width, &height, &nrChannels, 0);

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

CInputLayout* CGraphicApiOGL::CreateInputLayout(CShaders& _vertexShader ){


	return nullptr;
}

///
/// S E T´s 
///

void CGraphicApiOGL::SetPixelShader(CShaders& _pixelShader ){

	auto shader = reinterpret_cast<CShadersOGL&>(_pixelShader);

	glUseProgram(shader.m_rendererID);
}

void CGraphicApiOGL::SetVertexShader(CShaders& _vertexShader ){

	auto shader = reinterpret_cast<CShadersOGL&>(_vertexShader);

	glUseProgram(shader.m_rendererID);
}

void CGraphicApiOGL::SetVertexBuffer(CVertexBuffer& _vertexBuffer ){


}

void CGraphicApiOGL::SetIndexBuffer(CIndexBuffer& _indexBuffer ){


}

void CGraphicApiOGL::SetConstantBuffer(CConstantBuffer& _constantBuffer , 
	const unsigned int _startSlot , const unsigned int _numBuffers ){


}

void CGraphicApiOGL::SetSamplerState(const unsigned int _startSlot , 
	std::vector<CSamplerState*>& _samplerState ){


}

void CGraphicApiOGL::SetShaderResourceView(std::vector<CTexture*>& _shaderResourceView , 
	const unsigned int _startSlot , const unsigned int _numViews ){


}

void CGraphicApiOGL::SetRenderTarget(CTexture& _renderTarget , 
	CTexture& _depthStencil ){


}

void CGraphicApiOGL::SetDepthStencil(CTexture& _depthStencil , 
	const unsigned int _stencilRef ){


}

void CGraphicApiOGL::SetInputLayout(CInputLayout& _vertexLayout ){


}

void CGraphicApiOGL::SetViewport(const unsigned int _numViewports , 
	const unsigned int _width , const unsigned int _heigth ){

	glViewport(0, 0, _width, _heigth);
}

void CGraphicApiOGL::SetPrimitiveTopology(const unsigned int _topology ){


}

void CGraphicApiOGL::SetYourVS(CShaders& _vertexShader ){


}

void CGraphicApiOGL::SetYourVSConstantBuffers(CConstantBuffer* _constantBuffer , 
	const unsigned int _startSlot , const unsigned int _numBuffers ){


}

void CGraphicApiOGL::SetYourPS(CShaders& _pixelShader ){


}

void CGraphicApiOGL::SetYourPSConstantBuffers(CConstantBuffer* _constantBuffer , 
	const unsigned int _startSlot , const unsigned int _numBuffers ){


}

void CGraphicApiOGL::SetYourPSSampler(CSamplerState& _sampler , 
	const unsigned int _startSlot , const unsigned int _numSamplers ){


}