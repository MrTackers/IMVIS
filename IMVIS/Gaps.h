#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;
using namespace std;

class GatenBeter {
public:
    GatenBeter(Mat& src, Mat& dst);
    void process(void);
    int labelPixel(uint16_t h, uint16_t w);
    int label;
private:
    Mat src, dst;
    int HEIGHT, WIDTH;
    int SIZE_THRESHOLD = 50;
};
