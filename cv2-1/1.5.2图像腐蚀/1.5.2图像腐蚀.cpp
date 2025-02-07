// 1.5.2图像腐蚀.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\highgui\highgui.hpp>//imread,imshow,waitKey
#include<opencv2\imgproc\imgproc.hpp>//getStructuringElement,MORPH_RECT,erode
using namespace cv;

int main()
{
	system("color 1A");//背景蓝色，字绿色
	printf("hello");
	//数据结构准备
	Mat srcImage, dstImage;
	srcImage = imread("1.jpg");
	//处理
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	erode(srcImage, dstImage, element);
	//显示
	imshow("【原图】", srcImage);
	imshow("【腐蚀效果图】", dstImage);

	while (waitKey(0) != 27) {}
	return 0;
}

