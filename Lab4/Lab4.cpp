#include <windows.h>
#include "module1.h"
#include "module2.h"
#include "resource.h"

#define ID_WORK1 1
#define ID_WORK2 2

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
    HWND hwnd;
    MSG messages;
    WNDCLASSEX wincl;

    wincl.hInstance = hInst;
    wincl.lpszClassName = TEXT("Lab4Class");
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof(WNDCLASSEX);

    wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = MAKEINTRESOURCE(IDR_MAINMENU);
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    if (!RegisterClassEx(&wincl))
        return 0;

    hwnd = CreateWindowEx(
        0,
        TEXT("Lab4Class"),
        TEXT("Lab4"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        544,
        375,
        HWND_DESKTOP,
        NULL,
        hInst,
        NULL
    );

    ShowWindow(hwnd, ncmdshow);

    while (GetMessage(&messages, NULL, 0, 0))
    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }

    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int number = 0;
    wchar_t buffer[4];

    switch (message)
    {
    case WM_CREATE:
    {
        HMENU hMenu = CreateMenu();
        AppendMenu(hMenu, MF_STRING, ID_WORK1, TEXT("Робота1"));
        AppendMenu(hMenu, MF_STRING, ID_WORK2, TEXT("Робота2"));
        SetMenu(hwnd, hMenu);
    }
    break;

    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case ID_WORK1:
            Func_MOD1(hwnd);
            break;

        case ID_WORK2:
            Func_MOD2(hwnd);
            break;

        case IDM_EXIT:
            PostQuitMessage(0);
            break;

        case IDM_ABOUT:
            DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, [](HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) -> INT_PTR {
                if (message == WM_COMMAND)
                {
                    if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
                    {
                        EndDialog(hDlg, LOWORD(wParam));
                        return (INT_PTR)TRUE;
                    }
                }
                return (INT_PTR)FALSE;
                });
            break;
        }
    }
    break;

    case WM_USER + 1:
        number = (int)wParam;
        InvalidateRect(hwnd, NULL, TRUE);
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        TextOut(hdc, 10, 10, TEXT("Вибране число: "), 16);
        _itow_s(number, buffer, 10);
        TextOut(hdc, 130, 10, buffer, wcslen(buffer));
        EndPaint(hwnd, &ps);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
