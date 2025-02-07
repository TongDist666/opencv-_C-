// 3.2.1滑动条的使用.2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\core.hpp>
#include<Windows.h>
#include<opencv2\highgui\highgui.hpp>
using namespace cv;

#define WINDOW_NAME "滑动条窗口"

const int trackbar_max = 100;//滑动条最大值
int trackbar_now=30;//滑动条最小值
double a, b;

Mat srcImage1, srcImage2, dstImage;

void on_change(int, void*) {
	a = (double)trackbar_now / trackbar_max;//图片1的混合比例
	b = 1.0 - a;//图片2的混合比例
	addWeighted(srcImage1, a, srcImage2, b,0.0, dstImage);//混合
	imshow(WINDOW_NAME, dstImage);
}

int main()
{
	srcImage1 = imread("1.jpg");
	srcImage2 = imread("1.1.jpg");
	if (srcImage1.data != 0 and srcImage2.data != 0) printf("图片载入成功");
	else { printf("图片载入失败"); Sleep(3000); return -1; }

	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);//此处窗口用NORMAL的话刚开始没显示图片，所以窗口很小，滑动条很小，有点不合适
	
	char trackbar_name[50];
	sprintf_s(trackbar_name,"透明度 %d",trackbar_max);
	
	on_change(trackbar_now, 0);
	createTrackbar(trackbar_name, WINDOW_NAME, &trackbar_now, trackbar_max,on_change);
	/*
	creatTrackbar(
		1 const string& 滑动条名
		2 const string& 窗口名
		3 int* 滑动条初始位置
		4 int 滑动条最大值（最小值为 0）
		5 TrackCallback on_change=0 回调函数
		6 void* userdata=0 如果3中实参是全局变量，可以不管这个参数
	)
	*/
	

	while(waitKey(0)!=27){}
    return 0;
}