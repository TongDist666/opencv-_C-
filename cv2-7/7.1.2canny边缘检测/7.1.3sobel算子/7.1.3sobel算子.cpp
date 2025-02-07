// 7.1.3sobel算子.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<iostream>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;
using namespace std;

#define WIN_X "X方向sobel"
#define WIN_Y "Y方向sobel"
#define WIN_DST "合并梯度"

void d_change(int, void*);

int dx_0 = 1;//X方向差分阶数
int dx_max = 2;
int dy_0 = 1;//Y方向差分阶数
int dy_max = 2;

int ksize_0 = 1;//sobel内核尺寸
int ksize_max = 3;

int delta_0 = 1;
int delta_max = 20;

Mat srcImage, dstImage, x_image, y_image;

int main()
{
	srcImage = imread("1.jpg");
	cout << srcImage.type() << endl;
	if (!srcImage.data)
	{
		printf("fail to load the picture!");
		return 0;
	}
	namedWindow(WIN_DST);
	namedWindow(WIN_X);
	namedWindow(WIN_Y);

	createTrackbar("x差分阶数", WIN_DST, &dx_0, dx_max, d_change);
	createTrackbar("y差分阶数", WIN_DST, &dy_0, dy_max, d_change);
	createTrackbar("sobel内核尺寸", WIN_DST, &ksize_0, ksize_max, d_change);
	createTrackbar("delta", WIN_DST, &delta_0, delta_max, d_change);
	d_change(0, 0);

	while(waitKey(0)!=27){}
    return 0;
}
void d_change(int, void*) {
	/*
	void Sobel( 
		InputArray src, 
		OutputArray dst, 
		int ddepth,输出图像深度
			需满足：
				src.depth		ddepth
				CV_8U			-1/CV_16S/CV_32F/CV_64F
				CV_16U/CV_16S	-1/CV_32F/CV_64F
				CV_32F			-1/CV_32F/CV_64F
				CV_64F			-1/CV_64F
        int dx, x方向差分阶数
		int dy, y方向差分阶数
		int ksize = 3,sobel内核尺寸		1、3、5、7之一	
				注：
					ksize=1时，会使用1X3或3X1内核，且不进行高斯平滑操作
					ksize=3时，sobel内核可能出现明显误差，为此可使用Scharr函数（仅作用于3X3），更精确
        double scale = 1, 计算导数时可选的缩放因子
		double delta = 0,结果存入目标图之前可选的delta值
        int borderType = BORDER_DEFAULT );
	*/
	Sobel(srcImage, x_image, CV_16S, dx_0, 0, ksize_0 * 2 + 1, 1, double(delta_0));
	Sobel(srcImage, y_image, CV_16S, 0, dy_0, ksize_0 * 2 + 1, 1, double(delta_0));

	convertScaleAbs(x_image, x_image);//梯度有负值，因此绝对值一下
	convertScaleAbs(y_image, y_image);
	addWeighted(x_image, 0.5, y_image, 0.5, 0, dstImage);

	imshow(WIN_X, x_image);
	imshow(WIN_Y, y_image);
	imshow(WIN_DST, dstImage);
}
