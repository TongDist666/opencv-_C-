// 6.7.3基本阈值操作.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;
using namespace std;

#define WINDOW_NAME "【程序窗口】"

int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat g_srcImage, g_grayImage, g_dstImage;

static void ShowHelpText();
void on_Threshold(int, void*);

int main()
{
	ShowHelpText();

	//【1】读入源图片
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data) { printf("读取图片错误，请确定目录下是否有imread函数指定的图片存在~！ \n"); return false; }
	imshow("原始图", g_srcImage);

	cvtColor(g_srcImage, g_grayImage, COLOR_RGB2GRAY);

	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);

	createTrackbar("模式",WINDOW_NAME, &g_nThresholdType,4, on_Threshold);

	createTrackbar("参数值",WINDOW_NAME, &g_nThresholdValue,255, on_Threshold);

	on_Threshold(0, 0);

	while(waitKey(0)!=27){}
	return 0;
}

void on_Threshold(int, void*)
{
	threshold(g_grayImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);

	imshow(WINDOW_NAME, g_dstImage);
}

static void ShowHelpText()
{
	printf("\n\t按键操作说明: \n\n"
		"\t\t键盘按键【ESC】- 退出程序\n"
		"\t\t滚动条模式0- 二进制阈值\n"
		"\t\t滚动条模式1- 反二进制阈值\n"
		"\t\t滚动条模式2- 截断阈值\n"
		"\t\t滚动条模式3- 反阈值化为0\n"
		"\t\t滚动条模式4- 阈值化为0\n");
}