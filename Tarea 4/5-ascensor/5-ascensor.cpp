// 5-ascensor.cpp : Define el punto de entrada de la aplicación.
//

#include "framework.h"
#include "5-ascensor.h"

#define MAX_LOADSTRING 100
#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))
#endif

// Variables globales:
HINSTANCE hInst;                                // instancia actual
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal

int g_piso = 0;
int g_pisoVisual = 0;
RECT g_rectBotones[3];

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Colocar código aquí.

    // Inicializar cadenas globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY5ASCENSOR, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realizar la inicialización de la aplicación:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY5ASCENSOR));

    MSG msg;

    // Bucle principal de mensajes:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCIÓN: MyRegisterClass()
//
//  PROPÓSITO: Registra la clase de ventana.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY5ASCENSOR));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY5ASCENSOR);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCIÓN: InitInstance(HINSTANCE, int)
//
//   PROPÓSITO: Guarda el identificador de instancia y crea la ventana principal
//
//   COMENTARIOS:
//
//        En esta función, se guarda el identificador de instancia en una variable común y
//        se crea y muestra la ventana principal del programa.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Almacenar identificador de instancia en una variable global

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PROPÓSITO: Procesa mensajes de la ventana principal.
//
//  WM_COMMAND  - procesar el menú de aplicaciones
//  WM_PAINT    - Pintar la ventana principal
//  WM_DESTROY  - publicar un mensaje de salida y volver
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
    {
        POINT pt;
        pt.x = GET_X_LPARAM(lParam);
        pt.y = GET_Y_LPARAM(lParam);

        // Calcula los rectángulos de los botones
        RECT rcClient;
        GetClientRect(hWnd, &rcClient);
        int ancho = (rcClient.right - rcClient.left) / 3;
        int alto = 60;
        for (int i = 0; i < 3; ++i) {
            g_rectBotones[i].left = rcClient.left + i * ancho + 10;
            g_rectBotones[i].top = rcClient.top + 20;
            g_rectBotones[i].right = g_rectBotones[i].left + ancho - 20;
            g_rectBotones[i].bottom = g_rectBotones[i].top + alto;
        }

        for (int i = 0; i < 3; ++i) {
            if (PtInRect(&g_rectBotones[i], pt)) {
                g_piso = i + 1;
                g_pisoVisual = g_piso;
                InvalidateRect(hWnd, NULL, TRUE);
                break;
            }
        }
    }
    break;


    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Analizar las selecciones de menú:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        RECT rcClient;
        GetClientRect(hWnd, &rcClient);
        int ancho = (rcClient.right - rcClient.left) / 3;
        int alto = 60;
        HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);

        // Dibuja los botones
        for (int i = 0; i < 3; ++i) {
            g_rectBotones[i].left = rcClient.left + i * ancho + 10;
            g_rectBotones[i].top = rcClient.top + 20;
            g_rectBotones[i].right = g_rectBotones[i].left + ancho - 20;
            g_rectBotones[i].bottom = g_rectBotones[i].top + alto;

            HBRUSH hBrush;
            if (g_pisoVisual == i + 1)
                hBrush = CreateSolidBrush(RGB(200, 200, 255)); // Color destacado
            else
                hBrush = CreateSolidBrush(RGB(220, 220, 220)); // Color normal

            FillRect(hdc, &g_rectBotones[i], hBrush);
            DeleteObject(hBrush);

            // Dibuja el borde
            FrameRect(hdc, &g_rectBotones[i], (HBRUSH)GetStockObject(BLACK_BRUSH));

            // Dibuja el número
            SelectObject(hdc, hFont);
            WCHAR txt[2] = { L'1' + i, 0 };
            SetBkMode(hdc, TRANSPARENT);
            DrawTextW(hdc, txt, 1, &g_rectBotones[i], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
        }

        // Dibuja el texto del último piso
        WCHAR buffer[32];
        wsprintf(buffer, L"Ultimo piso: %d", g_piso);
        RECT rcTexto = { rcClient.left, rcClient.top + alto + 40, rcClient.right, rcClient.bottom };
        DrawTextW(hdc, buffer, -1, &rcTexto, DT_CENTER | DT_TOP | DT_SINGLELINE);

        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Controlador de mensajes del cuadro Acerca de.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
