// 1.6.2-2摄像头配合canny边缘检测.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>//VideoCapture
using namespace cv;

int main()
{
	system("color 6A");//背景翔黄色色，字绿色
	printf("hello");

	//读取摄像头
	VideoCapture capture(0);

	while (1) {
		Mat frame,edgs;
		capture >> frame;//读取当前帧
		cvtColor(frame, edgs, CV_BGR2GRAY);//转换为灰度图
		blur(edgs, edgs, Size(7, 7));//3x3内核模糊（2X3+1）
		Canny(edgs, edgs, 0, 30, 3);//canny检测

		imshow("摄像头加canny", edgs);//显示
		if (waitKey(30) == 27) break;
	}
	return 0;
}
