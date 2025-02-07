// 7.1.2canny边缘检测.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;

#define WIN_CANNY "canny检测"

Mat srcImage, dstImage, grayImage;

void on_change(int, void*);
int blursize_0 = 2;//降噪 内核尺寸 最小值
int blursize_max = 20;//降噪 内核尺寸 最大值
int low_threshold_0 = 3;//低阈值 最小值
int low_threshold_max = 30;//低阈值 最大值
int high_threshold_0 = 9;//高阈值 最小值
int high_threshold_max = 200;//高阈值 最大值
int sobel_size_0 = 0;//sobel 孔径 只能是3，5，7
int sobel_size_max = 2;

int main()
{
	srcImage = imread("1.jpg");
	dstImage.create(srcImage.size(), srcImage.type());
	if (!srcImage.data) {
		printf("fail to load the picture!");
		return 0;
	}
	//转换成灰度图
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY);
	
	namedWindow(WIN_CANNY);
	createTrackbar("blursize", WIN_CANNY, &blursize_0, blursize_max, on_change);
	createTrackbar("low_threshold", WIN_CANNY, &low_threshold_0, low_threshold_max, on_change);
	createTrackbar("high_threshold", WIN_CANNY, &high_threshold_0, high_threshold_max, on_change);
	createTrackbar("sobel_size", WIN_CANNY, &sobel_size_0, sobel_size_max, on_change);
	on_change(0, 0);

	while(waitKey(0)!=27){}                                                                                                                                                                                                                                                                                                                                                                                                  
    return 0;
}
void on_change(int, void*) {
	//先降噪
	blur(grayImage, dstImage, Size(blursize_0+1, blursize_0+1));

	/*
	void Canny( 
		InputArray image, //源图像 8位 单通
		OutputArray edges,//输出的边缘图
        double threshold1, //第一个滞后性阈值
		double threshold2,//第二个滞后性阈值  这两顺序可颠倒，不影响
			对于这两个阈值，低阈值用于边缘连接，高阈值用于控制强边缘的初始段  建议：高/低=2:1~3:1
				1像素幅值超过高阈值，保留为边缘像素
				2像素幅值低于低阈值，像素被排除
				3像素幅值位于高低阈值之间，该像素仅在连接到一个高于高阈值的像素时被保留
        int apertureSize = 3, //sobel 孔径大小  只能是3，5，7
		bool L2gradient = false );//计算图像梯度幅值标识
	*/
	Canny(dstImage, dstImage, low_threshold_0, high_threshold_0, sobel_size_0*2+3);
	imshow(WIN_CANNY, dstImage);
}
