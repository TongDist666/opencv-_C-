// 7.1.4.3laplacian算子使用.cpp: 定义控制台应用程序的入口点。
//图像减去自身的Laplacian算子可以增强对比度

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
#include<opencv2\highgui\highgui.hpp>
using namespace cv;

int main()
{
	system("color 5E");//紫色背景

	Mat src, src_gray, dst, abs_dst;

	//【1】载入原始图  
	src = imread("1.jpg");  //工程目录下应该有一张名为1.jpg的素材图

							//【2】显示原始图 
	imshow("【原始图】图像Laplace变换", src);

	//【3】使用高斯滤波消除噪声
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);

	//【4】转换为灰度图
	cvtColor(src, src_gray, COLOR_RGB2GRAY);

	//【5】使用Laplace函数
	//Laplacian(输入图像 单通8位，输出图像，图像深度，二阶导数的滤波器孔径 必须为正奇数 默认1即3*3，比例因子 默认1，结果delta值，边界模式)
	Laplacian(src_gray, dst, CV_16S, 3, 1, 0, BORDER_DEFAULT);
	imshow("[此时的dst]", dst);

	//【6】计算绝对值，并将结果转换成8位
	convertScaleAbs(dst, abs_dst);

	//【7】显示效果图
	imshow("【效果图】图像Laplace变换", abs_dst);

	printf("hello");
	while (waitKey(333) != 27) {}
    return 0;
}

