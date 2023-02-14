#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loops through each row
    for (int i = 0; i < height; i++)
    {
        // Loops through each column
        for (int j = 0; j < width; j++)
        {
            float averagecol = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            image[i][j].rgbtRed = round(averagecol);
            image[i][j].rgbtGreen = round(averagecol);
            image[i][j].rgbtBlue = round(averagecol);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loops through each row
    for (int i = 0; i < height; i++)
    {
        // Loops through each column
        for (int j = 0; j < width; j++)
        {
            float sepiared = (.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            if (sepiared > 255)
            {
                sepiared = 255;
            }
            float sepiagreen = (.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            if (sepiagreen > 255)
            {
                sepiagreen = 255;
            }
            float sepiablue = (.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiablue > 255)
            {
                sepiablue = 255;
            }

            image[i][j].rgbtRed = round(sepiared);
            image[i][j].rgbtGreen = round(sepiagreen);
            image[i][j].rgbtBlue = round(sepiablue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempimage[height][width];
    // Loops through each row and makes a temp image
    for (int i = 0; i < height; i++)
    {
        // Loops through each pixel and swap positions
        for (int j = 0; j < width; j++)
        {
            // Creates a copy of the image
            tempimage[i][j] = image[i][j];
        }
    }
    // Loops through each row and swaps the position of each pixel based on the temp image
    for (int i = 0; i < height; i++)
    {
        for (int j = 1; j < width; j++)
        {
            // Gathers the new colors from the copy to avoid copying the same pixel twice
            image[i][j] = tempimage[i][width - j - 1];
        }
    }
    // Corrects the first row
    for (int i = 0; i < height; i++)
    {
        image[i][0] = tempimage[i][width - 1];
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempimage[height][width];
    // Loops through each row and makes a temp image
    for (int i = 0; i < height; i++)
    {
        // Loops through each pixel and swap positions
        for (int j = 0; j < width; j++)
        {
            // Creates a copy of the image
            tempimage[i][j].rgbtRed = image[i][j].rgbtRed;
            tempimage[i][j].rgbtGreen = image[i][j].rgbtGreen;
            tempimage[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    // Loops through each row
    for (int i = 0; i < height; i++)
    {
        // Loops through each column
        for (int j = 0; j < width; j++)
        {
            float counter = 0.0;
            float averageRed = 0.0;
            float averageGreen = 0.0;
            float averageBlue = 0.0;

            averageRed += tempimage[i][j].rgbtRed;
            averageGreen += tempimage[i][j].rgbtGreen;
            averageBlue += tempimage[i][j].rgbtBlue;
            counter ++;

            if (i + 1 < height) // Check top
            {
                averageRed += tempimage[i + 1][j].rgbtRed;
                averageGreen += tempimage[i + 1][j].rgbtGreen;
                averageBlue += tempimage[i + 1][j].rgbtBlue;
                counter ++;
            }
            if (j < width - 1) // Check right
            {
                averageRed += tempimage[i][j + 1].rgbtRed;
                averageGreen += tempimage[i][j + 1].rgbtGreen;
                averageBlue += tempimage[i][j + 1].rgbtBlue;
                counter ++;
            }
            if (i - 1 >= 0) // Check bottom
            {
                averageRed += tempimage[i - 1][j].rgbtRed;
                averageGreen += tempimage[i - 1][j].rgbtGreen;
                averageBlue += tempimage[i - 1][j].rgbtBlue;
                counter ++;
            }
            if (j - 1 >= 0) // Check left
            {
                averageRed += tempimage[i][j - 1].rgbtRed;
                averageGreen += tempimage[i][j - 1].rgbtGreen;
                averageBlue += tempimage[i][j - 1].rgbtBlue;
                counter ++;
            }
            if (i + 1 < height && j < width - 1) // Check top right
            {
                averageRed += tempimage[i + 1][j + 1].rgbtRed;
                averageGreen += tempimage[i + 1][j + 1].rgbtGreen;
                averageBlue += tempimage[i + 1][j + 1].rgbtBlue;
                counter ++;
            }
            if (i + 1 < height && j - 1 >= 0) // Check top left
            {
                averageRed += tempimage[i + 1][j - 1].rgbtRed;
                averageGreen += tempimage[i + 1][j - 1].rgbtGreen;
                averageBlue += tempimage[i + 1][j - 1].rgbtBlue;
                counter ++;
            }
            if (i - 1 >= 0 && j < width - 1) // Check bottom right
            {
                averageRed += tempimage[i - 1][j + 1].rgbtRed;
                averageGreen += tempimage[i - 1][j + 1].rgbtGreen;
                averageBlue += tempimage[i - 1][j + 1].rgbtBlue;
                counter ++;
            }
            if (i - 1 >= 0 && j - 1 >= 0) // Check bottom left
            {
                averageRed += tempimage[i - 1][j - 1].rgbtRed;
                averageGreen += tempimage[i - 1][j - 1].rgbtGreen;
                averageBlue += tempimage[i - 1][j - 1].rgbtBlue;
                counter ++;
            }
            image[i][j].rgbtRed = round(averageRed / counter);
            image[i][j].rgbtGreen = round(averageGreen / counter);
            image[i][j].rgbtBlue = round(averageBlue / counter);
        }
    }
    return;
}
