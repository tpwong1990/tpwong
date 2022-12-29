#include "helpers.h"
#include <stdio.h>

int sobel_gx (int hegiht, int width, RGBTRIPLE image[height][width]);

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

    //Blur the image (handle for height != 0 && height != height)
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            long temp_R = 0;
            long temp_G = 0;
            long temp_B = 0;
            int ave_counter = 0;
            //average neighboring pixels
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    // up-left corners
                    if (i == 0 && j == 0)
                    {
                        if (((k == 0 && l == 0) || (k == 0 && l == 1)) || ((k == 1 && l == 0) || (k == 1 && l == 1)))
                        {
                            temp_R = temp_R + image[i + k][j + l].rgbtRed;
                            temp_G = temp_G + image[i + k][j + l].rgbtGreen;
                            temp_B = temp_B + image[i + k][j + l].rgbtBlue;
                            ave_counter++;
                        }
                    }
                    // up-right corners
                    if (i == 0 && j == width -1)
                    {
                        if (((k == -1 && l == 0) || (k == -1 && l == 1)) || ((k == 0 && l == 0) || (k == 0 && l == 1)))
                        {
                            temp_R = temp_R + image[i + k][j + l].rgbtRed;
                            temp_G = temp_G + image[i + k][j + l].rgbtGreen;
                            temp_B = temp_B + image[i + k][j + l].rgbtBlue;
                            ave_counter++;
                        }
                    }
                    //lower-left corners
                    if (i == height - 1 && j == 0)
                    {
                        if (((k == -1 && l == 0) || (k == -1 && l == 1)) || ((k == 0 && l == 0) || (k == 0 && l == 1)))
                        {
                            temp_R = temp_R + image[i + k][j + l].rgbtRed;
                            temp_G = temp_G + image[i + k][j + l].rgbtGreen;
                            temp_B = temp_B + image[i + k][j + l].rgbtBlue;
                            ave_counter++;
                        }
                    }
                    //lower-right corners
                    if (i == height - 1 && j == width - 1)
                    {
                        if (((k == -1 && l == -1) || (k == -1 && l == 0)) || ((k == 0 && l == -1) || (k == 0 && l == 0)))
                        {
                            temp_R = temp_R + image[i + k][j + l].rgbtRed;
                            temp_G = temp_G + image[i + k][j + l].rgbtGreen;
                            temp_B = temp_B + image[i + k][j + l].rgbtBlue;
                            ave_counter++;
                        }
                    }
                    //upper edge
                    if (i == 0 && j != 0 && j != width -1)
                    {
                        if (k != -1)
                        {
                            temp_R = temp_R + image[i + k][j + l].rgbtRed;
                            temp_G = temp_G + image[i + k][j + l].rgbtGreen;
                            temp_B = temp_B + image[i + k][j + l].rgbtBlue;
                            ave_counter++;
                        }
                    }
                    //lower edge
                    if (i == height - 1 && j != 0 && j != width -1)
                    {
                        if (k != 1)
                        {
                            temp_R = temp_R + image[i + k][j + l].rgbtRed;
                            temp_G = temp_G + image[i + k][j + l].rgbtGreen;
                            temp_B = temp_B + image[i + k][j + l].rgbtBlue;
                            ave_counter++;
                        }
                    }
                    //left edge
                    if (j == 0 && i != 0 && i != height - 1)
                    {
                        if (l != -1)
                        {
                            temp_R = temp_R + image[i + k][j + l].rgbtRed;
                            temp_G = temp_G + image[i + k][j + l].rgbtGreen;
                            temp_B = temp_B + image[i + k][j + l].rgbtBlue;
                            ave_counter++;
                        }
                    }
                    //right edge
                    if (j == width - 1 && i != 0 && i != height - 1)
                    {
                        if (l != 1)
                        {
                            temp_R = temp_R + image[i + k][j + l].rgbtRed;
                            temp_G = temp_G + image[i + k][j + l].rgbtGreen;
                            temp_B = temp_B + image[i + k][j + l].rgbtBlue;
                            ave_counter++;
                        }
                    }
                    //middle
                    if ((i > 0 && i < height -1) && (j > 0 && j < width - 1))
                    {
                        temp_R = temp_R + image[i + k][j + l].rgbtRed;
                        temp_G = temp_G + image[i + k][j + l].rgbtGreen;
                        temp_B = temp_B + image[i + k][j + l].rgbtBlue;
                        ave_counter++;
                    }
                }
            }
            //assgin the averaged value to image_dump
            dump_R[i][j] = temp_R / ave_counter;
            dump_G[i][j] = temp_G / ave_counter;
            dump_B[i][j] = temp_B / ave_counter;
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

int sobel_gx (int hegiht, int width, RGBTRIPLE image[height][width])
{
    //assign Gx kernels
    const int GX[2][2];
    GX[0] = {-1, 0, 1};
    GX[1] = {-2, 0, 2};
    GX[3] = {-1, 0 ,1};
    long temp_R = 0;
    long temp_G = 0;
    long temp_B = 0;
    for (int i = -1; i <= 1; i++)
    {
        for int j = -1; j <= 1; j++
        {
            temp = temp + GX[i + 1][j + 1]*image[height + i][width + j].rgbtRed
        }
    }
}