#include "..\Includes\CGraphicApi.h"
#include "..\Includes\CGraphicApiDX.h"

#include <windows.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <codecvt>
#include <locale>

///
/// Global variables
///

///The main window class name.
static TCHAR g_szWindowClass[] = _T("DesktopApp");
///The string that appears in the application's title bar.
static TCHAR g_szTitle[] = _T("Windows - KriegerFS-");
///Tamaño de pantalla
unsigned int g_width = 1000;
unsigned int g_height = 800;
///
HINSTANCE g_hInst;
///
std::vector<SimpleVertex*> g_pVertices;
///
std::vector<unsigned int*> g_pIndices;
///
glm::mat4x4 g_World;
glm::mat4x4 g_View;

///
/// 
/// 
CGraphicApiDX* g_pGraphicApiDx = new CGraphicApiDX();
std::vector<CTexture*> g_pRenderTargetView;
CTexture* g_pDepthStencil = nullptr;
CVertexShader* g_pVertexShader = nullptr;
CInputLayout* g_pVertexLayout = nullptr;
CPixelShader* g_pPixelShader = nullptr;
CVertexBuffer* g_pVertexBuffer = nullptr;
CIndexBuffer* g_pIndexBuffer = nullptr;
CConstantBuffer* g_pCBNeverChanges = nullptr;
CConstantBuffer* g_pCBChangeOnResize = nullptr;
CConstantBuffer* g_pCBChangesEveryFrame = nullptr;

///
/// Funciones
///

///Manejar los mensajes que la aplicación 
/// recibe de Windows cuando ocurren eventos.
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

///Guardamos información de la ventana
///del typedef "WNDCLASSEX"
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

///
void TheWorld() {

    ///Inicializamos la matriz de identidad
    g_World = glm::mat4(1.0f);

    // Initialize the view matrix
    glm::vec3 Front = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 Right = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 Eye = glm::vec3(0.0f, 3.0f, -6.0f);
    glm::vec3 LookAt = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    
    int Far = 1000;
    float Near = 0.01;
    float FoV = 0.78539816339;

    g_View;
}

///Creación de la ventana
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

///Creación del simple vertex
void CreateSimpleVertex() {

    SimpleVertex vertices[] =
    {
        { glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 0.0f) },
        { glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
        { glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
        { glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },

        { glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f) },
        { glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
        { glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
        { glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },

        { glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
        { glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
        { glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f) },
        { glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },

        { glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
        { glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
        { glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f) },
        { glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },

        { glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f) },
        { glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 0.0f) },
        { glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(1.0f, 1.0f) },
        { glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f) },

        { glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
        { glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f) },
        { glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) },
        { glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },
    };

    for (unsigned int i = 0; i < 120; i++) {

        g_pVertices.push_back(&vertices[i]);
    }
}

///Creación del indices
void CreateIndices() {

    unsigned int indices[] =
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

    for (unsigned int i = 0; i < 36; i++) {

        g_pIndices.push_back(&indices[i]);
    }
}

///Función con todos los create
void AllCreates() {

    ///Creamos el render target view
    g_pRenderTargetView.push_back(g_pGraphicApiDx->CreateTexture(g_width, g_height,
        D3D11_BIND_RENDER_TARGET,
        TEXTURE_FORMAT_R8G8B8A8_UNORM));

    ///Creamos el depth stencil view
    g_pDepthStencil = g_pGraphicApiDx->CreateTexture(g_width, g_height,
        D3D11_BIND_DEPTH_STENCIL,
        TEXTURE_FORMAT_D24_UNORM_S8_UINT);

    ///Creamos el vertex shader
    g_pVertexShader = g_pGraphicApiDx->CreateVertexShader
    (std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes("CubeShader.fx"), "VS");

    ///Creamos el input layout
    g_pVertexLayout = g_pGraphicApiDx->CreateInputLayout(*g_pVertexShader);

    ///Creamos el pixel shader
    g_pPixelShader = g_pGraphicApiDx->CreatePixelShader
    (std::wstring_convert<std::codecvt_utf8<wchar_t>>().from_bytes("CubeShader.fx"), "PS");

    ///Creamos el vertex buffer
    CreateSimpleVertex();
    g_pVertexBuffer = g_pGraphicApiDx->CreateVertexBuffer(g_pVertices);

    ///Creamos el index buffer
    CreateIndices();
    g_pIndexBuffer = g_pGraphicApiDx->CreateIndexBuffer(g_pIndices);

    ///Creamos los constant buffers

    ///NeverChanges
    g_pCBNeverChanges = g_pGraphicApiDx->CreateConstantBuffer(sizeof(CBNeverChanges));

    ///NeverChanges
    g_pCBChangeOnResize = g_pGraphicApiDx->CreateConstantBuffer(sizeof(CBChangeOnResize));

    ///NeverChanges 
    g_pCBChangesEveryFrame = g_pGraphicApiDx->CreateConstantBuffer(sizeof(CBChangesEveryFrame));

    ///Creamos el sample state
    g_pGraphicApiDx->CreateSamplerState();


}

///Función con todos las guardados
void AllSets() {

    ///Guardamos los render targets
    g_pGraphicApiDx->SetRenderTarget(g_pRenderTargetView, *g_pDepthStencil, 1);

    ///Guardamos un viewport
    g_pGraphicApiDx->SetViewport(1, g_width, g_height);

    ///Guardamos el input layout
    g_pGraphicApiDx->SetInputLayout(*g_pVertexLayout);

    ///Guardamos el vertex buffer
    g_pGraphicApiDx->SetVertexBuffer(*g_pVertexBuffer);

    ///Guardamos el index buffer
    g_pGraphicApiDx->SetIndexBuffer(*g_pIndexBuffer);

    ///Guardamos la topología
    g_pGraphicApiDx->SetPrimitiveTopology(PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

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

    ///Mandamos la ventana a la API
    g_pGraphicApiDx->InitDevice();

    AllCreates();

    AllSets();

   



















    ///Actualizamos la ventana
    UpdateWindow(hWnd);

    ///Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}