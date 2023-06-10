#include "Gaps.h"
using namespace cv;
using namespace std;

#include <iostream>

GatenBeter::GatenBeter(Mat& src, Mat& dst) {
    this->src = src;
    this->dst = dst;
    HEIGHT = src.rows;
    WIDTH = src.cols;
}

int GatenBeter::labelPixel(uint16_t h, uint16_t w) {
    int16_t i, j;
    int size = 1; // initialize size to 1
    if ((src.at<uchar>(h, w) == 255) && (dst.at<uchar>(h, w) == 255)) {
        dst.at<uchar>(h, w) = label;
        for (i = -1; i < 2; i++) {
            for (j = -1; j < 2; j++) {
                if (((i == 0) || (j == 0)) && (h + i >= 0) && (h + i < HEIGHT) && (w + j >= 0) && (w + j < WIDTH)) {
                    size += labelPixel(h + i, w + j); // increment size by the size of the labeled region
                }
            }
        }
        return size; // return the size of the labeled region
    }
    return 0;
}



void GatenBeter::process(void) {
    int16_t h, w;
    for (h = 0; h < HEIGHT; h++)
        for (w = 0; w < WIDTH; w++) {
            dst.at<uchar>(h, w) = 255;
        }
    label = 0;
    for (h = 0; h < HEIGHT; h++) {
        for (w = 0; w < WIDTH; w++) {
            int size = labelPixel(h, w);
            if ((size > SIZE_THRESHOLD) && (label < 254)) { // only increment label count if the size of the region is above the threshold
                label++;
            }
        }
    }
    cout << "Label: " << label << endl;
}