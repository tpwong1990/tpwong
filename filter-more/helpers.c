#include "helpers.h"
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //take ave of RGB value
            BYTE temp = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            image[i][j].rgbtBlue = temp;
            image[i][j].rgbtGreen = temp;
            image[i][j].rgbtRed = temp;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // flip the pixel horizontally
            BYTE temp_R = image[i][j].rgbtRed;
            BYTE temp_G = image[i][j].rgbtGreen;
            BYTE temp_B = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = image[i][width - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - j].rgbtBlue;
            image[i][width - j].rgbtRed = temp_R;
            image[i][width - j].rgbtGreen = temp_G;
            image[i][width - j].rgbtBlue = temp_B;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //allocate dump image 2d array
    BYTE dump_R[height][width];
    BYTE dump_G[height][width];
    BYTE dump_B[height][width];

    //Blur the image
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            BYTE temp_R = 0;
            BYTE temp_G = 0;
            BYTE temp_B = 0;
            printf("R: %i\n", image[i][j].rgbtRed);
            printf("G: %i\n", image[i][j].rgbtGreen);
            printf("B: %i\n", image[i][j].rgbtBlue);
            //average neighboring pixels
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    temp_R = temp_R + image[i + k][j + l].rgbtRed;
                    temp_G = temp_G + image[i + k][j + l].rgbtGreen;
                    temp_B = temp_B + image[i + k][j + l].rgbtBlue;
                }
            }
            //assgin the averaged value to image_dump
            dump_R[i][j] = temp_R / 10;
            dump_G[i][j] = temp_G / 10;
            dump_B[i][j] = temp_B / 10;
        }
    }

    // paste image_dump to image
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            image[i][j].rgbtRed = dump_R[i][j];
            image[i][j].rgbtGreen = dump_G[i][j];
            image[i][j].rgbtBlue = dump_B[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
