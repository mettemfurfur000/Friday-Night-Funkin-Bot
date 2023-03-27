#include "binn.h"
#include "binn.c"
#include "structures.h"
#include <string>
#include <stdio.h>

void print_info(arrow &a)
{
    printf("[[%x%x%x],%d,%d,[%x]]\n",
           a.arrow_color.r,
           a.arrow_color.g,
           a.arrow_color.b,
           a.arrow_pos.x,
           a.arrow_pos.y,
           a.associated_key);
}

size_t sizeoffile(FILE *f)
{
    size_t l;
    fseek(f, 0, SEEK_END);
    l = ftell(f);
    fseek(f, 0, SEEK_SET);
    return l;
}

void read_binn_object(binn *obj, char *filename)
{
    FILE *f = fopen(filename, "rb");

    fread(obj, 1, sizeoffile(f), f);

    fclose(f);
}

void write_binn_object(binn *obj, char *filename)
{
    FILE *f = fopen(filename, "wb");

    fwrite(binn_ptr(obj), 1, binn_size(obj), f);

    fclose(f);
}

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
        buffer = (char *)malloc(length);
        if (buffer)
        {
            fread(buffer, 1, length, f);
        }
        fclose(f);
    }

    if (buffer)
    {
        printf("%s\n", buffer);
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
    binn_object_set_int8(obj, "r", a.arrow_color.r);
    binn_object_set_int8(obj, "g", a.arrow_color.g);
    binn_object_set_int8(obj, "b", a.arrow_color.b);

    binn_object_set_int32(obj, "x", a.arrow_pos.x);
    binn_object_set_int32(obj, "y", a.arrow_pos.y);
    binn_object_set_int16(obj, "key", a.associated_key);

    print_info(a);

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

    fread(obj, 1, sizeoffile(pFile), pFile);

    // add values to it

    a.arrow_color.r = binn_object_int8(obj, "r");
    a.arrow_color.g = binn_object_int8(obj, "g");
    a.arrow_color.b = binn_object_int8(obj, "b");

    a.arrow_pos.x = binn_object_int32(obj, "x");
    a.arrow_pos.y = binn_object_int32(obj, "y");
    a.associated_key = binn_object_int16(obj, "key");

    // close arrowData file
    fclose(pFile);
    // release the object
    binn_free(obj);

    print_info(a);
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