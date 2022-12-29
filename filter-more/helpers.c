#include "helpers.h"

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
    //allocate dump image memory
    RGBTRIPLE(*image_dump)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    //Blur the image
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            BYTE temp_R = 0;
            BYTE temp_G = 0;
            BYTE temp_B = 0;
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
            image_dump[i][j].rgbtRed = temp_R / 9;
            image_dump[i][j].rgbtGreen = temp_G / 9;
            image_dump[i][j].rgbtBlue = temp_B / 9;
        }
    }

    // paste image_dump to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_dump[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
