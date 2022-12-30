#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
int find_jpeg(BYTE x_1, BYTE x_2, BYTE x_3, BYTE x_4);

int main(int argc, char *argv[])
{
    //check command line - no. of command line
    if (argc != 2)
    {
        printf("Usage: ./name of a forensic image\n");
        return 1;
    }
    char *image_name = argv[1];
    //open file
    FILE *image_in = fopen(image_name, "r");
    if (image_in == NULL)
    {
        printf("Could not open %s.\n", image_name);
        return 1;
    }
    //record the size of input image
    long size_image_in = sizeof(&image_in);
    //Read file and find JPEG signatures
    const int FAT_size = 512;
    int block_count = 0;
    //while (status == 1)
    //{}
        int read_count = 0;
        //allocate memory for buffer
        BYTE *buffer = malloc(512);
        BYTE temp_1st;
        BYTE temp_2nd;
        BYTE temp_3rd;
        BYTE temp_4th;
        int status = 0;
    while (fread(buffer, 1, FAT_size, &image_in[block_count * FAT_size]) == FAT_size)
    {
        read_count++;
        if (read_count == 1)
        {
            temp_1st = buffer[0];
        }
        if (read_count == 2)
        {
            temp_2nd = buffer[1];
        }
        if (read_count == 3)
        {
            temp_3rd = buffer[2];
        }
        if (read_count == 4)
        {
            temp_4th = buffer[3];
        }
        //read first 4 bytes
        if (find_jpeg(temp_1st, temp_2nd, temp_3rd, temp_4th) == 0)
        {
            status = 1;
            //continue to read
        }
        else
        {
            free(buffer);
            break;
            return 1;
        }
    }
    block_count++;








    fclose(image_in);
}

int find_jpeg(BYTE x_1, BYTE x_2, BYTE x_3, BYTE x_4)
{
    if ((x_1 == 255 && x_2 == 216 && x_3 == 255) && (x_4 >= 224 && x_4 <= 239))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}