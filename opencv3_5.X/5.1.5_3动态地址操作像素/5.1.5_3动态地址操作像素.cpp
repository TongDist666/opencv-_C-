// 5.1.5_3动态地址操作像素.cpp: 定义控制台应用程序的入口点。
//

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
	//改变命令行颜色（蓝色）
	system("color 9F");

	//【1】创建原始图并显示
	Mat srcImage = imread("1.jpg");
	imshow("原始图像", srcImage);

	//【2】按原始图的参数规格来创建创建效果图
	Mat dstImage;
	dstImage.create(srcImage.rows, srcImage.cols, srcImage.type());//效果图的大小、类型与原图片相同 

	//【3】记录起始时间
	double time0 = static_cast<double>(getTickCount());

	//【4】调用颜色空间缩减函数
	colorReduce(srcImage, dstImage, 32);

	//【5】计算运行时间并输出
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "此方法运行时间为： " << time0 << "秒" << endl;  //输出运行时间

												   //【6】显示效果图
	imshow("效果图", dstImage);
	waitKey(0);
}

void colorReduce(Mat& inputImage, Mat& outputImage, int div)
{
	//参数准备
	outputImage = inputImage.clone();  //拷贝实参到临时变量
	int rowNumber = outputImage.rows;  //行数
	int colNumber = outputImage.cols;  //列数

									   
	//存取彩色图像像素
	for (int i = 0; i < rowNumber; i++)
	{
		for (int j = 0; j < colNumber; j++)
		{
			// ------------------------【开始处理每个像素】--------------------
			//at方法本身不会进行类型转换，使用前确定mat和Vec3b类型符合
			outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div * div + div / 2;  //蓝色通道
			outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div * div + div / 2;  //绿色通道
			outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div * div + div / 2;  //红是通道
																									// -------------------------【处理结束】----------------------------
		}  // 行处理结束     
	}
}