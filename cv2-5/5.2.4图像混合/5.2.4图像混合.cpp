// 5.2.4图像混合.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;

Mat srcImage1, srcImage2, dstImage, roiImage;
int track_start = 30;
int track_max = 100;

void on_change(int,void*);
int main()
{
	srcImage1 = imread("1-1.jpg", CV_LOAD_IMAGE_COLOR);
	srcImage2 = imread("2.JPG", CV_LOAD_IMAGE_COLOR);
	
	namedWindow("图像混合");
	createTrackbar("混合比例：","图像混合", &track_start,track_max,on_change);
	on_change(30,0);

	while (waitKey(0) != 27) {}
	return 0;
}

void on_change(int, void*) {
	Mat mask;
	srcImage1.copyTo(dstImage);
	roiImage = dstImage(Rect(10, 10, srcImage2.cols, srcImage2.rows));
	mask.create(srcImage2.rows,srcImage2.cols,srcImage2.type());
	double a = double(track_start) / 100;
	double b = 1 - a;
	addWeighted(roiImage,a,srcImage2,b,0,mask);

	/*
	addWeighted(
		InputArray src1, //第一个加权数组
		double alpha, //第一个数组权重
		InputArray src2,//第二个加权数组
        double beta, //第二数组权重
		double gamma, //偏置
		OutputArray dst,// 输出数组
		int dtype = -1);//数组深度  -1表示使用第一数组深度

		注意：
			当数组深度为 CV_32S时，该函数不能用
	*/
	mask.copyTo(roiImage);
	imshow("图像混合", dstImage);
}