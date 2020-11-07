#include "..\Includes\CGraphicApi.h"
#include "..\Includes\CGraphicApiDX.h"

#include <windows.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <codecvt>
#include <locale>

///
/// V A R I A B L E S
/// G L O B A L E S
///

///The main window class name.
static TCHAR g_szWindowClass[] = _T("DesktopApp");
///The string that appears in the application's title bar.
static TCHAR g_szTitle[] = _T("Windows - KriegerFS-");
///Tamaño de pantalla
unsigned int g_width = 1000;
unsigned int g_height = 800;

HINSTANCE g_hInst;

std::vector<SimpleVertex> g_pVertices;
std::vector<uint32_t> g_pIndices;

glm::mat4x4 g_world;
glm::mat4x4 g_view;
glm::mat4x4 g_projection;

glm::vec4 g_vMeshColor(0.7f, 0.7f, 0.7f, 1.0f);

CGraphicApi* g_pGraphicApiDX = new CGraphicApiDX();
CTexture* g_pRenderTargetView = nullptr;
CTexture* g_pDepthStencil = nullptr;
CVertexShader* g_pVertexShader = nullptr;
CInputLayout* g_pVertexLayout = nullptr;
CPixelShader* g_pPixelShader = nullptr;
CVertexBuffer* g_pVertexBuffer = nullptr;
CIndexBuffer* g_pIndexBuffer = nullptr;
CConstantBuffer* g_pConstantBuffer1 = nullptr;
CConstantBuffer* g_pConstantBuffer2 = nullptr;

///
/// S T R U C T´s
/// 

struct ConstantBuffer1 {

    glm::mat4x4 mView;
    glm::mat4x4 mProjection;
};

struct ConstantBuffer2 {

    glm::mat4x4 mWorld;
    glm::vec4 vMeshColor;
};

///
/// F U N C I O N E S
///

/// <summary>
/// Manejar los mensajes que la aplicación 
/// recibe de Windows cuando ocurren eventos.
/// </summary>
/// <param name="_hWnd"></param>
/// <param name="_message"></param>
/// <param name="_wParam"></param>
/// <param name="_lParam"></param>
/// <returns></returns>
LRESULT CALLBACK WndProc(HWND _hWnd, UINT _message,
    WPARAM _wParam, LPARAM _lParam) {

    PAINTSTRUCT ps;
    HDC hdc;

    switch (_message)
    {
        case WM_PAINT:
            hdc = BeginPaint(_hWnd, &ps);
            EndPaint(_hWnd, &ps);

            break;

        case WM_DESTROY:
            PostQuitMessage(0);

            break;

        default:
            return DefWindowProc(_hWnd, _message, _wParam, _lParam);

            break;
    }

    return 0;
}
/// <summary>
/// Guardamos información de la ventana
/// del typedef "WNDCLASSEX"
/// </summary>
/// <param name="_wcex"></param>
/// <param name="_hInstance"></param>
void SetWndClassEx(WNDCLASSEX& _wcex, _In_ HINSTANCE& _hInstance) {

    _wcex.cbSize = sizeof(WNDCLASSEX);
    _wcex.style = CS_HREDRAW | CS_VREDRAW;
    _wcex.lpfnWndProc = WndProc;
    _wcex.cbClsExtra = 0;
    _wcex.cbWndExtra = 0;
    _wcex.hInstance = _hInstance;
    _wcex.hIcon = LoadIcon(_hInstance, IDI_APPLICATION);
    _wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    _wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    _wcex.lpszMenuName = NULL;
    _wcex.lpszClassName = g_szWindowClass;
    _wcex.hIconSm = LoadIcon(_wcex.hInstance, IDI_APPLICATION);
}
/// <summary>
/// Creación de la ventana
/// </summary>
/// <returns></returns>
HWND& CreateNewWindow() {

    HWND hWnd = CreateWindow(
        ///g_szWindowClass: the name of the application
        g_szWindowClass,
        ///g_szTitle: the text that appears in the title bar
        g_szTitle,
        // WS_OVERLAPPEDWINDOW: the type of window to create
        WS_OVERLAPPEDWINDOW,
        ///CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
        CW_USEDEFAULT, CW_USEDEFAULT,
        ///initial size (width, height)
        g_width, g_height,
        ///NULL: the parent of this window
        NULL,
        ///NULL: this application does not have a menu bar
        NULL,
        // _hInstance: the first parameter from WinMain
        g_hInst,
        ///NULL: not used in this application
        NULL
    );

    return hWnd;
}
/// <summary>
/// Creación del simple vertex
/// </summary>
void CreateSimpleVertex() {

    g_pVertices =
    {
        { glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
        { glm::vec4(1.0f, 1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f) },
        { glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
        { glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },

        { glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
        { glm::vec4(1.0f, -1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f) },
        { glm::vec4(1.0f, -1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
        { glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },

        { glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
        { glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f) },
        { glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
        { glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },

        { glm::vec4(1.0f, -1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
        { glm::vec4(1.0f, -1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f) },
        { glm::vec4(1.0f, 1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
        { glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },

        { glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
        { glm::vec4(1.0f, -1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f) },
        { glm::vec4(1.0f, 1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
        { glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },

        { glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
        { glm::vec4(1.0f, -1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f) },
        { glm::vec4(1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
        { glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },
    };
}
/// <summary>
/// Creación del indices
/// </summary>
void CreateIndices() {

    g_pIndices =
    {
        3,1,0,
        2,1,3,

        6,4,5,
        7,4,6,

        11,9,8,
        10,9,11,

        14,12,13,
        15,12,14,

        19,17,16,
        18,17,19,

        22,20,21,
        23,20,22
    };
}
/// <summary>
/// Creación de la camara 
/// para el mundo
/// </summary>
void CreateCamera() {

    ///Inicializamos la matriz de identidad
    g_world = glm::mat4(1.0f);

    /// Inicializamos los valores para camara
    CameraDescriptor cameraDesc;
    cameraDesc.s_eye = glm::vec3(0.0f, 3.0f, -6.0f);
    cameraDesc.s_far = 1000.0f;
    cameraDesc.s_foV = 0.78539816339f;
    cameraDesc.s_height = g_height;
    cameraDesc.s_lookAt = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraDesc.s_near = 0.01f;
    cameraDesc.s_up = glm::vec3(0.0f, 1.0f, 0.0f);
    cameraDesc.s_width = g_width;

    ///Inicializamos el punto de vista
    g_view = glm::lookAtLH(cameraDesc.s_eye, 
        cameraDesc.s_lookAt, 
        cameraDesc.s_up);

    ///Inicializamos la matriz de proyección
    g_projection = glm::perspectiveFovLH(cameraDesc.s_foV, cameraDesc.s_width,
        cameraDesc.s_height, cameraDesc.s_near, 
        cameraDesc.s_far);
}
/// <summary>
/// Función para almacenar todas las funciones
/// con descripción de "UPDATE"
/// </summary>
void Update() {

    ConstantBuffer1 newConstBuff1;
    newConstBuff1.mProjection = glm::transpose(g_projection);
    newConstBuff1.mView = glm::transpose(g_view);
    g_pGraphicApiDX->UpdateConstantBuffer(&newConstBuff1, *g_pConstantBuffer1);

    ConstantBuffer2 cb;
    cb.mWorld = glm::transpose(g_world);
    cb.vMeshColor = g_vMeshColor;
    g_pGraphicApiDX->UpdateConstantBuffer(&cb, *g_pConstantBuffer2);
}
/// <summary>
/// Función para guardar valores y generar
/// información para la pantalla
/// </summary>
void Render() {

    ///Guardamos los render targets
    g_pGraphicApiDX->SetRenderTarget(*g_pRenderTargetView, *g_pDepthStencil);
    ///Guardamos un viewport
    g_pGraphicApiDX->SetViewport(1, g_width, g_height);
    ///Guardamos el input layout
    g_pGraphicApiDX->SetInputLayout(*g_pVertexLayout);
    ///Guardamos el vertex buffer
    g_pGraphicApiDX->SetVertexBuffer(*g_pVertexBuffer);
    ///Guardamos el index buffer
    g_pGraphicApiDX->SetIndexBuffer(*g_pIndexBuffer);
    ///Guardamos la topología
    g_pGraphicApiDX->SetPrimitiveTopology(PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    ///
    /// Clear the back buffer
    ///
    g_pRenderTargetView = g_pGraphicApiDX->ClearYourRenderTargetView(g_pRenderTargetView);

    ///
    /// Clear the depth buffer to 1.0 (max depth)
    ///
    g_pDepthStencil = g_pGraphicApiDX->ClearYourDepthStencilView(g_pDepthStencil);

    ///
    /// Render the cube
    ///
    g_pGraphicApiDX->SetYourVS(*g_pVertexShader);
    g_pGraphicApiDX->SetYourVSConstantBuffers(g_pConstantBuffer1, 0, 1);
    g_pGraphicApiDX->SetYourVSConstantBuffers(g_pConstantBuffer2, 1, 1);
    g_pGraphicApiDX->SetYourPSConstantBuffers(g_pConstantBuffer2, 1, 1);
    g_pGraphicApiDX->SetYourPS(*g_pPixelShader);
    g_pGraphicApiDX->DrawIndex(36, 0, 0);

    ///
    /// Present our back buffer to our front buffer
    ///

    g_pGraphicApiDX->SwapChainPresent(0, 0);
}
/// <summary>
/// Función donde generamos el proyecto
/// en DirectX
/// </summary>
/// <param name="_hWnd"></param>
void DXProyect(HWND _hWnd) {

    ///Mandamos la ventana a la API
    g_pGraphicApiDX->InitDevice(_hWnd);

    ///Generamos el mundo y su camara
    CreateCamera();

    ///
    /// C R E A T E´s
    ///

    ///Creamos el render target view
    g_pRenderTargetView = g_pGraphicApiDX->GetDefaultBackBuffer();

    ///Creamos el depth stencil view
    g_pDepthStencil = g_pGraphicApiDX->CreateTexture(g_width, g_height,
        D3D11_BIND_DEPTH_STENCIL,
        TEXTURE_FORMAT_D24_UNORM_S8_UINT);

    ///Creamos el vertex shader
    g_pVertexShader = g_pGraphicApiDX->CreateVertexShader
    (L"CubeShader.fx", "VS", "");

    ///Creamos el input layout
    g_pVertexLayout = g_pGraphicApiDX->CreateInputLayout(*g_pVertexShader);

    ///Creamos el pixel shader
    g_pPixelShader = g_pGraphicApiDX->CreatePixelShader
    (L"CubeShader.fx", "PS", "");

    ///Creamos el vertex buffer
    CreateSimpleVertex();
    g_pVertexBuffer = g_pGraphicApiDX->CreateVertexBuffer(g_pVertices);

    ///Creamos el index buffer
    CreateIndices();
    g_pIndexBuffer = g_pGraphicApiDX->CreateIndexBuffer(g_pIndices);

    ///Creamos los constant buffers para el shader
    g_pConstantBuffer1 = g_pGraphicApiDX->CreateConstantBuffer(sizeof(ConstantBuffer1));
    g_pConstantBuffer2 = g_pGraphicApiDX->CreateConstantBuffer(sizeof(ConstantBuffer2));
}
/// <summary>
/// Función donde se generará el proyecto
/// para OpenGL
/// </summary>
/// <param name="_hWnd"></param>
void OGLProyect(HWND _hWnd) {


}

///
/// F U N C I Ó N
/// P R I N C I P A L
/// 
int CALLBACK WinMain(
    _In_ HINSTANCE _hInstance,
    _In_opt_ HINSTANCE _hPrevInstance,
    _In_ LPSTR     _lpCmdLine,
    _In_ int       _nCmdShow){

    WNDCLASSEX wcex;

    ///Guardamos la información principal
    /// para la ventana
    SetWndClassEx(wcex, _hInstance);

    ///Posible error
    if (!RegisterClassEx(&wcex)){

        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    ///Store instance handle in our global variable
    g_hInst = _hInstance;

    ///Creamos la ventana
    HWND hWnd = CreateNewWindow();

    ///Posible error
    if (!hWnd) {

        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("Windows Desktop Guided Tour"),
            NULL);

        return 1;
    }

    ///hWnd: the value returned from CreateWindow
    ///_nCmdShow: the fourth parameter from WinMain
    ShowWindow(hWnd, _nCmdShow);

    ///Proyecto en Direct X
    DXProyect(hWnd);

    ///Proyecto en OpenGL
    //OGLProyect(hWnd);

    ///Actualizamos la ventana
    UpdateWindow(hWnd);
    ///Main message loop:
    MSG msg = { 0 };
    while (WM_QUIT != msg.message){

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else{

            Update();

            Render();
        }
    }
    return (int)msg.wParam;
}