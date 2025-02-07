// 5.2.1感兴趣区域ROI.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;

int main()
{
	Mat srcImage1 = imread("1.jpg",CV_LOAD_IMAGE_COLOR);
	Mat srcImage2 = imread("2.JPG", CV_LOAD_IMAGE_COLOR);

	Mat roiImage = srcImage1(Rect(10,10,srcImage2.cols,srcImage2.rows));
	srcImage2.copyTo(roiImage);

	imshow("roi",srcImage1);

	while (waitKey(0) != 27) {}
    return 0;
}