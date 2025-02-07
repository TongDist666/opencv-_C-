// 6.5.3floodfill函数用法实例.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;

int main()
{
	system("color 9F");//亮蓝色
	Mat srcImg = imread("1.jpg");
	imshow("原图", srcImg);

	Rect flood;
	//scalar(255,0,0)是蓝色，后两个分别为绿，红
	floodFill(srcImg, Point(50, 300), Scalar(255, 0, 0), &flood, Scalar(20, 20, 20), Scalar(20, 20, 20));
	imshow("效果图", srcImg);
	printf("按q键退出");
	while (char(waitKey(333)) != 'q') {}
    return 0;
}

