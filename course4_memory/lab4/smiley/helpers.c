#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            /* if the pixel of the image was previously black */
            if (image[h][w].rgbtBlue  == 0x00 ||
                image[h][w].rgbtGreen == 0x00 ||
                image[h][w].rgbtRed   == 0x00)
            {
                /* make it coral */
                image[h][w].rgbtRed   = 0xff;
                image[h][w].rgbtGreen = 0x7f;
                image[h][w].rgbtBlue  = 0x50;
            }
            /* else if it was white */
            else
            {
                /* this color makes the backround match my VSCode dark mode */
                image[h][w].rgbtRed   = 0x1f;
                image[h][w].rgbtGreen = 0x1f;
                image[h][w].rgbtBlue  = 0x1f;
            }
        }
    }
}
