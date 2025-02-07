// 6.4.4顶帽运算top_hat.cpp: 定义控制台应用程序的入口点。
//顶帽运算：原图和开运算之差，用来分离比临近点亮一定的斑块，对大幅背景且有规则微小物体的情况下，可用来提取背景。

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	system("color 8F");//暗一点的灰白色

	Mat image = imread("1.jpg");
	namedWindow("【原始图】顶帽运算", WINDOW_NORMAL);
	namedWindow("【效果图】顶帽运算", WINDOW_NORMAL);

	imshow("【原始图】顶帽运算", image);
	//定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//进行顶帽运算
	morphologyEx(image, image, MORPH_TOPHAT, element);

	imshow("【效果图】顶帽运算", image);

	printf("按q键退出");
	while (char(waitKey(333)) != 'q') {}
	return 0;
}