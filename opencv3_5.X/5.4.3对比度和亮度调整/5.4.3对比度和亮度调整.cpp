// 5.4.3对比度和亮度调整.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<iostream>

using namespace cv;
using namespace std;

static void on_ContrastAndBright(int, void *);

int ContrastValue;//对比度
int BrightValue;//亮度
Mat srcImage, dstImage;

int main()
{
	srcImage = imread("1.jpg");
	if (!srcImage.data) { printf("图片读取失败！"); return false; }
	dstImage = Mat::zeros(srcImage.size(), srcImage.type());

	//设定对比度和亮度的初值
	ContrastValue = 60;
	BrightValue = 60;
	namedWindow("效果图窗口", 1);

	//创建轨迹条
	createTrackbar("对比度：", "效果图窗口", &ContrastValue, 300, on_ContrastAndBright);
	createTrackbar("亮度：", "效果图窗口", &BrightValue, 200, on_ContrastAndBright);

	//调用回调函数
	on_ContrastAndBright(ContrastValue, 0);
	on_ContrastAndBright(BrightValue, 0);

	while(char(waitKey(1)!='q')){}

	return 0;
}
//-----------------------------【ContrastAndBright( )函数】------------------------------------
//	描述：改变图像对比度和亮度值的回调函数
//-----------------------------------------------------------------------------------------------

static void on_ContrastAndBright(int, void*) {
	namedWindow("原始图窗口", 1);

	// 三个for循环，执行运算 g_dstImage(i,j) = a*g_srcImage(i,j) + b
	for (int y = 0; y < srcImage.rows; y++) {//行
		for (int x = 0; x < srcImage.cols; x++) {//列
			for (int c = 0; c < 3; c++) {//BGR三通道
				dstImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((ContrastValue*0.01)*(srcImage.at<Vec3b>(y,x)[c])+BrightValue);
				//对比度一般取值0~3浮点值，为了对应轨迹条，变成300*0.01
				//saturate_cast为溢出保护
			}
		}
	}
	imshow("原始图窗口", srcImage);
	imshow("效果图窗口", dstImage);
}

