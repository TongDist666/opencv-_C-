// 1.4.8.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>//system,Mat,imread,imshow,waitKey
using namespace cv;

int main()
{
	system("color 0A");//背景黑色，字绿色
	printf("hello");

	Mat img = imread("1.jpg");
	imshow("图片", img);
	while (waitKey(0) != 27) {}
	return 0;
}