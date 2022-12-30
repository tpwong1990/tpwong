#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;
bool find_jpeg(BYTE x_1, BYTE x_2, BYTE x_3);

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
    //Read file and find JPEG signatures
    const int FAT_size = 512;
    int block_count = 0
    BYTE temp;
    read_count = 0;
    while (fread(temp, 1, FAT_size, image_in) == FAT_size)
    {
        read_count++;
        if (read_count == 1)
        {
            BYTE temp_1st = temp;
        }
        if (read_count == 2)
        {
            BYTE temp_2nd = temp;
        }
        if (read_count == 3)
        {
            BYTE temp_3rd = temp;
        }
        //read first 3 bytes
        if (find_jpeg(temp_1st, temp_2nd, temp_3rd) == true)
        {
            //allocate memory for image
            *image_out = malloc();
        }
        else
        {
            break;
            return 1;
        }

    }
    fclose(inptr);
}

bool find_jpeg(BYTE x_1, BYTE x_2, BYTE x_3)
{
    if (x_1 == 255 && x_2 == 216 && x_3 == 255)
    {
        return true;
    }
    else
    {
        return false;
    }
}