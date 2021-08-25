#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Grab the pixel at coordinate x, y:
            RGBTRIPLE *p = &image[y][x];
            // Compute the average of the red, green, and blue values
            BYTE avg = round((float) (p->rgbtRed + p->rgbtGreen + p->rgbtBlue) / 3);
            // Set the red, green, and blue values to the same average
            p->rgbtRed = avg;
            p->rgbtGreen = avg;
            p->rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // To convert an image to sepia, the red, green, and blue values are
    // converted to new values based on the original values, using equations
    // like so:
    // new_R = A * orig_R + B * orig_G + C * orig_B
    // new_G = D * orig_R + E * orig_G + F * orig_B
    // new_B = G * orig_R + H * orig_G + I * orig_B
    // where A through I are constants.
    // These arrays define the constants for each color.
    float sepia[3][3] =
    {
        {0.393, 0.769, 0.189},
        {0.349, 0.686, 0.168},
        {0.272, 0.534, 0.131}
    };

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Get our original values:
            BYTE orig[3] =
            {
                image[y][x].rgbtRed,
                image[y][x].rgbtGreen,
                image[y][x].rgbtBlue
            };

            // Grab our pixel:
            BYTE *p[3] =
            {
                &image[y][x].rgbtRed,
                &image[y][x].rgbtGreen,
                &image[y][x].rgbtBlue
            };

            // Run sepia filter
            for (int i = 0; i < 3; i++)
            {
                // Declare a float for our equation
                float p_sum = 0.0;
                for (int j = 0; j < 3; j++)
                {
                    p_sum += sepia[i][j] * orig[j];
                }
                // For overflows
                if (p_sum > 255)
                {
                    *p[i] = (BYTE) 255;
                }
                else
                {
                    *p[i] = (BYTE) round(p_sum);
                }
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        // Flip it and reverse it
        for (int x = 0; x < width / 2; x++)
        {
            RGBTRIPLE orig = image[y][x];
            image[y][x] = image[y][width - x - 1];
            image[y][width - x - 1] = orig;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Make a copy of the original image.
    RGBTRIPLE orig_img[height][width];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            orig_img[y][x] = image[y][x];
        }
    }

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Get the pixel's neighbors
            RGBTRIPLE neighbors[9];
            int count = 0;
            for (int x_blur = -1; x_blur <= 1; x_blur++)
            {
                for (int y_blur = -1; y_blur <= 1; y_blur++)
                {
                    if (x + x_blur >= 0 && x + x_blur < width)
                    {
                        if (y + y_blur >= 0 && y + y_blur < height)
                        {
                            neighbors[count] = orig_img[y + y_blur][x + x_blur];
                            count++;
                        }
                    }
                }
            }
            // Average the neighbors
            int r_sum = 0, g_sum = 0, b_sum = 0;
            for (int i = 0; i < count; i++)
            {
                r_sum += neighbors[i].rgbtRed;
                g_sum += neighbors[i].rgbtGreen;
                b_sum += neighbors[i].rgbtBlue;
            }
            image[y][x].rgbtRed = round((float) r_sum / count);
            image[y][x].rgbtGreen = round((float) g_sum / count);
            image[y][x].rgbtBlue = round((float) b_sum / count);
        }
    }
    return;
}
