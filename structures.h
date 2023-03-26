#include <windows.h>

#ifndef FNF_B_STRUCT_H
#define FNF_B_STRUCT_H

struct color
{
    BYTE r;
    BYTE g;
    BYTE b;
};

struct position_2d
{
    int x, y;
};

struct arrow
{
    color arrow_color;
    position_2d arrow_pos;
    WORD associated_key;
};

#endif