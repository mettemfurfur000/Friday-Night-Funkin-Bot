#include "settings.cpp"
#include <iostream>

using namespace std;

int main()
{
    load_arrows(arrows4,4);
    int delay = (int)(1000 / cps);
    while(!close_app_NOW)
    {
        check_buttons();
        if(work) scan_and_do(arrows4,possible_gap,delay_press,delay_release);
        Sleep(delay);
    }
    save_arrows(arrows4,4);
}
