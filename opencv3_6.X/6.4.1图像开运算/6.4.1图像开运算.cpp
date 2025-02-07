// 6.4.1图像开运算.cpp: 定义控制台应用程序的入口点。
//开运算，先腐蚀后膨胀
//消除小物体，在纤细点处分离物体，平滑边界并不明显改变面积

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>

using namespace cv;

int main()
{
	system("color 5F");//紫色
	Mat srcImg = imread("1.jpg");

	namedWindow("【开运算】原图", WINDOW_NORMAL);
	namedWindow("【开运算】效果图", WINDOW_NORMAL);

	imshow("【开运算】原图", srcImg);
	//定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//进行形态学操作
	morphologyEx(srcImg, srcImg, MORPH_OPEN, element);//可以就地操作

	imshow("【开运算】效果图",srcImg);
	printf("按ESC退出");
	while (waitKey(1)!=27){}
    return 0;
}