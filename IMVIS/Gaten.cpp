#include "Gaten.h"

#include <iostream>
using namespace cv;
using namespace std;

Gaten::Gaten(Mat& src, Mat& dst) {
    this->src = src;
    this->dst = dst;
    HEIGHT = src.rows;
    WIDTH = src.cols;
}

void Gaten::process(void)
{
    int binnenhoek = 0;
    int buitenhoek = 0;
    for (int h = 1; h < HEIGHT - 1; h++)
    {
        for (int w = 1; w < WIDTH - 1; w++)
        {
            int tempTeller = 0;
            for (int i = 0; i <= 1; i++)
            {
                for (int j = 0; j <= 1; j++)
                {
                    if (src.at<uchar>(h + i, w + j) == 255)
                        tempTeller++;
                }
            }
            if (tempTeller == 3)
                binnenhoek++;
            if (tempTeller == 1)
                buitenhoek++;
        }
    }
    int a = (buitenhoek - binnenhoek) / 4;
    cout << a << endl;

}