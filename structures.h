#include <windows.h>

#ifndef FNF_B_STRUCT_H
#define FNF_B_STRUCT_H

struct position_2d
{
    int x, y;
};

struct arrow
{
    COLORREF arrow_color;
    position_2d arrow_pos;
    WORD associated_key;
};

#endif