// 5.1.5_1指针访问像素.cpp: 定义控制台应用程序的入口点。
//

/*
对于较大的图像进行像素改变，应该先计算所有值，需要时查表直接赋值，这样快
*/

#include "stdafx.h"
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp>  
#include <iostream>  
using namespace std;
using namespace cv;

void colorReduce(Mat& inputImage, Mat& outputImage, int div);
void ShowHelpText();

int main()
{
	//【1】创建原始图并显示
	Mat srcImage = imread("1.jpg");
	imshow("原始图像", srcImage);

	//【2】按原始图的参数规格来创建创建效果图
	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());//效果图的大小、类型与原图片相同 

	//【3】记录起始时间
	double time0 = static_cast<double>(getTickCount());//getTickCount()返回自电脑启动后走过的时钟周期

	//【4】调用颜色空间缩减函数
	colorReduce(srcImage, dstImage, 32);

	//【5】计算运行时间并输出
	time0 = ((double)getTickCount() - time0) / getTickFrequency();//getTickFrequency()返回CPU一秒所走时钟周期数
	cout << "\t此方法运行时间为： " << time0 << "秒" << endl;  //输出运行时间

													 //【6】显示效果图
	imshow("效果图", dstImage);
	waitKey(0);
}

void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
	//参数准备
	outputImage = inputImage.clone();  //拷贝实参到临时变量
	int rowNumber = outputImage.rows;  //行数
	int colNumber = outputImage.cols*outputImage.channels();  //列数 x 通道数=每一行元素的个数
	//灰度图通道数为1，彩色图为3

	//双重循环，遍历所有的像素值
	for (int i = 0; i < rowNumber; i++)  //行循环
	{
		uchar* data = outputImage.ptr<uchar>(i);  //Mat.ptr<uchar>(i)获取第i行的首地址
		for (int j = 0; j < colNumber; j++)   //列循环
		{
			// ---------【开始处理每个像素】-------------     
			data[j] = data[j] / div * div + div / 2;
			// ----------【处理结束】---------------------
		}  //行处理结束
	}
}