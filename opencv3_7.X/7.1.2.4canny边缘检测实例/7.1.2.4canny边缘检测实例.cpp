// 7.1.2.4canny边缘检测实例.cpp: 定义控制台应用程序的入口点。
/*canny边缘检测过程：
	1 去噪
	2 计算梯度幅值和方向
	3 非极大值抑制
	4 滞后阈值
*/

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;

int main()
{
	system("color 3E");//背景靛蓝色
	Mat src = imread("1.jpg");
	Mat src_1 = src.clone();

	imshow("canny边缘检测原图", src);
	//----------------------------------------------------------------------------------
	//	一、最简单的canny用法，拿到原图后直接用。
	//	注意：此方法在OpenCV2中可用，在OpenCV3中已失效
	//----------------------------------------------------------------------------------
	//Canny( srcImage, srcImage, 150, 100,3 );
	//imshow("【效果图】Canny边缘检测", srcImage); 


	//----------------------------------------------------------------------------------
	//	二、高阶的canny用法，转成灰度图，降噪，用canny，最后将得到的边缘作为掩码，拷贝原图到效果图上，得到彩色的边缘图
	//----------------------------------------------------------------------------------
	Mat dst, edge, gray;

	// 【1】创建与src同类型和大小的矩阵(dst)
	dst.create(src_1.size(), src_1.type());

	// 【2】将原图像转换为灰度图像
	cvtColor(src_1, gray, COLOR_BGR2GRAY);

	// 【3】先用使用 3x3内核来降噪
	blur(gray, edge, Size(3, 3));

	// 【4】运行Canny算子
	//canny(输入图像 单通8位，输出图像，第一滞后性阈值，第二滞后性阈值，sobel算子孔径大小 默认为3，梯度幅值标识 默认false)
	Canny(edge, edge, 3, 9, 3);

	//【5】将dst内的所有元素设置为0 
	dst = Scalar::all(0);

	//【6】使用Canny算子输出的边缘图Edge作为掩码，来将图拷到目标图dst中
	src_1.copyTo(dst, edge);
	imshow("canny边缘检测效果图", edge);

	printf("hello");
	while (waitKey(333)!=27){}
	
    return 0;
}

