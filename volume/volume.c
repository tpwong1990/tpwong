// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef uint8_t BYTE;
typedef int16_t BYTE2;

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    //Copy header from input file to output file
    BYTE temp[HEADER_SIZE];
    fread(temp, 1, HEADER_SIZE, input);
    fwrite(temp, 1, HEADER_SIZE, output);

    //Read samples from input file and write updated data to output file
    BYTE2 sample[1];
    while (fread(sample, sizeof(BYTE2), 1, input) != 0)
    {
        sample[0] = sample[0] * factor;
        fwrite(sample, sizeof(BYTE2), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
    return 0;
}
