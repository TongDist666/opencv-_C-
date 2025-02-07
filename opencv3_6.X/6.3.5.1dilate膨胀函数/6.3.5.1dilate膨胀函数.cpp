// 6.3.5.1dilate膨胀函数.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

int main()
{
	system("color 1F");//0F是黑色，1F是蓝色
	printf("按ESC键退出");
	//载入原图 
	Mat img = imread("1.jpg");

	namedWindow("膨胀操作原图", WINDOW_NORMAL);
	namedWindow("膨胀操作效果图", WINDOW_NORMAL);
	//显示原图
	imshow("膨胀操作原图", img);
	//进行腐蚀操作
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	Mat out;
	dilate(img, out, element);
	//显示效果图
	imshow("膨胀操作效果图", out);
	while (true)
		if (waitKey(333) == 27) return 0;
}

