#pragma once
#include <Windows.h>

#include "glm\glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "CConstantBufferDX.h"


/// <summary>
/// Estructura con los datos
/// para la creación de una camara
/// </summary>
struct CameraDescriptor {

    float s_width;
    float s_height;
    float s_near;
    float s_far;
    float s_foV;

    glm::vec3 s_eye;
    glm::vec3 s_lookAt;
    glm::vec3 s_up;
};

class CCamera{

    private:
        ///
        /// Miembros
        /// 

        bool m_clickPressed = false;

        float m_angule;
        float m_maxAngule = 2160.0f;

        glm::vec2 m_originalMousePos;

        glm::vec3 m_up;
        glm::vec3 m_front;
        glm::vec3 m_locketFront;
        glm::vec3 m_onlyXnY;
        glm::vec3 m_locketonlyXnY;
        glm::vec3 m_right;

        glm::mat4x4 m_projection;
        glm::mat4x4 m_position;
        glm::mat4x4 m_axis;
        glm::mat4x4 m_view;

        CameraDescriptor m_cameraDesc;

    public:
        ///
        ///Métodos 
        ///
        
        ///Constructor
        CCamera() = default;
        ///
        ~CCamera() = default;

        void Init(CameraDescriptor _cameraDesc);

        void UpdateViewMatrix();

        void InputDetection(WPARAM _param);

        void PitchX(WPARAM _param);

        void RollY(WPARAM _param);

        void YawZ(WPARAM _param);

        void Move(WPARAM _param);

        void MouseRotation();

        ///
        /// C R E A T E´s
        /// 

        void CreateView();

        void CreateProjectionMatrix();

        ///
        /// S E T´s
        /// 

        void SetWidht(float _width);

        void SetHeight(float _height);

        void SetNear(float _near);

        void SetFar(float _far);

        void SetFoV(float _foV);

        void SetEye(glm::vec3 _vec3);

        void SetLookAt(glm::vec3 _vec3);

        void SetUp(glm::vec3 _vec3);

        void SetOriginalMousePos(float _x, 
            float _y);

        void SetClickPressed(bool _bool);

        ///
        /// G E T´s
        /// 
        
        glm::mat4x4 GetView();

        glm::mat4x4 GetProjection();

        glm::vec2 GetOriginalMousePos();

        bool GetClickPressed();
};