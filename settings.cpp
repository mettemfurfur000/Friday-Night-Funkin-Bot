#include "structures.h"
#include "functions.cpp"
#include "filesystem.cpp"

WORD bot_toggle_button = VK_INSERT;
WORD key_change_arrows = VK_HOME;
WORD exit_key = VK_DELETE;

arrow arrows4[4];

bool work = false;
int cps = 200; // clicks per second /checks per second
bool close_app_NOW = false;

int possible_gap = 85;
int delay_press = 1;
int delay_release = 1;

void save_settings()
{
    binn *obj = binn_object();

    binn_object_set_int32(obj, "cps", cps);
    binn_object_set_int32(obj, "possible_gap", possible_gap);
    binn_object_set_int32(obj, "delay_press", delay_press);
    binn_object_set_int32(obj, "delay_release", delay_release);

    write_binn_object(obj, "settings.bin");

    binn_free(obj);
}

void load_settings()
{
    binn *obj = binn_object();

    read_binn_object(obj, "settings.bin");

    cps = binn_object_int32(obj, "cps");
    possible_gap = binn_object_int32(obj, "possible_gap");
    delay_press = binn_object_int32(obj, "delay_press");
    delay_release = binn_object_int32(obj, "delay_release");

    binn_free(obj);
}

void check_buttons()
{
    if (GetAsyncKeyState(exit_key) & 1)
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

        while (!(GetAsyncKeyState(VK_END) & 1))
        {
            if (GetAsyncKeyState(VK_DELETE) & 1)
            {
                printf("Exited\n");
                return;
            }
            Sleep(35);
        }

        GetCursorPos(NULL);
        GetAsyncKeyState(VK_LBUTTON);
        for (int i = 0; i < 4; i++)
        {
            printf("Assigning %d arrow...\n", i);
            printf("Move the cursor and press the \"End\" key to set Position\n");
            set_arrow_pos(arrows4[i]);
            printf("Move the cursor on the arrow with needed color and press the \"End\" key to set Arrow Color\n");
            set_arrow_color_from_monitor(arrows4[i]);
            // printf("Press key to bind this Arrow(single key!)\n");
            // set_associated_key(arrows4[i]); //newermind
            print_info(arrows4[i]);
        }

        arrows4[0].associated_key = VK_LEFT;
        arrows4[1].associated_key = VK_DOWN;
        arrows4[2].associated_key = VK_UP;
        arrows4[3].associated_key = VK_RIGHT;
    }
}

int exists(const char *fname)
{
    FILE *file;
    if ((file = fopen(fname, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

bool check_debug_mode()
{
    return exists("debug.bin");
}