// 3.2.2获取当前滑动条位置.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\core.hpp>
#include<iostream>
#include<opencv2\highgui\highgui.hpp>
using namespace cv;
using namespace std;

const int trackbar_max = 100;
int trackbar_now = 3;

void on_change(int, void*);

int main()
{
	printf("记录滑动条位置\n");
	Mat srcImage = imread("1.jpg");
	namedWindow("获取滑动调位置", 1);
	imshow("获取滑动调位置", srcImage);
	createTrackbar("滑动条", "获取滑动调位置",&trackbar_now,trackbar_max,on_change);
	while (waitKey(333) != 27) { 
		char color[30];
		sprintf_s(color, "color 0%d",rand() % 10);
		//printf("color 0%d", rand() % 10); 
		cout << color << endl;
		system(color);
	}
    return 0;
}
void on_change(int, void*) {
	printf("滑动条当前位置：%d\n", getTrackbarPos("滑动条", "获取滑动调位置"));
}
