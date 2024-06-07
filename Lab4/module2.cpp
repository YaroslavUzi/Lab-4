#include "module2.h"
#include "resource.h"

LRESULT CALLBACK DialogProc2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DialogProc3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
static HWND hMainWnd;

int Func_MOD2(HWND hWnd)
{
    hMainWnd = hWnd;
    DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hWnd, DialogProc2);
    return 0;
}

LRESULT CALLBACK DialogProc2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON_NEXT:
            EndDialog(hDlg, IDD_DIALOG3);
            DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG3), hMainWnd, DialogProc3);
            return TRUE;

        case IDC_BUTTON_CANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return TRUE;
        }
        break;

    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }
    return FALSE;
}

LRESULT CALLBACK DialogProc3(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON_BACK:
            EndDialog(hDlg, IDD_DIALOG2);
            DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG2), hMainWnd, DialogProc2);
            return TRUE;

        case IDC_BUTTON_CANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            return TRUE;
        }
        break;

    case WM_CLOSE:
        EndDialog(hDlg, 0);
        return TRUE;
    }
    return FALSE;
}
