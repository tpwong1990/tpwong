#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int sobel(int height, int width, RGBTRIPLE image[height][width], int cur_x, int cur_y, char c);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //take ave of RGB value
            double temp = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            image[i][j].rgbtBlue = (BYTE) round(temp);
            image[i][j].rgbtGreen = (BYTE) round(temp);
            image[i][j].rgbtRed = (BYTE) round(temp);
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
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][width - 1 - j].rgbtRed = temp_R;
            image[i][width - 1 - j].rgbtGreen = temp_G;
            image[i][width - 1 - j].rgbtBlue = temp_B;
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
            double temp_R = 0;
            double temp_G = 0;
            double temp_B = 0;
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
                    if (i == 0 && j == width - 1)
                    {
                        if (((k == 1 && l == 0) || (k == 1 && l == -1)) || ((k == 0 && l == 0) || (k == 0 && l == -1)))
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
                    if (i == 0 && j != 0 && j != width - 1)
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
                    if (i == height - 1 && j != 0 && j != width - 1)
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
                    if ((i > 0 && i < height - 1) && (j > 0 && j < width - 1))
                    {
                        temp_R = temp_R + image[i + k][j + l].rgbtRed;
                        temp_G = temp_G + image[i + k][j + l].rgbtGreen;
                        temp_B = temp_B + image[i + k][j + l].rgbtBlue;
                        ave_counter++;
                    }
                }
            }
            //assgin the averaged value to image_dump
            dump_R[i][j] = round(temp_R / (double) ave_counter);
            dump_G[i][j] = round(temp_G / (double) ave_counter);
            dump_B[i][j] = round(temp_B / (double) ave_counter);
        }
    }

    // paste image_dump to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
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
    // Allocate memory for image with total height from (-1 to height) and width from (-1 to width)
    RGBTRIPLE(*image_dump)[width + 2] = calloc(height + 2, (width + 2) * sizeof(RGBTRIPLE));

    //Assign black value to the edge of the image_dump
    for (int l = 0; l <= width + 1; l++)
    {
        image_dump[0][l].rgbtRed = 0;
        image_dump[0][l].rgbtGreen = 0;
        image_dump[0][l].rgbtBlue = 0;
        image_dump[height + 1][l].rgbtRed = 0;
        image_dump[height + 1][l].rgbtGreen = 0;
        image_dump[height + 1][l].rgbtBlue = 0;
    }
    for (int k = 0; k <= height + 1; k++)
    {
        image_dump[k][0].rgbtRed = 0;
        image_dump[k][0].rgbtGreen = 0;
        image_dump[k][0].rgbtBlue = 0;
        image_dump[k][width + 1].rgbtRed = 0;
        image_dump[k][width + 1].rgbtGreen = 0;
        image_dump[k][width + 1].rgbtBlue = 0;
    }
    // put the ori image into image_dump
    for (int k = 1; k <= height; k++)
    {
        for (int l = 1; l <= width; l++)
        {
            image_dump[k][l] = image[k - 1][l - 1];
        }
    }
    // calucate the edge value
    for (int k = 1; k <= height; k++)
    {
        for (int l = 1; l <= width; l++)
        {
            image[k - 1][l - 1].rgbtRed = sobel(height + 2, width + 2, image_dump, k, l, 'r');
            image[k - 1][l - 1].rgbtGreen = sobel(height + 2, width + 2, image_dump, k, l, 'g');
            image[k - 1][l - 1].rgbtBlue = sobel(height + 2, width + 2, image_dump, k, l, 'b');
        }
    }
    free(image_dump);
    return;
}

int sobel(int height, int width, RGBTRIPLE image[height][width], int cur_x, int cur_y, char c)
{
    //assign Gx kernels
    const int GX[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    //assgin Gy kernels
    const int GY[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    long temp_Rx = 0;
    long temp_Gx = 0;
    long temp_Bx = 0;
    long temp_Ry = 0;
    long temp_Gy = 0;
    long temp_By = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (c == 'r')
            {
                temp_Rx = temp_Rx + GX[i + 1][j + 1] * image[cur_x + i][cur_y + j].rgbtRed;
                temp_Ry = temp_Ry + GY[i + 1][j + 1] * image[cur_x + i][cur_y + j].rgbtRed;
            }
            if (c == 'g')
            {
                temp_Gx = temp_Gx + GX[i + 1][j + 1] * image[cur_x + i][cur_y + j].rgbtGreen;
                temp_Gy = temp_Gy + GY[i + 1][j + 1] * image[cur_x + i][cur_y + j].rgbtGreen;
            }
            if (c == 'b')
            {
                temp_Bx = temp_Bx + GX[i + 1][j + 1] * image[cur_x + i][cur_y + j].rgbtBlue;
                temp_By = temp_By + GY[i + 1][j + 1] * image[cur_x + i][cur_y + j].rgbtBlue;
            }
        }
    }
    double result;
    switch (c)
    {
        case 'r':
            result = sqrt(temp_Rx * temp_Rx + temp_Ry * temp_Ry);
            if (result > 255)
            {
                result = 255;
            }
            break;

        case 'g':
            result = sqrt(temp_Gx * temp_Gx + temp_Gy * temp_Gy);
            if (result > 255)
            {
                result = 255;
            }
            break;

        case 'b':
            result = sqrt(temp_Bx * temp_Bx + temp_By * temp_By);
            if (result > 255)
            {
                result = 255;
            }
            break;
    }
    return round(result);
}