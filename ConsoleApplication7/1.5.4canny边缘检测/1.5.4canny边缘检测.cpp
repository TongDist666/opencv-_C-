// 1.5.4canny边缘检测.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;

int main()
{
	Mat srcImage = imread("1.jpg");
	imshow("原图_canny边缘检测", srcImage);
	Mat edge, grayImage;

	//1.将原图转换为灰度图像
	//cvtColor( InputArray src, OutputArray dst, int code, int dstCn = 0 )
	//CV_BGR2GRAY = 6
	cvtColor(srcImage, grayImage, CV_BGR2GRAY);

	//2.先使用3*3内核降噪
	blur(grayImage, edge, Size(3, 3));

	//3.运行canny算子
	/*第一个参数表示输入图像，必须为单通道灰度图。
	第二个参数表示输出的边缘图像，为单通道黑白图。
	第三个参数和第四个参数表示阈值，这二个阈值中当中的小阈值用来控制边缘连接，
	大的阈值用来控制强边缘的初始分割即如果一个像素的梯度大与上限值，则被认为是边缘像素，
	如果小于下限阈值，则被抛弃。如果该点的梯度在两者之间则当这个点与高于上限值的像素点连接时我们才保留，否则删除。
	第五个参数表示Sobel 算子大小，默认为3即表示一个3*3的矩阵。*/
	//Canny( InputArray image, OutputArray edges,double threshold1, double threshold2,int apertureSize = 3, bool L2gradient = false );
	Canny(edge, edge, 3, 9, 3,false);//最后一个参数为TRUE的话不显示效果图

	imshow("效果图_canny边缘检测",edge);
	waitKey(0);
    return 0;
}

