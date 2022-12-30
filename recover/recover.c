#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

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

    const int FAT_size = 512;
    int block_count = 0;
    int jpeg_count = 0;
    int writing_status = 0;

    //allocate memory for buffer
    BYTE *buffer = malloc(512);
    //Read file and find JPEG signatures
    while (fread(buffer, 1, FAT_size, &image_in[block_count * FAT_size]) == FAT_size)
    {
        //check if it is jpeg
        if (find_jpeg(buffer[0], buffer[1], buffer[2], buffer[3]) == 0) || (writing_status == 1)
        {
            jpeg_count++;
            //continue to read
            //open file for jpeg
            string fout = NULL;
            sprintf(fout, "03%i.jpg", jpeg_count - 1);
            FILE *image_out = fopen(fout, "w");

            //write data to fout
            fwrite(buffer, 1, FAT_size, image_out);
            writing_status = 1;
        }
        else
        {
            free(buffer);
        }
        block_count++;
    }









    fclose(image_in);
}

int find_jpeg(BYTE x_1, BYTE x_2, BYTE x_3, BYTE x_4)
{
    if ((x_1 == 0xff && x_2 == 0xd8 && x_3 == 0xff) && ((x_4 & 0xf0) == 0xe0))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}