#include "structures.h"
#include "functions.cpp"
#include "filesystem.cpp"

WORD bot_toggle_button = VK_INSERT;
WORD key_change_arrows = VK_HOME;

arrow arrows4[4];

bool work = false;
int cps = 30; // clicks per second /checks per second

int possible_gap = 5;
int delay_press = 10;
int delay_release = 5;

void check_buttons()
{
    if (GetAsyncKeyState(bot_toggle_button) & 1)
    {
        work = !work;
        printf("Bot state: %s\n", work ? "ON" : "OFF");
    }

    if (GetAsyncKeyState(key_change_arrows) & 1)
    {
        GetCursorPos(NULL);
        GetAsyncKeyState(VK_LBUTTON);
        for (int i = 0; i < 4; i++)
        {
            printf("Assigning %d arrow...\n", i);
            set_arrow_pos(arrows4[i]);
            printf("Arrow[%d] = %d,%d\n", i, arrows4[i].arrow_pos.x, arrows4[i].arrow_pos.y);
        }
    }
}