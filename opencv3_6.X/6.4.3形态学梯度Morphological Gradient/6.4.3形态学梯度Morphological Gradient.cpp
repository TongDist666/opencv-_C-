// 6.4.3形态学梯度Morphological Gradient.cpp: 定义控制台应用程序的入口点。
//形态学梯度：膨胀图和腐蚀图之差，可以将边缘突出出来

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{   
	system("color 7F");//灰白色

	Mat image = imread("1.jpg"); 
	namedWindow("【原始图】形态学梯度",WINDOW_NORMAL);
	namedWindow("【效果图】形态学梯度", WINDOW_NORMAL);

	imshow("【原始图】形态学梯度", image);
	//定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//进行形态学操作
	morphologyEx(image, image, MORPH_GRADIENT, element);

	imshow("【效果图】形态学梯度", image);

	printf("按q键退出");
	while (char(waitKey(333)) != 'q') {}
	return 0;
}