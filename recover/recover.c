#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;
const int FAT_size = 512;
int find_jpeg(BYTE x_1, BYTE x_2, BYTE x_3, BYTE x_4);
void extract_image(int count, BYTE temp[FAT_size]);

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

    int jpeg_count = 0;
    int writing_status = 0;

    //allocate memory for buffer
    BYTE *buffer = malloc(FAT_size);

    //Read file and find JPEG signatures
    while (fread(buffer, 1, FAT_size, image_in) == FAT_size)
    {
        int jpeg_found = find_jpeg(buffer[0], buffer[1], buffer[2], buffer[3]);
        //check if it is jpeg
        if ((jpeg_found == 1) && writing_status == 0)
        {
            jpeg_count++;
            extract_image(jpeg_count, buffer);
            writing_status = 1;
        }
        else
        {
            if ((jpeg_found == 1) && writing_status == 1)
            {
                jpeg_count++;
                extract_image(jpeg_count, buffer);
                writing_status = 1;
            }
            else
            {
                if ((jpeg_found == 0) && writing_status == 1)
                {
                    extract_image(jpeg_count, buffer);
                    writing_status = 1;
                }
            }
        }
    }
    free(buffer);
    fclose(image_in);
}

int find_jpeg(BYTE x_1, BYTE x_2, BYTE x_3, BYTE x_4)
{
    if ((x_1 == 0xff && x_2 == 0xd8 && x_3 == 0xff) && ((x_4 & 0xf0) == 0xe0))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void extract_image(int count, BYTE temp[FAT_size])
{
    //open file for jpeg
    char *fout = malloc(8);
    sprintf(fout, "%03i.jpg", count - 1);
    FILE *image_out = fopen(fout, "a");

    //write data to fout
    fwrite(temp, 1, FAT_size, image_out);
    free(fout);
    fclose(image_out);
}