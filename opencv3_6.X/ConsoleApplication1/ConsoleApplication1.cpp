// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>

//-----------------------------------【命名空间声明部分】---------------------------------------
//            描述：包含程序所使用的命名空间
//-----------------------------------------------------------------------------------------------
using namespace cv;
using namespace std;
//-----------------------------------【main( )函数】--------------------------------------------
//            描述：控制台应用程序的入口函数，我们的程序从这里开始
//-----------------------------------------------------------------------------------------------
const int g_nMaxAlphaValue = 90;//Alpha值的最大值
int g_nAlphaValueSlider;//滑动条对应的变量
Mat dst, dst2;

void colorReduce(Mat& inputImage, Mat& outputImage, int div);
void on_Trackbar(int, void*)
{
	//根据alpha和beta值进行线性混合
	colorReduce(dst, dst2, g_nAlphaValueSlider + 10);
	//显示效果图
	imshow("【效果图】整体方向Sobel-2", dst2);
}
int main()
{
	//【0】创建 grad_x 和 grad_y 矩阵
	Mat grad_x, grad_y;
	Mat abs_grad_x, abs_grad_y;
	//【1】载入原始图  
	Mat src = imread("1.jpg");  //工程目录下应该有一张名为1.jpg的素材图

								//【2】显示原始图 
	imshow("【原始图】sobel边缘检测", src);

	//【3】求 X方向梯度
	Sobel(src, grad_x, CV_16S, 1, 0, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	//imshow("【效果图】 X方向Sobel", abs_grad_x);

	//【4】求Y方向梯度
	Sobel(src, grad_y, CV_16S, 0, 1, 3, 1, 1, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	//imshow("【效果图】Y方向Sobel", abs_grad_y);

	//【5】合并梯度(近似)
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dst);
	imshow("【效果图】整体方向Sobel", dst);

	dst2.create(dst.rows, dst.cols, dst.type());//效果图的大小、类型与原图片相同
	colorReduce(dst, dst2,0);

	namedWindow("【效果图】整体方向Sobel-2", WINDOW_NORMAL);
	//在创建的窗体中创建一个滑动条控件
	char TrackbarName[50];

	//这里用sprintf会报错，说不安全
	sprintf_s(TrackbarName, "像素阈值： %d", g_nMaxAlphaValue);

	createTrackbar(TrackbarName, "【效果图】整体方向Sobel-2", &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);

	//结果在回调函数中显示
	on_Trackbar(g_nAlphaValueSlider, 0);

	imshow("【效果图】整体方向Sobel-2", dst2);
	//cout << dst2 .row(0)<< endl;

	waitKey(0);
	return 0;
}
void colorReduce(Mat& inputImage, Mat& outputImage,int div)
{
	//参数准备
	outputImage = inputImage.clone();  //拷贝实参到临时变量
	int rowNumber = outputImage.rows;  //行数
	int colNumber = outputImage.cols*outputImage.channels();  //列数 x 通道数=每一行元素的个数

															  //双重循环，遍历所有的像素值
	for (int i = 0; i < rowNumber; i++)  //行循环
	{
		uchar* data = outputImage.ptr<uchar>(i);  //获取第i行的首地址
		for (int j = 0; j < colNumber; j++)   //列循环
		{
			// ---------【开始处理每个像素】-------------     
			//data[j] = data[j] / div * div + div / 2;
			if (data[j] < div) data[j] = 0;
			// ----------【处理结束】---------------------
		}  //行处理结束
	}
}