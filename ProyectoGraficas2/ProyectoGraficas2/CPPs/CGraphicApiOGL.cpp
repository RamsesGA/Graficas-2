#include "..\Includes\CGraphicApiOGL.h"
#include "..\Includes\CTextureOGL.h"
#include "..\Includes\CSamplerStateOGL.h"
#include "..\Includes\CConstantBufferOGL.h"
#include "..\Includes\CShadersOGL.h"
#include "..\Includes\CVertexBufferOGL.h"
#include "..\Includes\CIndexBufferOGL.h"
#include "..\Includes\CInputLayoutOGL.h"
#include "..\Includes\stb_image.h"

#include <iostream>
#include <fstream>
#include <sstream>

/// <summary>
/// Función propia de OpenGL para la lectura
/// del shader
/// </summary>
/// <returns></returns>
std::string ReadShaderOGL(const std::wstring& _nameVS) {

	std::ifstream shaderFile;

	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {

		shaderFile.open(_nameVS);
		
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();

		shaderFile.close();

		return shaderStream.str();
	}
	catch(std::ifstream::failure e){

		std::cout << "ERROR, no se pudo leer el shader\n";
		return "";
	}
}

bool AnalyzeVertexShaderOGL(const std::wstring& _nameVS) {

	std::string bufferAnalyze;

	for (unsigned int i = 0; i < _nameVS.size(); i++) {

		bufferAnalyze += _nameVS[i];

		if (('_' == bufferAnalyze[i]) &&
			("OGL_" != bufferAnalyze)) {

			return false;
		}
		else if (('_' == bufferAnalyze[i]) &&
				("OGL_" == bufferAnalyze)) {

				return true;
		}
	}

	return false;
}

bool AnalyzePixelShaderOGL(const std::wstring& _namePS) {

	std::string bufferAnalyze;

	for (unsigned int i = 0; i < _namePS.size(); i++) {

		bufferAnalyze += _namePS[i];

		if (('_' == bufferAnalyze[i]) &&
			("OGL_" != bufferAnalyze)) {

			return false;
		}
		else if (('_' == bufferAnalyze[i]) &&
				("OGL_" == bufferAnalyze)) {

				return true;
		}
	}

	return false;
}

/// 
/// D E S T R U C T O R
/// 

CGraphicApiOGL::~CGraphicApiOGL(){

	// delete the rendering context  
	wglDeleteContext(m_renderingContext);
}

///
/// H E R E N C I A
///

bool CGraphicApiOGL::InitDevice(HWND _hWnd){

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

	m_hWnd = _hWnd;

	m_HandleToDC = GetDC(_hWnd);

	int pixelFormat = ChoosePixelFormat(m_HandleToDC, &pfd);

	SetPixelFormat(m_HandleToDC, pixelFormat, &pfd);

	m_renderingContext = wglCreateContext(m_HandleToDC);

	wglMakeCurrent(m_HandleToDC, m_renderingContext);

	if (!gladLoadGL()){

		return false;
	}

	RECT rc;

	GetClientRect(_hWnd, &rc);

	m_width = rc.right - rc.left;
	m_height = rc.bottom - rc.top;

	SetViewport(1, m_width, m_height);

	glEnable(GL_DEPTH_TEST);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	GLuint detectError = glGetError();

	if (detectError != 0) {

		exit(1);
	}

	return true;
}

void CGraphicApiOGL::DrawIndex(unsigned int _indexCount , 
	unsigned int _startIndexLocation , 
	unsigned int _baseVertexLocation ){

	glDrawElements(m_topology, _indexCount,
		GL_UNSIGNED_INT, 0);

	GLuint detectError = glGetError();

	if (detectError != 0) {

		exit(1);
	}
}

void CGraphicApiOGL::SwapChainPresent(unsigned int _syncInterval,
	unsigned int _flags) {

	SwapBuffers(m_HandleToDC);
}

CTexture* CGraphicApiOGL::LoadTextureFromFile(std::string _srcFile){

	int width;
	int height; 
	int components;

	unsigned char* data = stbi_load(_srcFile.c_str(), 
		&width, &height, &components, 0);

	if (!data) {

		return nullptr;
		stbi_image_free(data);
	}
	else{

		GLenum format = GL_ZERO;

		if (1 == components){

			format = GL_RED;
		}
		else if (2 == components){

			format = GL_RG;
		}
		else if (3 == components){

			format = GL_RGB;
		}
		else if (4 == components){

			format = GL_RGBA;
		}

		auto* texture = new CTextureOGL();

		glGenTextures(1, &texture->m_texture);
		glBindTexture(GL_TEXTURE_2D, texture->m_texture);
		glTexImage2D(GL_TEXTURE_2D,
			0,
			format,
			width,
			height,
			0,
			format,
			GL_UNSIGNED_BYTE,
			data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(data);

		return texture;
	}
}

CTexture* CGraphicApiOGL::GetDefaultBackBuffer(){return nullptr;}

CTexture* CGraphicApiOGL::GetDefaultDepthStencil(){return nullptr;}

void CGraphicApiOGL::UnbindOGL(){

	glUseProgram(0);
}

///
/// U P D A T E´s
/// 

///Siempre que pida un puntero de información, debo pedir el tamaño de esa información
void CGraphicApiOGL::UpdateConstantBuffer(const void* _srcData , 
	CConstantBuffer& _updateDataCB ){

	auto& UBO = reinterpret_cast<CConstantBufferOGL&>(_updateDataCB);

	glBindBuffer(GL_UNIFORM_BUFFER, UBO.m_uniformBufferObject);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, UBO.m_bufferSize, _srcData);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	
	GLuint detectError = glGetError();

	if (detectError != 0) {

		exit(1);
	}
}

///
/// C L E A R´s
/// 

///TODO: Pedir de parámetro el color
void CGraphicApiOGL::ClearYourRenderTargetView(CTexture* _renderTarget ){
	
	glClearColor(0.0f, 0.125f,
		0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	GLuint detectError = glGetError();

	if (detectError != 0) {

		exit(1);
	}
}

void CGraphicApiOGL::ClearYourDepthStencilView(CTexture* _depthStencil ){

	glClear(GL_DEPTH_BUFFER_BIT);

	GLuint detectError = glGetError();

	if (detectError != 0) {

		exit(1);
	}
}

///
/// C R E A T E´s 
///

///Tener en cuenta la abstracción de PROGRAM
///Y tener separado vertex / pixel shaders
/// Cambiar el nombre de la fuinción a CreateShadersProgram
CShaders* CGraphicApiOGL::CreateVertexAndPixelShader(const std::wstring& _nameVS,
	const std::string& _entryPointVS, const std::wstring& _namePS, 
	const std::string& _entryPointPS){

	if (!(AnalyzeVertexShaderOGL(_nameVS))) {

		return nullptr;
	}
	if (!(AnalyzePixelShaderOGL(_namePS))) {

		return nullptr;
	}

	std::string VS_ShaderSrc = ReadShaderOGL(_nameVS);
	std::string PS_ShaderSrc = ReadShaderOGL(_namePS);

	///Generamos el tipo de dato para ir guardando
	/// los datos necesarios y entregarlo al usuario
	auto* shaders = new CShadersOGL();

	// Create an empty vertex shader handle
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Send the vertex shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	const GLchar* source = (const GLchar*)VS_ShaderSrc.c_str();
	glShaderSource(vertexShader, 1, &source, nullptr);

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
		delete shaders;

		return nullptr;
	}

	shaders->m_vertexShader = vertexShader;

	// Create an empty fragment shader handle
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Send the fragment shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	source = (const GLchar*)PS_ShaderSrc.c_str();
	glShaderSource(fragmentShader, 1, &source, nullptr);

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
		delete shaders;

		return nullptr;
	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	shaders->m_rendererID = glCreateProgram();

	// Attach our shaders to our program
	glAttachShader(shaders->m_rendererID, vertexShader);
	glAttachShader(shaders->m_rendererID, fragmentShader);

	// Link our program
	glLinkProgram(shaders->m_rendererID);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(shaders->m_rendererID, GL_LINK_STATUS, (int*)&isLinked);

	if (isLinked == GL_FALSE){

		GLint maxLength = 0;
		glGetProgramiv(shaders->m_rendererID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(shaders->m_rendererID, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(shaders->m_rendererID);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		delete shaders;

		return nullptr;
	}

	shaders->m_fragmentShader = fragmentShader;

	// Always detach shaders after a successful link.
	glDetachShader(shaders->m_rendererID, vertexShader);
	glDetachShader(shaders->m_rendererID, fragmentShader);

	return shaders;
}

CVertexBuffer* CGraphicApiOGL::CreateVertexBuffer(const void* _data,
	const unsigned int _size){

	auto* VBO = new CVertexBufferOGL();

	///Guardamos el tamaño del buffer
	VBO->m_vertexBufferSize = _size;

	///Creamos objetos de búfer y devolvemos los identificadores de los objetos de búfer
	glGenBuffers(1, &VBO->m_vertexBufferObject);

	///Enlazamos VBO para la matriz de vértices
	glBindBuffer(GL_ARRAY_BUFFER, VBO->m_vertexBufferObject);

	///Copiamos los datos en el objeto de búfer
	glBufferData(GL_ARRAY_BUFFER, 
		VBO->m_vertexBufferSize,
		_data, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLuint detectError = glGetError();

	if (detectError != 0) {

		delete VBO;
		exit(1);
	}

	return VBO;
}

CIndexBuffer* CGraphicApiOGL::CreateIndexBuffer(const void* _data,
	const unsigned int _size){

	auto* EBO = new CIndexBufferOGL();

	EBO->m_indexBufferSize = _size;

	///Creamos objetos de búfer y devolvemos los identificadores de los objetos de búfer
	glGenBuffers(1, &EBO->m_indexBufferObject);

	///Enlazamos el EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO->m_indexBufferObject);

	///Copiamos los datos en el objeto de búfer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 
		EBO->m_indexBufferSize, _data,
		GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	GLuint detectError = glGetError();

	if (detectError != 0) {

		delete EBO;
		exit(1);
	}

	return EBO;
}

CConstantBuffer* CGraphicApiOGL::CreateConstantBuffer(const unsigned int _bufferSize){

	auto* UBO = new CConstantBufferOGL();
	
	///Generamos el buffer y lo inicializamos
	glGenBuffers(1, &UBO->m_uniformBufferObject);
	glBindBuffer(GL_UNIFORM_BUFFER, UBO->m_uniformBufferObject);
	glBufferData(GL_UNIFORM_BUFFER, _bufferSize, nullptr, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	
	UBO->m_bufferSize = _bufferSize;

	GLuint detectError = glGetError();

	if (detectError != 0) {

		delete UBO;
		exit(1);
	}

	return UBO;
}

CTexture* CGraphicApiOGL::CreateTexture(const unsigned int _width , 
	const unsigned int _height , const unsigned int _bindFlags , 
	TEXTURE_FORMAT _textureFormat ,
	const std::string _fileName){

	auto* tex = new CTextureOGL();

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

	unsigned char* data = stbi_load(_fileName.c_str(), &width, &height, &nrChannels, 4);

	if (data){

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		tex->m_texture = texture;
		tex->m_data = *data;
	}
	else{

		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	GLuint detectError = glGetError();

	if (detectError != 0) {

		delete tex;
		exit(1);
	}

	return tex;
}

CSamplerState* CGraphicApiOGL::CreateSamplerState() {

	auto* samplerState = new CSamplerStateOGL();

	glGenSamplers(1, &samplerState->m_samplerState);
	glSamplerParameteri(samplerState->m_samplerState, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glSamplerParameteri(samplerState->m_samplerState, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glSamplerParameteri(samplerState->m_samplerState, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(samplerState->m_samplerState, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	GLuint detectError = glGetError();

	if (detectError != 0) {

		delete samplerState;
		exit(1);
	}

	return samplerState;
}

CInputLayout* CGraphicApiOGL::CreateInputLayout(CShaders& _vertexShader){
	
	auto* inputLayout = new CInputLayoutOGL();
	auto& shader = reinterpret_cast<CShadersOGL&>(_vertexShader);

	///Creamos el vertex array
	glGenVertexArrays(1, &inputLayout->m_inputLayout);
	///Ahora indicamos a OGL que lo vamos a usar
	glBindVertexArray(inputLayout->m_inputLayout);

	bool firstOffSet = true;
	unsigned int offSet = 0;
	unsigned int sizeComponent = 0;
	int total = -1;

	glGetProgramiv(shader.m_rendererID, GL_ACTIVE_ATTRIBUTES, &total);

	for (unsigned int i = 0; i < total; i++) {
		
		char name[100];
		memset(name, ' ', 100);

		int num = -1;
		int name_len = -1;

		GLenum type = GL_ZERO;

		glGetActiveAttrib(shader.m_rendererID, GLuint(i), 
			sizeof(name) - 1, &name_len, &num, 
			&type, name);

		name[name_len] = 0;

		GLuint location = glGetAttribLocation(shader.m_rendererID, name);

		///Switch para obtener el tamaño del componente
		/// y asignar su offset correspondiente
		switch (type){

			case GL_FLOAT_VEC2:

				sizeComponent = 2;
				if (!firstOffSet) {

					offSet += 8;
				}
				break;

			case GL_FLOAT_VEC3:

				sizeComponent = 3;
				if (!firstOffSet) {

					offSet += 12;
				}
				break;

			case GL_FLOAT_VEC4:

				sizeComponent = 4;
				if (!firstOffSet) {

					offSet += 16;
				}
				break;
		}
		
		glVertexAttribFormat(location, sizeComponent,
			GL_FLOAT, false, offSet);

		GLuint detectError = glGetError();

		if (detectError != 0) {

			delete inputLayout;
			exit(1);
		}

		glVertexAttribBinding(location, 0);
		glEnableVertexAttribArray(location);
	}

	GLuint detectError = glGetError();

	if (detectError != 0) {

		delete inputLayout;
		exit(1);
	}

	return inputLayout;
}

///
/// S E T´s 
///

void CGraphicApiOGL::SetPixelShader(CShaders& _pixelShader ){

	auto& shader = reinterpret_cast<CShadersOGL&>(_pixelShader);

	glUseProgram(shader.m_rendererID);

	GLuint detectError = glGetError();

	if (detectError != 0) {

		exit(1);
	}
}

void CGraphicApiOGL::SetVertexShader(CShaders& _vertexShader ){

	auto& shader = reinterpret_cast<CShadersOGL&>(_vertexShader);

	glUseProgram(shader.m_rendererID);

	GLuint detectError = glGetError();

	if (detectError != 0) {

		exit(1);
	}
}

void CGraphicApiOGL::SetVertexBuffer(CVertexBuffer& _vertexBuffer) {

	auto& vertex = reinterpret_cast<CVertexBufferOGL&>(_vertexBuffer);

	glBindVertexBuffer(0, vertex.m_vertexBufferObject, 0, sizeof(Vertex));

	GLuint detectError = glGetError();

	if (detectError != 0) {

		exit(1);
	}
}

void CGraphicApiOGL::SetIndexBuffer(CIndexBuffer& _indexBuffer){

	auto& index = reinterpret_cast<CIndexBufferOGL&>(_indexBuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index.m_indexBufferObject);

	GLuint detectError = glGetError();

	if (detectError != 0) {

		exit(1);
	}
}

void CGraphicApiOGL::SetConstantBuffer(bool _isVertex,
	CConstantBuffer& _constantBuffer,
	const unsigned int _startSlot,
	const unsigned int _numBuffers){

	auto& constantBuffer = reinterpret_cast<CConstantBufferOGL&>(_constantBuffer);

	glBindBuffer(GL_UNIFORM_BUFFER, constantBuffer.m_uniformBufferObject);

	GLuint detectError = glGetError();

	if (detectError != 0) {

		exit(1);
	}
}

void CGraphicApiOGL::SetSamplerState(const unsigned int _startSlot , 
	std::vector<CSamplerState*>& _samplerState,
	CTexture& _texture){

	auto& sampler = reinterpret_cast<CSamplerStateOGL&>(_samplerState);
	auto& texture = reinterpret_cast<CTextureOGL&>(_texture);

	glBindSampler(texture.m_texture, sampler.m_samplerState);

	GLuint detectError = glGetError();

	if (detectError != 0) {

		exit(1);
	}
}

void CGraphicApiOGL::SetShaderResourceView(CTexture* _shaderResourceView,
	const unsigned int _startSlot, const unsigned int _numViews) {

	auto* resourceView = reinterpret_cast<CTextureOGL*>(_shaderResourceView);
	
	glActiveTexture(GL_TEXTURE0 + _startSlot);

	glBindTexture(GL_TEXTURE_2D, resourceView->m_texture);

	GLuint detectError = glGetError();

	if (detectError != 0) {

		delete resourceView;
		exit(1);
	}
}

void CGraphicApiOGL::SetRenderTarget(CTexture* _renderTarget , 
	CTexture* _depthStencil ){

	if (nullptr != _renderTarget) {

		auto* renderTarget = reinterpret_cast<CTextureOGL*>(_renderTarget);
		auto* depthStencil = reinterpret_cast<CTextureOGL*>(_depthStencil);

		glBindFramebuffer(GL_FRAMEBUFFER, renderTarget->m_framebuffer);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH24_STENCIL8,
			GL_RENDERBUFFER, depthStencil->m_renderBufferObject);

		GLuint detectError = glGetError();

		if (detectError != 0) {

			exit(1);
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CGraphicApiOGL::SetDepthStencil(CTexture& _depthStencil , 
	const unsigned int _stencilRef ){}

void CGraphicApiOGL::SetInputLayout(CInputLayout& _vertexLayout ){

	auto& inputLayout = reinterpret_cast<CInputLayoutOGL&>(_vertexLayout);

	glBindVertexArray(inputLayout.m_inputLayout);

	GLuint detectError = glGetError();

	if (detectError != 0) {

		exit(1);
	}
}

void CGraphicApiOGL::SetViewport(const unsigned int _numViewports , 
	const unsigned int _width , const unsigned int _heigth ){

	glViewport(0, 0, _width, _heigth);

	GLuint detectError = glGetError();

	if (detectError != 0) {

		exit(1);
	}
}

void CGraphicApiOGL::SetPrimitiveTopology(const unsigned int _topology ){

	switch (_topology) {

		case PRIMITIVE_TOPOLOGY_POINTLIST:
			m_topology = GL_POINTS;
			break;

		case PRIMITIVE_TOPOLOGY_LINELIST:
			m_topology = GL_LINES;
			break;

		case PRIMITIVE_TOPOLOGY_LINESTRIP:
			m_topology = GL_LINE_STRIP;
			break;

		case PRIMITIVE_TOPOLOGY_TRIANGLELIST:
			m_topology = GL_TRIANGLES;
			break;

		case PRIMITIVE_TOPOLOGY_TRIANGLESTRIP:
			m_topology = GL_TRIANGLE_STRIP;
			break;
	}

	GLuint detectError = glGetError();

	if (detectError != 0) {

		exit(1);
	}
}

void CGraphicApiOGL::SetShaders(CShaders& _shaders){

	auto& shaders = reinterpret_cast<CShadersOGL&>(_shaders);

	glUseProgram(shaders.m_rendererID);

	GLuint detectError = glGetError();

	if (detectError != 0) {

		exit(1);
	}
}

void CGraphicApiOGL::SetYourVSConstantBuffers(CConstantBuffer* _constantBuffer , 
	const unsigned int _startSlot , const unsigned int _numBuffers ){

	auto* constantBuffer = reinterpret_cast<CConstantBufferOGL*>(_constantBuffer);

	glBindBufferBase(GL_UNIFORM_BUFFER, 
		_startSlot, 
		constantBuffer->m_uniformBufferObject);

	GLuint detectError = glGetError();

	if (detectError != 0) {

		delete constantBuffer;
		exit(1);
	}
}

void CGraphicApiOGL::SetYourPSConstantBuffers(CConstantBuffer* _constantBuffer , 
	const unsigned int _startSlot , const unsigned int _numBuffers ){

	auto* constantBuffer = reinterpret_cast<CConstantBufferOGL*>(_constantBuffer);

	glBindBufferBase(GL_UNIFORM_BUFFER,
		_startSlot,
		constantBuffer->m_uniformBufferObject);

	GLuint detectError = glGetError();

	if (detectError != 0) {

		delete constantBuffer;
		exit(1);
	}
}

void CGraphicApiOGL::SetYourPSSampler(CSamplerState& _sampler , 
	const unsigned int _startSlot , const unsigned int _numSamplers ){}


///
/// N O
/// T O C A R
/// 

void CGraphicApiOGL::SetYourVS(CShaders& _vertexShader) {}

void CGraphicApiOGL::SetYourPS(CShaders& _pixelShader) {}