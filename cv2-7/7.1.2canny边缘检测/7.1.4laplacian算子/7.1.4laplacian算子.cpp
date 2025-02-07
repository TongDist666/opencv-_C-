// 7.1.4laplacian算子.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;

#define WIN_DST "laplacian算子"

void on_change(int, void*);

int ksize_0 = 0;
int ksize_max = 10;

int scale_0 = 10;
int scale_max = 30;

Mat srcImage, grayImage,dstImage;

int main()
{
	srcImage=imread("1.jpg");
	if (!srcImage.data)
	{
		printf("fail to load the picture!");
		return 0;
	}
	namedWindow(WIN_DST);

	GaussianBlur(srcImage, srcImage, Size(3,3),0,0);
	cvtColor(srcImage, grayImage, COLOR_RGB2GRAY);

	createTrackbar("laplacian孔径", WIN_DST, &ksize_0, ksize_max, on_change);
	createTrackbar("scale", WIN_DST, &scale_0, scale_max, on_change);
	on_change(0, 0);

	while (waitKey(0) != 27);
    return 0;
}
void on_change(int, void*) {
	/*
	void Laplacian( 
		InputArray src, 源图  单通 8位
		OutputArray dst, 输出边缘图
		int ddepth,目标图深度
        int ksize = 1, 用于计算二阶导数的滤波的孔径尺寸 必须为正奇数
		double scale = 1, 计算拉普拉斯值时可选的比例因子
		double delta = 0,
        int borderType = BORDER_DEFAULT );
	*/
	Laplacian(grayImage, dstImage, CV_16S, ksize_0*2+1,double(scale_0/10));
	imshow(WIN_DST, dstImage);
}
