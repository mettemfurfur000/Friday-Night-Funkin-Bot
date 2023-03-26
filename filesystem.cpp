#include "binn.h"
#include "binn.c"
#include "structures.h"
#include <string>
#include <stdio.h>

void read_file_and_print(char *filename)
{
    char *buffer = 0;
    long length;
    FILE *f = fopen(filename, "rb");

    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = (char*)malloc(length);
        if (buffer)
        {
            fread(buffer, 1, length, f);
        }
        fclose(f);
    }

    if (buffer)
    {
        printf("%s\n",buffer);
    }

    delete[] buffer;
}

int save_arrow_state(arrow &a, int index)
{
    binn *obj;
    FILE *pFile;

    string filename = "arrowData" + to_string(index) + ".bin";

    // create a new object
    obj = binn_object();

    // add values to it
    binn_object_set_int32(obj, "color", a.arrow_color);
    binn_object_set_int32(obj, "x", a.arrow_pos.x);
    binn_object_set_int32(obj, "y", a.arrow_pos.y);
    binn_object_set_int16(obj, "key", a.associated_key);

    printf("saving arrow, data:[%x,%d,%d,%d]\n", a.arrow_color, a.arrow_pos.x, a.arrow_pos.y, a.associated_key);

    pFile = fopen(filename.c_str(), "wb");

    if (!pFile)
        return 1; // error with file

    fwrite(binn_ptr(obj), 1, binn_size(obj), pFile);
    // close arrowData file
    fclose(pFile);
    // release the object
    binn_free(obj);
    return 0;
}

int load_arrow_state(arrow &a, int index)
{
    binn *obj;
    FILE *pFile;

    string filename = "arrowData" + to_string(index) + ".bin";

    pFile = fopen(filename.c_str(), "rb");

    if (!pFile)
        return 1; // error with file

    // create a new object
    obj = binn_object();

    fread(obj, 1, sizeof(arrow), pFile);

    // add values to it

    a.arrow_color = binn_object_int32(obj, "color");
    a.arrow_pos.x = binn_object_int32(obj, "x");
    a.arrow_pos.y = binn_object_int32(obj, "y");
    a.associated_key = binn_object_int16(obj, "key");

    // close arrowData file
    fclose(pFile);
    // release the object
    binn_free(obj);

    printf("loaded arrow, data:[%x,%d,%d,%d]\n", a.arrow_color, a.arrow_pos.x, a.arrow_pos.y, a.associated_key);
    return 0;
}

void load_arrows(arrow *ar, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (load_arrow_state(ar[i], i))
            printf("Error loading arrow %d...\n", i);
    }
}

void save_arrows(arrow *ar, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (save_arrow_state(ar[i], i))
            printf("Error saving arrow %d...\n", i);
    }
}