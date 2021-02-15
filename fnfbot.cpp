#include <windows.h>
#include<thread>
#include <iostream>
#include <tchar.h>
void cheats() {
    for (;;) {
        COLORREF color;
        int red, green, blue;
        HDC hDC = GetDC(NULL);
        color = GetPixel(hDC, 1458, 170);
        /*
       color = GetPixel(hDC, 1183, 109);
       */
        red = GetRValue(color);
        green = GetGValue(color);
        blue = GetBValue(color);
        if (red == 194 && green == 75 && blue == 153 || red == 170 && green == 110 && blue == 161/*64*/) {

            INPUT ip;
            //255,210,212
             // Pause for 5 seconds.

             // Set up a generic keyboard event.
            ip.type = INPUT_KEYBOARD;
            ip.ki.wScan = 0; // hardware scan code for key
            ip.ki.time = 0;
            ip.ki.dwExtraInfo = 0;

            // Press the "A" key
            ip.ki.wVk = 0x25; // virtual-key code for the "a" key
            ip.ki.dwFlags = 0; // 0 for key press
            SendInput(1, &ip, sizeof(INPUT));
            Sleep(20);
            ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
            SendInput(1, &ip, sizeof(INPUT));
        };
        color = GetPixel(hDC, 1918, 195);
        /*
       color = GetPixel(hDC, 1183, 109);
       */
        red = GetRValue(color);
        green = GetGValue(color);
        blue = GetBValue(color);

        if (red == 18 && green == 250 && blue == 5/*64*/ || red == 37 && green == 236 && blue == 32) {

            INPUT ip;
            //255,210,212
             // Pause for 5 seconds.

             // Set up a generic keyboard event.
            ip.type = INPUT_KEYBOARD;
            ip.ki.wScan = 0; // hardware scan code for key
            ip.ki.time = 0;
            ip.ki.dwExtraInfo = 0;

            // Press the "A" key
            ip.ki.wVk = 0x26; // virtual-key code for the "a" key
            ip.ki.dwFlags = 0; // 0 for key press
            SendInput(1, &ip, sizeof(INPUT));
            Sleep(20);
            ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
            SendInput(1, &ip, sizeof(INPUT));
        };
        color = GetPixel(hDC, 1700, 195);
        /*
       color = GetPixel(hDC, 1183, 109);
       */
        red = GetRValue(color);
        green = GetGValue(color);
        blue = GetBValue(color);
        if (red == 0 && green == 255 && blue == 255/*64*/ || red == 54 && green == 218 && blue == 222) {

            INPUT ip;
            //255,210,212
             // Pause for 5 seconds.

             // Set up a generic keyboard event.
            ip.type = INPUT_KEYBOARD;
            ip.ki.wScan = 0; // hardware scan code for key
            ip.ki.time = 0;
            ip.ki.dwExtraInfo = 0;

            // Press the "A" key
            ip.ki.wVk = 0x28; // virtual-key code for the "a" key
            ip.ki.dwFlags = 0; // 0 for key press
            SendInput(1, &ip, sizeof(INPUT));
            Sleep(20);
            ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
            SendInput(1, &ip, sizeof(INPUT));
        };
        //FOURTH ONE EEIOOEEOEOEOEO
        color = GetPixel(hDC, 2099, 149);
        /*
       color = GetPixel(hDC, 1183, 109);
       */
        red = GetRValue(color);
        green = GetGValue(color);
        blue = GetBValue(color);

        if (red == 249 && green == 57 && blue == 63/*64*/ || red == 101 && green == 16 && blue == 56/*64*/ || red == 203 && green == 99 && blue == 107/*64*/) {

            INPUT ip;
            //255,210,212
             // Pause for 5 seconds.

             // Set up a generic keyboard event.
            ip.type = INPUT_KEYBOARD;
            ip.ki.wScan = 0; // hardware scan code for key
            ip.ki.time = 0;
            ip.ki.dwExtraInfo = 0;

            // Press the "A" key
            ip.ki.wVk = 0x27; // virtual-key code for the "a" key
            ip.ki.dwFlags = 0; // 0 for key press
            SendInput(1, &ip, sizeof(INPUT));
            Sleep(20);
            ip.ki.dwFlags = KEYEVENTF_KEYUP; // KEYEVENTF_KEYUP for key release
            SendInput(1, &ip, sizeof(INPUT));
        };
        /* purple:
        1183
101
*/
        Sleep(0);
        ReleaseDC(NULL, hDC);
    }

}
int x;
int y;
using namespace std;
void GetCursorw() {
    POINT cursorPos;
    GetCursorPos(&cursorPos);
    int y;
    int x;
    x = cursorPos.x;
    y = cursorPos.y;
    Sleep(50);

}

int main() {

    cout << "FNF cheats have started. make sure to have the game in full window mode.";
cheats();
    cout << "ERROR. RELOAD THE PROGRAM NOW.";
}
