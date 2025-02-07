// 7.1.5scharr滤波器.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;
using namespace std;

#define WIN_X "X方向scharr"
#define WIN_Y "Y方向scharr"
#define WIN_DST "合并梯度"

void d_change(int, void*);

int delta_0 = 1;
int delta_max = 20;

Mat srcImage, dstImage, x_image, y_image;

int main()
{
	srcImage = imread("1.jpg");
	if (!srcImage.data)
	{
		printf("fail to load the picture!");
		return 0;
	}
	namedWindow(WIN_DST);
	namedWindow(WIN_X);
	namedWindow(WIN_Y);

	createTrackbar("delta", WIN_DST, &delta_0, delta_max, d_change);
	d_change(0, 0);

	while (waitKey(0) != 27) {}
	return 0;
}
void d_change(int, void*) {
	/*
	void Scharr(
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
	double scale = 1, 计算导数时可选的缩放因子
	double delta = 0,结果存入目标图之前可选的delta值
	int borderType = BORDER_DEFAULT );
	*/
	Scharr(srcImage, x_image, CV_16S, 1, 0, 1, double(delta_0));
	Scharr(srcImage, y_image, CV_16S, 0, 1, 1, double(delta_0));

	convertScaleAbs(x_image, x_image);//梯度有负值，因此绝对值一下
	convertScaleAbs(y_image, y_image);
	addWeighted(x_image, 0.5, y_image, 0.5, 0, dstImage);

	imshow(WIN_X, x_image);
	imshow(WIN_Y, y_image);
	imshow(WIN_DST, dstImage);
}
