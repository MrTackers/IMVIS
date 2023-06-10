#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

class Gaten
{
public:
	Gaten(Mat& src, Mat& dst);
	void process(void);
	int label;

private:
	Mat src, dst;
	int HEIGHT, WIDTH;
};