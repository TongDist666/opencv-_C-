// 1.5.4canny边缘检测.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>//imread,imshow,waitKey
#include<opencv2\imgproc\imgproc.hpp>//blur
using namespace cv;

int main()
{
	system("color 3A");//背景暗靛色，字绿色
	printf("hello");
	//数据结构准备
	Mat srcImage, grayImage,dstImage;
	srcImage = imread("1.jpg");
	//处理

	//1 转换成灰度图
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);
	//2 用3X3内核模糊
	blur(grayImage, dstImage, Size(3, 3));
	//3 运行canny算子
	Canny(dstImage,dstImage,3,9,3);

	//显示
	imshow("【原图】", srcImage);
	imshow("【canny边缘检测效果图】", dstImage);

	while (waitKey(0) != 27) {}
	return 0;
}