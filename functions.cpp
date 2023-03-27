#include "structures.h"
#include <stdio.h>

using namespace std;

#define KEYEVENTF_KEYDOWN 0x0000

const COLORREF rgbRed = 0x000000FF;

position_2d make_pos(POINT p)
{
    position_2d s;
    s.x = p.x;
    s.y = p.y;
    return s;
}

color make_color(COLORREF c)
{
    color p;
    p.r = GetRValue(c);
    p.g = GetGValue(c);
    p.b = GetBValue(c);
    return p;
}

inline bool interval(int val, int must_be, int &i)
{
    return ((must_be - i) <= val && val <= (must_be + i));
}

bool is_almost_the_same_color(color val, color must_be, int &pos_gap)
{
    int a, b;
    return interval(val.r, must_be.r, pos_gap) &&
           interval(val.g, must_be.g, pos_gap) &&
           interval(val.b, must_be.b, pos_gap);
}

void draw_cross(HDC &hDC, position_2d p, COLORREF color)
{
    const int dist = 10;
    SetPixel(hDC, p.x - dist, p.y, color);
    SetPixel(hDC, p.x + dist, p.y, color);
    SetPixel(hDC, p.x, p.y - dist, color);
    SetPixel(hDC, p.x, p.y + dist, color);
}

void update_key_state(WORD key, DWORD flag)
{
    INPUT ip;
    // Set up a generic keyboard event.
    ip.type = INPUT_KEYBOARD;
    ip.ki.wScan = 0; // hardware scan code for key
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;
    // Press any key
    ip.ki.wVk = key;      // virtual-key code for the key
    ip.ki.dwFlags = flag; // 0 for key press
    SendInput(1, &ip, sizeof(INPUT));
}

void arrow_press(HDC &hDC, arrow Arr, int &possible_gap, int &delay_btw, int &dealy_aft)
{
    // get single pixel from monitor
    COLORREF pixel_from_monitor = GetPixel(hDC, Arr.arrow_pos.x, Arr.arrow_pos.y);

    draw_cross(hDC, Arr.arrow_pos, rgbRed);

    if (is_almost_the_same_color(make_color(pixel_from_monitor), Arr.arrow_color, possible_gap))
    {
        if (!(GetAsyncKeyState(Arr.associated_key) & 1))
        {
            Sleep(delay_btw);
            update_key_state(Arr.associated_key, KEYEVENTF_KEYDOWN); // press
        }
    }
    else
    {
        if (GetAsyncKeyState(Arr.associated_key) & 1)
        {
            update_key_state(Arr.associated_key, KEYEVENTF_KEYUP); // release
            Sleep(dealy_aft);
        }
    }
}

void scan_and_do(arrow arrows4[4], int &possible_gap, int &delay_btw, int &dealy_aft)
{
    // get screen
    HDC hDC = GetDC(NULL);

    for (int i = 0; i < 4; i++)
    {
        arrow_press(hDC, arrows4[i], possible_gap, delay_btw, dealy_aft);
    }

    // release this shit
    ReleaseDC(NULL, hDC);
}

void set_arrow_pos(arrow &a)
{
    HDC hDC = GetDC(NULL);
    POINT p;

    while (!(GetAsyncKeyState(VK_END) & 1))
    {
        GetCursorPos(&p);
        draw_cross(hDC, make_pos(p), rgbRed);
        Sleep(15);
    }

    GetCursorPos(&p);
    a.arrow_pos.x = (int)p.x;
    a.arrow_pos.y = (int)p.y;
    ReleaseDC(NULL, hDC);
}

void set_arrow_color_from_monitor(arrow &a)
{
    HDC hDC = GetDC(NULL);
    POINT p;

    while (!(GetAsyncKeyState(VK_END) & 1))
    {
        GetCursorPos(&p);
        draw_cross(hDC, make_pos(p), GetPixel(hDC, p.x, p.y));
        Sleep(15);
    }

    GetCursorPos(&p);

    a.arrow_color = make_color(GetPixel(hDC, p.x - 1, p.y - 1));
    ReleaseDC(NULL, hDC);
}

void set_associated_key(arrow &a)
{
    Sleep(250);
    while (1)
    {
        for (int i = 0; i < 256; i++)
        {
            if (GetAsyncKeyState(i) & 1)
            {
                a.associated_key = i;
                return;
            }
        }
        Sleep(15);
    }
}