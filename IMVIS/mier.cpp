#include "Mier.h"
#include <stdlib.h>
#include <iostream>


Mier::Mier(Mat& src1, Mat& src2, Mat& dst) {
    this->src1 = src1;
    this->src2 = src2;
    this->dst = dst;
}


void Mier::threshold(Mat& src) {
    std::vector<int> grayscaleValues;  // Vector to store grayscale values



    int h, w;
    for (h = 0; h < src.rows; h++) {
        for (w = 0; w < src.cols; w++) {
            int value = src.at<uchar>(h, w);
            grayscaleValues.push_back(value);
        }
    }

    // Sort the grayscale values
    std::sort(grayscaleValues.begin(), grayscaleValues.end());

    // Calculate the median grayscale value
    int medianIndex = grayscaleValues.size() / 2;
    medianValue = grayscaleValues[medianIndex];
    std::cout << medianValue;


}

void Mier::binary(Mat& src, Mat& tempDst) {
    int h, w;
    // Set the median value to all pixels in the destination image
    for (h = 0; h < src.rows; h++) {
        for (w = 0; w < src.cols; w++) {
            if (src.at<uchar>(h, w) <= medianValue - 20) {
                tempDst.at<uchar>(h, w) = 0;
            }
            else {
                tempDst.at<uchar>(h, w) = 255;
            }
        }
    }
}

void Mier::xorOps(Mat& src1, Mat& src2, Mat& dst) {
    int h, w;
    for (h = 0; h < src1.rows; h++) {
        for (w = 0; w < src1.cols; w++) {
            dst.at<uchar>(h, w) = src1.at<uchar>(h, w) ^ src2.at<uchar>(h, w);
        }
    }
}

void Mier::erosion(Mat& src, Mat& dst) {
    for (int y = 0; y < src.rows; y++)
    {
        for (int x = 0; x < src.cols; x++)
        {
            if (x <= 1 || y <= 1 || x >= src.cols - 1 || y >= src.rows - 1)
                continue;

            // Pixel Erosion
            int pix = src.at<uchar>(y, x);
            int pix_top = src.at<uchar>(y - 1, x);
            int pix_bottom = src.at<uchar>(y + 1, x);
            int pix_left = src.at<uchar>(y, x - 1);
            int pix_right = src.at<uchar>(y, x + 1);
            int pix_top_left = src.at<uchar>(y - 1, x - 1);
            int pix_top_right = src.at<uchar>(y - 1, x + 1);
            int pix_bottom_left = src.at<uchar>(y + 1, x - 1);
            int pix_bottom_right = src.at<uchar>(y + 1, x + 1);

            if (pix == 0 || pix_top == 0 || pix_bottom == 0 || pix_left == 0 || pix_right == 0 || pix_top_left == 0 || pix_top_right == 0 || pix_bottom_left == 0 || pix_bottom_right == 0)
            {
                dst.at<uchar>(y, x) = 0;
            }
            else
            {
                dst.at<uchar>(y, x) = 255;
            }
        }
    }

}

void Mier::dilation(Mat& src, Mat& dst) {
    for (int y = 0; y < src.rows; y++)
    {
        for (int x = 0; x < src.cols; x++)
        {
            if (x <= 1 || y <= 1 || x >= src.cols - 1 || y >= src.rows - 1)
                continue;

            // Pixel Erosion
            int pix = src.at<uchar>(y, x);
            int pix_top = src.at<uchar>(y - 1, x);
            int pix_bottom = src.at<uchar>(y + 1, x);
            int pix_left = src.at<uchar>(y, x - 1);
            int pix_right = src.at<uchar>(y, x + 1);
            int pix_top_left = src.at<uchar>(y - 1, x - 1);
            int pix_top_right = src.at<uchar>(y - 1, x + 1);
            int pix_bottom_left = src.at<uchar>(y + 1, x - 1);
            int pix_bottom_right = src.at<uchar>(y + 1, x + 1);

            if (pix != 0 || pix_top != 0 || pix_bottom != 0 || pix_left != 0 || pix_right != 0 || pix_top_left != 0 || pix_top_right != 0 || pix_bottom_left != 0 || pix_bottom_right != 0)
            {
                dst.at<uchar>(y, x) = 255;
            }
            else
            {
                dst.at<uchar>(y, x) = 0;
            }
        }
    }
}


void Mier::process(void)
{
    Mat tmp1 = Mat::ones(src1.rows, src1.cols, CV_8U) * 0;
    Mat tmp2 = Mat::ones(src1.rows, src1.cols, CV_8U) * 0;
    Mat tmp3 = Mat::ones(src1.rows, src1.cols, CV_8U) * 0;
    Mat tmp4 = Mat::ones(src1.rows, src1.cols, CV_8U) * 0;
    Mat tmp5 = Mat::ones(src1.rows, src1.cols, CV_8U) * 0;
    Mat tmp6 = Mat::ones(src1.rows, src1.cols, CV_8U) * 0;
    threshold(src1);
    binary(src1, tmp1);
    binary(src2, tmp2);
    xorOps(tmp1, tmp2, tmp3);
    erosion(tmp3, tmp4);
    erosion(tmp4, tmp5);
    dilation(tmp5, dst);
    imshow("Test1", tmp1);
    imshow("Test2", tmp2);
    imshow("xor", tmp3);
    imshow("erode", tmp5);
    imshow("dilation", dst);


}