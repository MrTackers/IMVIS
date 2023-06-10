#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

class Mier {
public:
	Mier(Mat& src1, Mat& src2, Mat& dst);
	virtual void threshold(Mat& src);
	virtual void binary(Mat& src, Mat& dst);
	virtual void xorOps(Mat& src1, Mat& src2, Mat& dst);
	virtual void erosion(Mat& src, Mat& dst);
	virtual void dilation(Mat& src, Mat& dst);
	virtual void process(void);
private:
	Mat src1;
	Mat src2;
	Mat dst;
	int HEIGHT, WIDTH, medianValue;
};