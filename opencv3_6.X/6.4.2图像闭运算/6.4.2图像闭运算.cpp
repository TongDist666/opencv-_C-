// 6.4.2图像闭运算.cpp: 定义控制台应用程序的入口点。
//闭运算，先膨胀后腐蚀，排除小型黑洞（黑色区域）

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>

using namespace cv;

int main()
{
	system("color 6F");//米黄色

	Mat img = imread("1.jpg");

	namedWindow("【闭运算】原图", WINDOW_NORMAL);
	namedWindow("【闭运算】效果图", WINDOW_NORMAL);

	imshow("【闭运算】原图",img);
	//定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//进行形态学操作
	morphologyEx(img, img,MORPH_CLOSE, element);

	imshow("【闭运算】效果图",img);
	printf("按q键退出");
	while(char(waitKey(333))!='q'){}

    return 0;
}

