#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// static int copy_image(int height, int width, RGBTRIPLE dest_image[height][width], RGBTRIPLE src_image[height][width]);

/*******************************************************************
 * @brief Convert image to grayscale
 *        red, green, and blue values must have the same value
 *        to ensure same brightness, find the average
 * 
 * @param height 
 * @param width 
 * @param image 
 ******************************************************************/
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    /* for every pixel */
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            /* calculate the average*/
            float average = (
                                image[h][w].rgbtBlue  +
                                image[h][w].rgbtGreen +
                                image[h][w].rgbtRed
                            ) / 3.0;
            /* set every RGB to that average so that it retains the brightness */
            /* use round from math.h because the pixels are unsigned char = 1B numbers */
            image[h][w].rgbtBlue  = round(average);   
            image[h][w].rgbtGreen = round(average);   
            image[h][w].rgbtRed   = round(average);  
        }
    }
    return;
}

/*******************************************************************
 * @brief Reflect image horizontally
 *        any pixels on the left side of the image should end up on the right, and vice versa
 * 
 * @param height 
 * @param width 
 * @param image 
 ******************************************************************/
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    /* for every row in the image */
    for (int h = 0; h < height; h++)
    {
        /* for the first left half of the image */
        for (int w = 0; w < width / 2; w++)
        {
            /* swap the left with the right pixel */
            RGBTRIPLE temp = image[h][w];
            image[h][w] = image[h][width - w - 1];
            image[h][width - w - 1] = temp;
        }
    }
    return;
}

/*******************************************************************
 * @brief Blur image using box blur
 *        for each color value, average the color values
 *        of neighboring pixels.
 * 
 * @param height 
 * @param width 
 * @param image 
 ******************************************************************/
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    /* create a temporary image, allocate and initialize */
    /* this is the way to define, allocate and initialize a 2D array */
    RGBTRIPLE(*tempImage)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (tempImage == NULL)
    {
        fprintf(stderr, ">>\tFailed to allocate memory\n");
        return;
    }
    
    /* apply box blur algorithm */
    for (int h = 0; h < height; h++)
    {
        /* for every pixel */
        for (int w = 0; w < width; w++)
        {
            /* needed for the calculation of the average in the end */
            int numPixels = 0;
            int red = 0, green = 0, blue = 0;
            
            /* for every neighbouring pixel in X and Y axis */
            for (int i = -1; i <= 1; i++) // 3 times
            {
                for (int j = -1; j <= 1; j++) // 3 times
                {
                    /* if it is within the image and can be taken into account */
                    if (h + i >= 0 && h + i < height && w + j >= 0 && w + j < width)
                    {
                        red   += image[h + i][w + j].rgbtRed;
                        green += image[h + i][w + j].rgbtGreen;
                        blue  += image[h + i][w + j].rgbtBlue;
                        numPixels++;
                    }
                }
            }
            
            /* average color values of neighboring pixels */
            tempImage[h][w].rgbtRed   = round((float) red   / numPixels);
            tempImage[h][w].rgbtGreen = round((float) green / numPixels);
            tempImage[h][w].rgbtBlue  = round((float) blue  / numPixels);
        }
    }
    
    /* replace image with box-blurred image */
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = tempImage[h][w];
        }
    }
    
    free(tempImage);
}

/*******************************************************************
 * @brief Detect edges by applying the Sobel Operator to the image
 * 
 * @param height 
 * @param width 
 * @param image 
 ******************************************************************/
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*tempImage)[width] = calloc(height, (width) * sizeof(RGBTRIPLE));

    /* set to black */
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempImage[i][j].rgbtRed = 0;
            tempImage[i][j].rgbtGreen = 0;
            tempImage[i][j].rgbtBlue = 0;
        }
    }

    /* create a copy temporary image */
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempImage[i][j] = image[i][j];
        }
    }

    /* define the Gx and Gy kernels */
    int kernel_x[3][3] =
    {
        {-1,  0,  1},
        {-2,  0,  2},
        {-1,  0,  1}
    };

    int kernel_y[3][3] =
    {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2, 1 }
    };

    /* apply the Sobel operator to each pixel in the image */
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            /* define x and y gradient for the pixel */
            long long gx_red   = 0, gy_red   = 0;
            long long gx_green = 0, gy_green = 0;
            long long gx_blue  = 0, gy_blue  = 0;

            /* for the nine pixels surrounding the pixel in question */
            for (int pi = -1; pi <=1; pi++)
            {
                for (int pj = -1; pj <= 1; pj++)
                {
                    /* handle the edges and the corners */
                    if (
                        (i == 0 && pi == -1)         || // or statements
                        (i == height - 1 && pi == 1) ||
                        (j == 0 && pj == -1)         ||
                        (j == width - 1 && pj == 1)
                    )
                    {
                        continue;
                    }

                    /* multiply each value by the corresponding value in the G kernel */
                    gx_red   += kernel_x[pi + 1][pj + 1] * tempImage[i + pi][j + pj].rgbtRed;
                    gy_red   += kernel_y[pi + 1][pj + 1] * tempImage[i + pi][j + pj].rgbtRed;
                    gx_green += kernel_x[pi + 1][pj + 1] * tempImage[i + pi][j + pj].rgbtGreen;
                    gy_green += kernel_y[pi + 1][pj + 1] * tempImage[i + pi][j + pj].rgbtGreen;
                    gx_blue  += kernel_x[pi + 1][pj + 1] * tempImage[i + pi][j + pj].rgbtBlue;
                    gy_blue  += kernel_y[pi + 1][pj + 1] * tempImage[i + pi][j + pj].rgbtBlue;
                }
            }

            /* calculate the magnitude */
            double g_red   = round(sqrt(gx_red   * gx_red   + gy_red   * gy_red));
            double g_green = round(sqrt(gx_green * gx_green + gy_green * gy_green));
            double g_blue  = round(sqrt(gx_blue  * gx_blue  + gy_blue  * gy_blue));

            /* set the maximum allowed to 255 */
            g_red   = g_red   > 255 ? 255 : g_red;
            g_green = g_green > 255 ? 255 : g_green;
            g_blue  = g_blue  > 255 ? 255 : g_blue;

            /* finally, copy to the original image */
            image[i][j].rgbtRed   = (int)g_red;
            image[i][j].rgbtGreen = (int)g_green;
            image[i][j].rgbtBlue  = (int)g_blue;
        }
    }
    /* free the memory allocation */
    free(tempImage);
}
