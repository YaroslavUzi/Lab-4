#include "module1.h"
#include "resource.h"

LRESULT CALLBACK DialogProc1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
static HWND hMainWnd;

int Func_MOD1(HWND hWnd)
{
    hMainWnd = hWnd;
    DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DialogProc1);
    return 0;
}

LRESULT CALLBACK DialogProc1(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND hScrollBar, hEdit;
    static int pos = 0;
    wchar_t buffer[4];

    switch (message)
    {
    case WM_INITDIALOG:
        hScrollBar = GetDlgItem(hDlg, IDC_SCROLLBAR1);
        hEdit = GetDlgItem(hDlg, IDC_EDIT1);
        SetScrollRange(hScrollBar, SB_CTL, 1, 100, TRUE);
        SetScrollPos(hScrollBar, SB_CTL, 1, TRUE);
        return TRUE;

    case WM_HSCROLL:
        if (LOWORD(wParam) == SB_THUMBTRACK || LOWORD(wParam) == SB_THUMBPOSITION)
        {
            pos = HIWORD(wParam);
            SetScrollPos(hScrollBar, SB_CTL, pos, TRUE);
            _itow_s(pos, buffer, 10);
            SetWindowText(hEdit, buffer);
        }
        return TRUE;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON_OK:
            GetWindowText(hEdit, buffer, sizeof(buffer) / sizeof(buffer[0]));
            pos = _wtoi(buffer);
            SendMessage(hMainWnd, WM_USER + 1, pos, 0);
            EndDialog(hDlg, LOWORD(wParam));
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
