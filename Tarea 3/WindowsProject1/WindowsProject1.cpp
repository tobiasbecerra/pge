 #include "framework.h"
#include "WindowsProject1.h"
#include <stdio.h>

#define MAX_LOADSTRING 100

// Variables globales:
HINSTANCE hInst;                                // instancia actual
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal
HWND hEdit;                                     // Control de edición
bool isDarkMode = false;
#define IDT_AUTOSAVE 1
#define IDM_TOGGLE_DARKMODE 2000

// Colores/recursos para temas
const COLORREF CLR_DARK_BG = RGB(30, 30, 30);
const COLORREF CLR_DARK_TXT = RGB(220, 220, 220);
COLORREF CLR_LIGHT_BG;
COLORREF CLR_LIGHT_TXT;
HBRUSH hbrDark = NULL;
HBRUSH hbrLight = NULL;

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Construye el título con contador y, opcionalmente, aviso de autoguardado
static void UpdateAppTitle(HWND hWnd, bool announceAutosave)
{
    int len = GetWindowTextLength(hEdit);
    WCHAR newTitle[256];
    if (announceAutosave)
    {
        SYSTEMTIME st; GetLocalTime(&st);
        swprintf_s(newTitle, L"%s - Caracteres: %d - Autoguardado realizado a las %02d:%02d:%02d",
            szTitle, len, st.wHour, st.wMinute, st.wSecond);
    }
    else
    {
        swprintf_s(newTitle, L"%s - Caracteres: %d", szTitle, len);
    }
    SetWindowText(hWnd, newTitle);
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Inicializar cadenas globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_WINDOWSPROJECT1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realizar la inicialización de la aplicación:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSPROJECT1));

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

    return (int)msg.wParam;
}

//
//  FUNCIÓN: MyRegisterClass()
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDR_MAINMENU);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCIÓN: InitInstance(HINSTANCE, int)
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Almacenar identificador de instancia en una variable global

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
        return FALSE;

    // Crear el EDIT y ajustar estilos útiles
    hEdit = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL |
        ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
        0, 0, 0, 0, hWnd, (HMENU)1, hInstance, nullptr);

    // Inicializar colores claros según el tema del sistema
    CLR_LIGHT_BG = GetSysColor(COLOR_WINDOW);
    CLR_LIGHT_TXT = GetSysColor(COLOR_WINDOWTEXT);

    // Crear pinceles (se reutilizan; no crear en cada pintado)
    hbrDark = CreateSolidBrush(CLR_DARK_BG);
    hbrLight = CreateSolidBrush(CLR_LIGHT_BG);

    // Redimensionar inicialmente el EDIT para ocupar todo el cliente
    RECT rc;
    GetClientRect(hWnd, &rc);
    MoveWindow(hEdit, 0, 0, rc.right - rc.left, rc.bottom - rc.top, TRUE);

    // Temporizador de autoguardado (60s)
    SetTimer(hWnd, IDT_AUTOSAVE, 60000, NULL);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Inicializar el título con contador (0)
    UpdateAppTitle(hWnd, false);

    return TRUE;
}

//
//  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_SIZE:
    {
        // Ajustar el EDIT al nuevo tamaño del área cliente
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        if (hEdit)
            MoveWindow(hEdit, 0, 0, width, height, TRUE);
    }
    break;

    case WM_TIMER:
        if (wParam == IDT_AUTOSAVE) {
            int len = GetWindowTextLength(hEdit);
            wchar_t* buffer = new wchar_t[len + 1];
            GetWindowTextW(hEdit, buffer, len + 1);
            FILE* f = nullptr;
            if (_wfopen_s(&f, L"autosave.txt", L"w") == 0 && f) {
                fwprintf(f, L"%s", buffer);
                fclose(f);
            }
            delete[] buffer;

            // Anunciar el autoguardado en el título
            UpdateAppTitle(hWnd, true);
        }
        break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);

        // Si el cambio de texto viene del control EDIT
        if (HIWORD(wParam) == EN_CHANGE && (HWND)lParam == hEdit) {
            // Actualizar sólo el contador (sin aviso de autoguardado)
            UpdateAppTitle(hWnd, false);
            return 0; // No procesar como comando de menú
        }

        // Analizar las selecciones de menú:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case IDM_TOGGLE_DARKMODE:
            isDarkMode = !isDarkMode;
            InvalidateRect(hWnd, NULL, TRUE);
            InvalidateRect(hEdit, NULL, TRUE); // Repintar el EDIT con los nuevos colores
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;

    // Pintado del área cliente de la ventana principal (no del EDIT)
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        HBRUSH hbr = isDarkMode ? hbrDark : hbrLight;
        FillRect(hdc, &ps.rcPaint, hbr);
        EndPaint(hWnd, &ps);
    }
    break;

    // Colorear el EDIT según el tema
    case WM_CTLCOLOREDIT:
    {
        HDC hdc = (HDC)wParam;
        HWND hwndCtl = (HWND)lParam;
        if (hwndCtl == hEdit) {
            if (isDarkMode) {
                SetTextColor(hdc, CLR_DARK_TXT);
                SetBkColor(hdc, CLR_DARK_BG);
                return (INT_PTR)hbrDark;
            }
            else {
                SetTextColor(hdc, CLR_LIGHT_TXT);
                SetBkColor(hdc, CLR_LIGHT_BG);
                return (INT_PTR)hbrLight;
            }
        }
    }
    break;

    case WM_DESTROY:
        KillTimer(hWnd, IDT_AUTOSAVE);
        if (hbrDark) { DeleteObject(hbrDark);  hbrDark = NULL; }
        if (hbrLight) { DeleteObject(hbrLight); hbrLight = NULL; }
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