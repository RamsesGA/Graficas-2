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

        /// <summary>
        /// Miembro para detectar y notificar
        /// si el usuario hizo click
        /// </summary>
        bool m_clickPressed = false;
        /// <summary>
        /// Miembro para detectar si es OGL
        /// o DX
        /// </summary>
        bool m_isOGL;
        /// <summary>
        /// Miembro para guardar el ángulo
        /// </summary>
        float m_angule;
        /// <summary>
        /// Miembro para definir un ángulo máximo
        /// que puede girar el usuario
        /// </summary>
        float m_maxAngule = 2160.0f;
        /// <summary>
        /// Miembro para guardar la posición
        /// original del mouse
        /// </summary>
        glm::vec2 m_originalMousePos;
        /// <summary>
        /// Miembro para guardar los vectores
        /// de arriba
        /// </summary>
        glm::vec3 m_up;
        /// <summary>
        /// Miembro para guardar los vectores
        /// del frente
        /// </summary>
        glm::vec3 m_front;
        /// <summary>
        /// Miembro para guardar los vectores
        /// </summary>
        glm::vec3 m_locketFront;
        /// <summary>
        /// Miembro para guardar los vectores
        /// en movimiento X Y
        /// </summary>
        glm::vec3 m_onlyXnY;
        /// <summary>
        /// Miembro para guardar los vectores
        /// de X Y y lockear la cámara
        /// </summary>
        glm::vec3 m_locketonlyXnY;
        /// <summary>
        /// Miembro para guardar los vectores
        /// de la posición derecha
        /// </summary>
        glm::vec3 m_right;
        /// <summary>
        /// Miembro para almacenar una matríz
        /// de proyección
        /// </summary>
        glm::mat4x4 m_projection;
        /// <summary>
        /// Miembro para almacenar una matríz
        /// de posición
        /// </summary>
        glm::mat4x4 m_position;
        /// <summary>
        /// Miembro para almacenar una matríz
        /// de eje
        /// </summary>
        glm::mat4x4 m_axis;
        /// <summary>
        /// Miembro para almacenar una matríz
        /// de vista
        /// </summary>
        glm::mat4x4 m_view;
        /// <summary>
        /// Miembro para conectarse a la
        /// estructura y definir sus valores
        /// </summary>
        CameraDescriptor m_cameraDesc;

    public:
        ///
        ///Métodos 
        ///
        
        ///Constructor
        CCamera() = default;
        ///
        ~CCamera() = default;

        /// <summary>
        /// Función para incializar los miembros de la clase
        /// </summary>
        void Init(CameraDescriptor _cameraDesc,
            bool _isOGL);
        /// <summary>
        /// Función para actualizar nuestra matríz de vista
        /// </summary>
        void UpdateViewMatrix();
        /// <summary>
        /// Función para la detección de un input
        /// </summary>
        void InputDetection(WPARAM _param);
        /// <summary>
        /// Función para poder aplicar una rotación PITCH
        /// </summary>
        void PitchX(WPARAM _param);
        /// <summary>
        /// Función para poder aplicar una rotación ROLL
        /// </summary>
        void RollZ(WPARAM _param);
        /// <summary>
        /// Función para poder aplicar una rotación YAW
        /// </summary>
        void YawY(WPARAM _param);
        /// <summary>
        /// Función para poder aplicar un movimiento a la cámara
        /// </summary>
        void Move(WPARAM _param);
        /// <summary>
        /// Función para poder aplicar una rotación de la vista
        /// </summary>
        void MouseRotation();

        ///
        /// C R E A T E´s
        /// 

        /// <summary>
        /// Función para poder generar una vista
        /// </summary>
        void CreateView();
        /// <summary>
        /// Función para poder generar una
        /// matríz de proyección
        /// </summary>
        void CreateProjectionMatrix();

        ///
        /// S E T´s
        /// 

        /// <summary>
        /// Función para guardar el valor WIDHT
        /// </summary>
        void SetWidht(float _width);
        /// <summary>
        /// Función para guardar el valor HEIGHT
        /// </summary>
        void SetHeight(float _height);
        /// <summary>
        /// Función para guardar el valor NEAR
        /// </summary>
        void SetNear(float _near);
        /// <summary>
        /// Función para guardar el valor FAR
        /// </summary>
        void SetFar(float _far);
        /// <summary>
        /// Función para guardar el valor 
        /// Field Of View
        /// </summary>
        void SetFoV(float _foV);
        /// <summary>
        /// Función para guardar el valor EYE
        /// </summary>
        void SetEye(glm::vec3 _vec3);
        /// <summary>
        /// Función para guardar el valor LOOK AT
        /// </summary>
        void SetLookAt(glm::vec3 _vec3);
        /// <summary>
        /// Función para guardar el valor UP
        /// </summary>
        void SetUp(glm::vec3 _vec3);
        /// <summary>
        /// Función para guardar el valor X, Y
        /// de nuestro mouse
        /// </summary>
        void SetOriginalMousePos(float _x, 
            float _y);
        /// <summary>
        /// Función para guardar el valor bool
        /// sobre un click o no
        /// </summary>
        void SetClickPressed(bool _bool);

        ///
        /// G E T´s
        /// 
        
        /// <summary>
        /// Función para obtener la matríz de vista
        /// </summary>
        glm::mat4x4 GetView();
        /// <summary>
        /// Función para obtener la matríz de proyección
        /// </summary>
        glm::mat4x4 GetProjection();
        /// <summary>
        /// Función para obtener la posición original del mouse
        /// </summary>
        glm::vec2 GetOriginalMousePos();
        /// <summary>
        /// Función para obtener el booleano de detección de un click
        /// </summary>
        bool GetClickPressed();
};