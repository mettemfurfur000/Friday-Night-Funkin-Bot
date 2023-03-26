#include "structures.h"
#include <stdio.h>

using namespace std;

#define KEYEVENTF_KEYDOWN 0x0000

inline bool interval(int val, int must_be, int &i)
{
    return ((must_be + i) <= val && val >= (must_be - i));
}

bool is_almost_the_same_color(COLORREF val, COLORREF must_be, int &pos_gap)
{
    int a, b;
    return interval(GetRValue(val), GetRValue(must_be), pos_gap) &&
           interval(GetGValue(val), GetGValue(must_be), pos_gap) &&
           interval(GetBValue(val), GetBValue(must_be), pos_gap);
}

void update_key_state(WORD key, int delay, DWORD flag)
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
    Sleep(delay);
}

void arrow_press(HDC &hDC, arrow Arr, int &possible_gap, int &delay_btw, int &dealy_aft)
{
    // get single pixel from monitor
    COLORREF pixel_from_monitor = GetPixel(hDC, Arr.arrow_pos.x, Arr.arrow_pos.y);

    if (is_almost_the_same_color(pixel_from_monitor, Arr.arrow_color, possible_gap))
    {
        update_key_state(Arr.associated_key, delay_btw, KEYEVENTF_KEYDOWN); // press
    }
    else
    {
        update_key_state(Arr.associated_key, dealy_aft, KEYEVENTF_KEYUP); // release
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
    POINT p;
    while (1)
    {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x01)
        {
            GetCursorPos(&p);
            a.arrow_pos.x = p.x;
            a.arrow_pos.y = p.y;
            break;
        }
        Sleep(16);
    }
}

void set_arrow_color_from_monitor(arrow &a)
{
    HDC hDC = GetDC(NULL);
    COLORREF pixel_from_monitor = GetPixel(hDC, a.arrow_pos.x, a.arrow_pos.y);

    a.arrow_color = pixel_from_monitor;
    ReleaseDC(NULL, hDC);
}

void set_associated_key(arrow &a)
{
    printf("Press key to bind\n");

    WORD result = 0;

    do{
        Sleep(15);
        for (int i = 0; i < 256; i++) result |= GetAsyncKeyState(i);
    } while (!result);
}