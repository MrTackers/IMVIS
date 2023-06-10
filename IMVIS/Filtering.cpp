#include "Filtering.h"

#include <iostream>

using namespace cv;
using namespace std;

Filtering::Filtering(Mat &src, Mat &dst)
{
    this->src = src;
    this->dst = dst;
    HEIGHT = src.rows;
    WIDTH = src.cols;
}

void Filtering::Scherpheid(void)
{
    // Define kernel
    int kernel[3][3] = {
        {-1, -1, -1},
        {-1, 9, -1},
        {-1, -1, -1}};

    // Loop through the image
    for (int h = 0; h < HEIGHT; h++)
    {
        for (int w = 0; w < WIDTH; w++)
        {
            int sum = 0;

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    int y, x;
                    y = h + i - 1;
                    x = w + j - 1;

                    if (y < 0)
                        y = 0;

                    if (y >= HEIGHT)
                        y = HEIGHT - 1;

                    if (x < 0)
                        x = 0;

                    if (x >= WIDTH)
                        x = WIDTH - 1;

                    sum += kernel[i][j] * (int16_t)src.at<uchar>(y, x);
                }
            }

            if (sum < 0)
                sum = 0;
            if (sum > 255)
                sum = 255;

            dst.at<uchar>(h, w) = (uint8_t)sum;
        }
    }
}

void Filtering::Smoother(void)
{
    // Define kernel
    int kernel[3][3] = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}};

    // Loop through the image
    for (int h = 0; h < HEIGHT; h++)
    {
        for (int w = 0; w < WIDTH; w++)
        {
            int sum = 0;

            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    int y, x;
                    y = h + i - 1;
                    x = w + j - 1;

                    if (y < 0)
                        y = 0;

                    if (y >= HEIGHT)
                        y = HEIGHT - 1;

                    if (x < 0)
                        x = 0;

                    if (x >= WIDTH)
                        x = WIDTH - 1;

                    sum += kernel[i][j] * (int16_t)src.at<uchar>(y, x);
                }
            }

            // Normalize the sum
            sum /= 9;

            if (sum < 0)
                sum = 0;
            if (sum > 255)
                sum = 255;

            dst.at<uchar>(h, w) = (uint8_t)sum;
        }
    }
}

void Filtering::medianFilter(void)
{
    // Loop through the image
    for (int h = 0; h < HEIGHT; h++)
    {
        for (int w = 0; w < WIDTH; w++)
        {
            // Create an array to store the pixel values
            int values[9];
            int index = 0;

            //loop door image heen
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    int y, x;
                    y = h + i - 1;
                    x = w + j - 1;

                    // Handle edge cases
                    if (y < 0)
                        y = 0;

                    if (y >= HEIGHT)
                        y = HEIGHT - 1;

                    if (x < 0)
                        x = 0;

                    if (x >= WIDTH)
                        x = WIDTH - 1;

                    
                    values[index++] = src.at<uchar>(y, x);
                }
            }

            // Sort the array
            sort(values, values + 9);

            // Set the median value as the new pixel value
            dst.at<uchar>(h, w) = values[4];
        }
    }
}