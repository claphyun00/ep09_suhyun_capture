#include "pch.h"
#include <stdio.h>
#include "tipsware.h"

void OnMouseLeftUp(int a_mixed_key, POINT a_pos)
{
    RECT r;
    GetClientRect(gh_main_wnd, &r);
    ClientToScreen(gh_main_wnd, (POINT*)&r.left);
    ClientToScreen(gh_main_wnd, (POINT*)&r.right);

    void* p_image = CaptureScreenGP(r.left, r.top, r.right, r.bottom);

    char save_path[MAX_PATH];
    SYSTEMTIME cur_time;
    GetLocalTime(&cur_time);

    sprintf_s(save_path, MAX_PATH, ".\\cap\\%04d%02d%02d_%02d%02d%02d.png",
        cur_time.wYear, cur_time.wMonth, cur_time.wDay,
        cur_time.wHour, cur_time.wMinute, cur_time.wSecond);
    SaveImageGP(p_image, save_path);

    DeleteImageGP(p_image);
}

MOUSE_MESSAGE(NULL, OnMouseLeftUp, NULL)

int main()
{
    ChangeWorkSize(400, 300);
    CreateDirectory(".\\cap", NULL);

    int wnd_style = GetWindowLong(gh_main_wnd, GWL_EXSTYLE);
    if (!(wnd_style & WS_EX_LAYERED)) 
        SetWindowLong(gh_main_wnd, GWL_EXSTYLE, wnd_style | WS_EX_LAYERED);
    SetLayeredWindowAttributes(gh_main_wnd, RGB(255, 1, 1), 0, LWA_COLORKEY);

    wnd_style = ::GetWindowLong(gh_main_wnd, GWL_STYLE);
    ::SetWindowLong(gh_main_wnd, GWL_STYLE, wnd_style & ~WS_THICKFRAME);

    Clear(0, RGB(255, 1, 1)); 
    ShowDisplay();

    return 0;
}