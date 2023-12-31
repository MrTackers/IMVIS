#include "Zoom.h"

#include <iostream>

using namespace cv;
using namespace std;

Zoom::Zoom(Mat& src, Mat& dst, float zoomFactor, int x, int y)
{
    this->src = src;
    this->dst = dst;
    HEIGHT = src.rows;
    WIDTH = src.cols;
    this->zoomFactor = zoomFactor;
    this->x = x;
    this->y = y;
}


void affineTransformation(Mat& src, Mat& dst, float matrix[3][3])
{
    int height = src.rows;
    int width = src.cols;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Nieuwe coordinaten berekenen
            int new_x = (matrix[0][0] * i) + (matrix[0][1] * j) + (matrix[0][2] * 1);
            int new_y = (matrix[1][0] * i) + (matrix[1][1] * j) + (matrix[1][2] * 1);

            // Kijken of coordinaten in de image bounds zitten
            if (new_x >= 0 && new_x < height && new_y >= 0 && new_y < width)
            {
                // Destination image renderen met src pixels
                dst.at<uchar>(new_x, new_y) = src.at<uchar>(i, j);
            }
        }
    }
}

void affineTransformationInverted(Mat& src, Mat& dst, float matrix[3][3])
{
    int height = src.rows;
    int width = src.cols;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int og_x = (matrix[0][0] * i);
            int og_y = (matrix[1][1] * j);

            if (og_x >= 0 && og_x < height && og_y >= 0 && og_y < width)
                dst.at<uchar>(i, j) = src.at<uchar>(og_x, og_y);
        }
    }
}

void Zoom::process(void){
    // Calculated the target X, this makes the provided x centered into the new image.
       int targetX = x - ((WIDTH / zoomFactor) / 2);
       int targetY = y - ((HEIGHT / zoomFactor) / 2);


    float move_matrix[3][3] = {
        {1, 0, targetY * -1},
        {0, 1, targetX * -1},
        {0, 0, 1} };

    float calcZoom = 1 / zoomFactor;

    float zoom_matrix[3][3] = {
        {calcZoom, 0, 0},
        {0, calcZoom, 0},
        {0, 0, calcZoom} };

    Mat storage1 = Mat::ones(HEIGHT, WIDTH, CV_8U) * 255;
    affineTransformation(src, storage1, move_matrix);
    affineTransformationInverted(storage1, dst, zoom_matrix);
}