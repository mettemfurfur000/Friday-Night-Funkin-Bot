#include "structures.h"
#include "functions.cpp"
#include "filesystem.cpp"

WORD bot_toggle_button = VK_INSERT;
WORD key_change_arrows = VK_HOME;
WORD exit_key = VK_DELETE;

arrow arrows4[4];

bool work = false;
int cps = 30; // clicks per second /checks per second
bool close_app_NOW = false;

int possible_gap = 5;
int delay_press = 10;
int delay_release = 5;

void check_buttons()
{
    if(GetAsyncKeyState(exit_key) & 1)
    {
        close_app_NOW = true;
        printf("Bye bye! <3\n");
    }

    if (GetAsyncKeyState(bot_toggle_button) & 1)
    {
        work = !work;
        printf("Bot state: %s\n", work ? "ON" : "OFF");
    }

    if (GetAsyncKeyState(key_change_arrows) & 1)
    {
        read_file_and_print("tutor.txt");

        while(!(GetAsyncKeyState(VK_END) & 1)) {Sleep(35);}

        GetCursorPos(NULL);
        GetAsyncKeyState(VK_LBUTTON);
        for (int i = 0; i < 4; i++)
        {
            printf("Assigning %d arrow...\n", i);
            printf("Move the cursor and press the \"End\" key to set Position\n");
            set_arrow_pos(arrows4[i]);
            printf("Move the cursor on the arrow with needed color and press the \"End\" key to set Arrow Color\n");
            set_arrow_color_from_monitor(arrows4[i]);
            printf("Press key to bind this Arrow\n");
            set_associated_key(arrows4[i]);
            printf("Arrow assigned! data:[%x,%d,%d,%d]\n",
            arrows4[i].arrow_color,
            arrows4[i].arrow_pos.x,
            arrows4[i].arrow_pos.y,
            arrows4[i].associated_key);
        }
    }
}