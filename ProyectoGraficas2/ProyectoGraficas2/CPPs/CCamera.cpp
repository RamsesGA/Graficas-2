#include "..\Includes\CCamera.h"
#include "..\Includes\CConstantBufferDX.h"

void CCamera::Init(CameraDescriptor _cameraDesc){

	SetWidht(_cameraDesc.s_width);
	SetHeight(_cameraDesc.s_height);
	SetNear(_cameraDesc.s_near);
	SetFar(_cameraDesc.s_far);
	SetFoV(_cameraDesc.s_foV);
	SetEye(_cameraDesc.s_eye);
	SetLookAt(_cameraDesc.s_lookAt);
	SetUp(_cameraDesc.s_up);

	CreateView();
	CreateProjectionMatrix();
	UpdateViewMatrix();
}

void CCamera::UpdateViewMatrix(){

	m_right.x = m_view[0].x;
	m_right.y = m_view[0].y;
	m_right.z = m_view[0].z;

	m_up.x = m_view[1].x;
	m_up.y = m_view[1].y;
	m_up.z = m_view[1].z;

	m_front.x = m_view[2].x;
	m_front.y = m_view[2].y;
	m_front.z = m_view[2].z;

	m_cameraDesc.s_lookAt = m_cameraDesc.s_eye + m_front;
}

void CCamera::InputDetection(WPARAM _param){

	if (_param == VK_UP || _param == VK_DOWN) {

		PitchX(_param);
	}
	if (_param == VK_RIGHT || _param == VK_LEFT) {

		RollY(_param);
	}
	if (_param == 'z' || _param == 'Z' || _param == 'c' || _param == 'C') {

		YawZ(_param);
	}
	else {

		Move(_param);
	}
}

void CCamera::PitchX(WPARAM _param){

	glm::mat4x4 rotation;
	float speedrot = 0.10f;

	if (VK_UP == _param) {

		rotation =
		{
			1,	0,				0,					0,
			0,	cosf(speedrot),	-sinf(speedrot),	0,
			0,	sinf(speedrot),	cosf(speedrot),		0,
			0,	0,				0,					1
		};
	}
	else if (VK_DOWN == _param) {

		rotation =
		{
			1,	0,					0,					0,
			0,	cosf(-speedrot),	-sinf(-speedrot),	0,
			0,	sinf(-speedrot),	cosf(-speedrot),	0,
			0,	0,					0,					1
		};
	}

	m_view *= rotation;

	UpdateViewMatrix();
}

void CCamera::RollY(WPARAM _param){

	glm::mat4x4 rotation;
	float speedrot = 0.10f;

	if (VK_RIGHT == _param) {

		rotation =
		{
			cosf(speedrot),	-sinf(speedrot),	0,	0,
			sinf(speedrot),	cosf(speedrot),		0,	0,
			0,				0,					1,	0,
			0,				0,					0,	1
		};
	}
	else if (VK_LEFT == _param) {

		rotation =
		{
			cosf(-speedrot),	-sinf(-speedrot),		0,		0,
			sinf(-speedrot),	cosf(-speedrot),		0,		0,
			0,				0,							1,		0,
			0,				0,							0,		1
		};
	}

	m_view *= rotation;

	UpdateViewMatrix();
}

void CCamera::YawZ(WPARAM _param){

	glm::mat4x4 rotation;
	float speedrot = 0.10f;

	if ('z' == _param || 
		'Z' == _param) {

		rotation =
		{
			cosf(speedrot),		0,	sinf(speedrot),	0,
			0,					1,	0,				0,
			-sinf(speedrot),	0,	cosf(speedrot),	0,
			0,					0,	0,				1
		};
	}
	else if ('c' == _param || 
			'C' == _param) {

			rotation =
			{
				cosf(-speedrot),		0,	sinf(-speedrot),	0,
				0,						1,	0,					0,
				-sinf(-speedrot),		0,	cosf(-speedrot),	0,
				0,						0,	0,					1
			};
	}

	m_view *= rotation;

	UpdateViewMatrix();
}

void CCamera::Move(WPARAM _param){

	if (_param == 'w' || 
		'W' == _param) {

		m_cameraDesc.s_eye += m_front;
	}
	else if (_param == 's' || 
			'S' == _param) {

			m_cameraDesc.s_eye -= m_front;
	}
	else if (_param == 'a' || 
			'A' == _param) {

			m_cameraDesc.s_eye -= m_right;
	}
	else if (_param == 'd' || 
			'D' == _param) {

			m_cameraDesc.s_eye += m_right;
	}
	else if (_param == 'q' ||
			'Q' == _param) {

			m_cameraDesc.s_eye += m_up;
	}
	else if (_param == 'e' || 
			'E' == _param) {

			m_cameraDesc.s_eye -= m_up;
	}

	m_axis =
	{
		m_right.x,	m_right.y,	m_right.z,	0,
		m_up.x,		m_up.y,		m_up.z,		0,
		m_front.x,	m_front.y,	m_front.z,	0,
		0,			0,			0,			1
	};

	m_position =
	{
		1,	0,	0, -m_cameraDesc.s_eye.x,
		0,	1,	0, -m_cameraDesc.s_eye.y,
		0,	0,	1, -m_cameraDesc.s_eye.z,
		0,	0,	0,	1
	};


	m_position *= m_axis;

	m_view = m_position;

	UpdateViewMatrix();
}

void CCamera::MouseRotation(){

	glm::vec2 firstPos;
	glm::vec2 secondPos;

	float speedRot = 0.020f;
	float speedAngule = 1.0f;

	glm::mat4x4 Yaw =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	glm::mat4x4 Pitch =
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	POINT Temp;
	GetCursorPos(&Temp);

	firstPos.x = Temp.x;
	secondPos.y = Temp.y;

	if (firstPos.x < m_originalMousePos.x) {

		m_cameraDesc.s_lookAt -= m_right * speedRot;
		m_cameraDesc.s_up = m_up;

		CreateView();
	}

	if (firstPos.x > m_originalMousePos.x) {

		m_cameraDesc.s_lookAt += m_right * speedRot;
		m_cameraDesc.s_up = m_up;
		CreateView();
	}

	if (secondPos.y < m_originalMousePos.y && m_angule < m_maxAngule) {

		m_angule += speedAngule;

		if (m_angule > m_maxAngule) {

			m_angule = m_maxAngule;
		}
		else {

			Pitch =
			{
				1,	0,									0,										0,
				0,	cosf(speedAngule * 3.141516 / 180),	-sinf(speedAngule * 3.141516 / 180),	0,
				0,	sinf(speedAngule * 3.141516 / 180),	cosf(speedAngule * 3.141516 / 180),		0,
				0,	0,									0,										1
			};
		}

	}

	if (secondPos.y > m_originalMousePos.y && m_angule > -m_maxAngule) {

		m_angule -= speedAngule;

		if (m_angule < -m_maxAngule) {

			m_angule = -m_maxAngule;
		}
		else {

			Pitch =
			{
				1,	0,										0,										0,
				0,	cosf(-speedAngule * 3.141516 / 180),	-sinf(-speedAngule * 3.141516 / 180),	0,
				0,	sinf(-speedAngule * 3.141516 / 180),	cosf(-speedAngule * 3.141516 / 180),	0,
				0,	0,										0,										1
			};
		}

	}

	SetCursorPos(m_originalMousePos.x, m_originalMousePos.y);
	m_view *= Yaw;
	UpdateViewMatrix();

	m_view *= Pitch;
	UpdateViewMatrix();
}

///
/// C R E A T E´s
/// 

void CCamera::CreateView(){

	//Usamos left hand
	m_front = m_cameraDesc.s_lookAt - m_cameraDesc.s_eye;
	m_front = glm::normalize(m_front);

	m_right = glm::cross(m_cameraDesc.s_up, m_front);
	m_right = { m_right.x, 0, m_right.z };
	m_right = glm::normalize(m_right);

	m_up = glm::cross(m_front, m_right);
	m_up = glm::normalize(m_up);

	m_axis =
	{
		m_right.x,	m_right.y,	m_right.z,	0,
		m_up.x,		m_up.y,		m_up.z,		0,
		m_front.x,	m_front.y,	m_front.z,	0,
		0,			0,			0,			1
	};

	m_position =
	{
		1,	0,	0, -m_cameraDesc.s_eye.x,
		0,	1,	0, -m_cameraDesc.s_eye.y,
		0,	0,	1, -m_cameraDesc.s_eye.z,
		0,	0,	0,	1
	};

	m_position *= m_axis;
	m_view = m_position;
}

void CCamera::CreateProjectionMatrix(){

	m_projection = glm::perspectiveFovLH(m_cameraDesc.s_foV, m_cameraDesc.s_width,
		m_cameraDesc.s_height, m_cameraDesc.s_near, m_cameraDesc.s_far);
}

void CCamera::SetWidht(float _width){

	m_cameraDesc.s_width = _width;
}

void CCamera::SetHeight(float _height){

	m_cameraDesc.s_height = _height;
}

void CCamera::SetNear(float _near){

	m_cameraDesc.s_near = _near;
}

void CCamera::SetFar(float _far){

	m_cameraDesc.s_far = _far;
}

void CCamera::SetFoV(float _foV){

	m_cameraDesc.s_foV = _foV;
}

void CCamera::SetEye(glm::vec3 _vec3){

	m_cameraDesc.s_eye = _vec3;
}

void CCamera::SetLookAt(glm::vec3 _vec3){

	m_cameraDesc.s_lookAt = _vec3;
}

void CCamera::SetUp(glm::vec3 _vec3){

	m_cameraDesc.s_up = _vec3;
}

///
/// S E T´s
/// 

void CCamera::SetOriginalMousePos(float _x, float _y){

	m_originalMousePos = { _x, _y };
}

void CCamera::SetClickPressed(bool _bool){

	m_clickPressed = _bool;
}

///
/// G E T´s
/// 

glm::mat4x4 CCamera::GetView() {

	return m_view;
}

glm::mat4x4 CCamera::GetProjection(){

	return m_projection;
}

glm::vec2 CCamera::GetOriginalMousePos(){

	return m_originalMousePos;
}

bool CCamera::GetClickPressed(){

	return m_clickPressed;
}
