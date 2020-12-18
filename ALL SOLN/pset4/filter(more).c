#include "helpers.h"
#include <math.h>
#include <cs50.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];
            int average = round((pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed) / 3.0);
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = average;
        }
    }
    return;
}

void swap(RGBTRIPLE *pixel1, RGBTRIPLE *pixel2)
{
    RGBTRIPLE temp = *pixel1;
    *pixel1 = *pixel2;
    *pixel2 = temp;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j], &image[i][width - 1 - j]);
        }
    }
    return;
}

bool is_valid_pixel(int i, int j, int height, int width)
{
    return (i >= 0 && i < height && j >= 0 && j < width);
}

RGBTRIPLE blur_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int red_comp, green_comp, blue_comp;
    red_comp = green_comp = blue_comp = 0;
    int numOfValidPixel = 0;

    for (int temp_i = -1; temp_i <= 1; temp_i++)
    {
        for (int temp_j = -1; temp_j <= 1; temp_j++)
        {
            int new_i = i + temp_i;
            int new_j = j + temp_j;
            if (is_valid_pixel(new_i, new_j, height, width))
            {
                numOfValidPixel++;
                red_comp += image[new_i][new_j].rgbtRed;
                green_comp += image[new_i][new_j].rgbtGreen;
                blue_comp += image[new_i][new_j].rgbtBlue;
            }
        }
    }
    RGBTRIPLE blurred_pixel;
    blurred_pixel.rgbtRed = round((float)red_comp / numOfValidPixel);
    blurred_pixel.rgbtGreen = round((float)green_comp / numOfValidPixel);
    blurred_pixel.rgbtBlue = round((float)blue_comp / numOfValidPixel);
    return blurred_pixel;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_image[i][j] = blur_pixel(i, j, height, width, image);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
    return;
}

int cap(int value)
{
    return value < 255 ? value: 255;
}

RGBTRIPLE edged_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] = {{-1, 0, 1},{-2, 0, 2},{-1, 0, 1}};
    int red_valueX, green_valueX, blue_valueX;
    red_valueX = green_valueX = blue_valueX = 0;

    int red_valueY, green_valueY, blue_valueY;
    red_valueY = green_valueY = blue_valueY = 0;

    for (int temp_i = -1; temp_i <= 1; temp_i++)
    {
        for (int temp_j = -1; temp_j <= 1; temp_j++)
        {
            if (is_valid_pixel((i + temp_i),(j + temp_j), height, width))
            {
                int weightX = gx[temp_i + 1][temp_j + 1];
                red_valueX += weightX * image[temp_i + i][temp_j + j].rgbtRed;
                green_valueX += weightX * image[temp_i + i][temp_j + j].rgbtGreen;
                blue_valueX += weightX * image[temp_i + i][temp_j + j].rgbtBlue;

                int weightY = gx[temp_j + 1][temp_i + 1];
                red_valueY += weightY * image[temp_i + i][temp_j + j].rgbtRed;
                green_valueY += weightY * image[temp_i + i][temp_j + j].rgbtGreen;
                blue_valueY += weightY * image[temp_i + i][temp_j + j].rgbtBlue;
            }
        }
    }
    RGBTRIPLE pixel;
    pixel.rgbtRed = cap(round(sqrt(red_valueX * red_valueX + red_valueY * red_valueY)));
    pixel.rgbtGreen = cap(round(sqrt(green_valueX * green_valueX + green_valueY * green_valueY)));
    pixel.rgbtBlue = cap(round(sqrt(blue_valueX * blue_valueX + blue_valueY * blue_valueY)));
    return pixel;

}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_image[i][j] = edged_pixel(i, j, height, width, image);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
}
