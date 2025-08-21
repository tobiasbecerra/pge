// 1-check-in.cpp : Define el punto de entrada de la aplicación.
//

#include "framework.h"
#include "1-check-in.h"
#include <string>
#include <cwctype>

#define MAX_LOADSTRING 100

// Variables globales:
HINSTANCE hInst;                                // instancia actual
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal

// Estado de la entrada del huésped
static std::wstring g_nombre;

// ID y handle del botón Confirmar
#define ID_BTN_CHECKIN 1001
static HWND g_hBtnCheckIn = nullptr;

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
    LoadStringW(hInstance, IDC_MY1CHECKIN, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realizar la inicialización de la aplicación:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1CHECKIN));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1CHECKIN));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY1CHECKIN);
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

   // Crear botón "Confirmar check-in"
   g_hBtnCheckIn = CreateWindowW(
       L"BUTTON",
       L"Confirmar check-in",
       WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_DEFPUSHBUTTON,
       10, 50, 200, 32,
       hWnd,
       (HMENU)ID_BTN_CHECKIN,
       hInstance,
       nullptr
   );

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PROPÓSITO: Procesa mensajes de la ventana principal.
//
//  WM_COMMAND  - procesar el menú de aplicaciones y botones
//  WM_CHAR     - entrada de teclado por carácter
//  WM_PAINT    - Pintar la ventana principal
//  WM_SIZE     - Reposicionar controles
//  WM_DESTROY  - publicar un mensaje de salida y volver
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case ID_BTN_CHECKIN:
                if (HIWORD(wParam) == BN_CLICKED)
                {
                    if (g_nombre.empty())
                    {
                        MessageBoxW(hWnd,
                            L"Introduzca el nombre del huesped antes de confirmar.",
                            L"Aviso",
                            MB_ICONEXCLAMATION | MB_OK);
                    }
                    else
                    {
                        std::wstring pregunta = L"¿Confirmar check-in de: " + g_nombre + L"?";
                        int r = MessageBoxW(hWnd, pregunta.c_str(),
                                            L"Confirmar check-in",
                                            MB_ICONQUESTION | MB_YESNO | MB_DEFBUTTON1);
                        if (r == IDYES)
                        {
                            MessageBoxW(hWnd, L"Check-in confirmado.",
                                        L"Éxito", MB_ICONINFORMATION | MB_OK);
                            g_nombre.clear();
                            InvalidateRect(hWnd, nullptr, TRUE);
                        }
                    }
                    // Devolver el foco a la ventana principal para seguir escribiendo
                    SetFocus(hWnd);
                    return 0;
                }
                // Otros comandos no gestionados
                return DefWindowProc(hWnd, message, wParam, lParam);
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;

    case WM_CHAR:
        {
            wchar_t ch = static_cast<wchar_t>(wParam);
            if (ch == L'\b') {
                if (!g_nombre.empty()) g_nombre.pop_back();
            } else if (iswprint(ch)) {
                g_nombre.push_back(ch);
            }
            InvalidateRect(hWnd, nullptr, TRUE);
            return 0;
        }

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);

            RECT rc;
            GetClientRect(hWnd, &rc);
            rc.left += 10;
            rc.top  += 10;

            SetBkMode(hdc, TRANSPARENT);

            const std::wstring etiqueta = L"Nombre del huesped: ";
            const std::wstring texto = etiqueta + g_nombre;

            DrawTextW(hdc, texto.c_str(), static_cast<int>(texto.size()), &rc,
                      DT_LEFT | DT_TOP | DT_NOPREFIX);

            EndPaint(hWnd, &ps);
        }
        break;

    case WM_SIZE:
        {
            if (g_hBtnCheckIn)
            {
                RECT rc;
                GetClientRect(hWnd, &rc);
                int btnW = 200;
                int btnH = 32;
                int x = 10;
                int y = 50; // Debajo del rótulo
                MoveWindow(g_hBtnCheckIn, x, y, btnW, btnH, TRUE);
            }
            return 0;
        }

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
