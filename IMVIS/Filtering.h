#pragma once
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

class Filtering
{
public:
	Filtering(Mat &src, Mat &dst);
	void Scherpheid(void);
	void Smoother(void);
	void medianFilter(void);

private:
	Mat src, dst;
	int HEIGHT, WIDTH;
};
