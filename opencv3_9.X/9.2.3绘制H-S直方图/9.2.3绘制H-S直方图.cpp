// 9.2.3绘制H-S直方图.cpp: 定义控制台应用程序的入口点。
//H~ hue色调  S~saturation饱和度 即色调~饱和度直方图

#include "stdafx.h"
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;

int main()
{
	system("color 7C");//背景灰白色，字红色
	
	//【1】载入源图，转化为HSV颜色模型
	Mat srcImage, hsvImage;
	srcImage = imread("1.jpg");
	cvtColor(srcImage, hsvImage, COLOR_BGR2HSV);

	system("color 2F");

	//【2】参数准备
	//将色调量化为30个等级，将饱和度量化为32个等级
	int hueBinNum = 30;//色调的直方图直条数量
	int saturationBinNum = 32;//饱和度的直方图直条数量
	int histSize[] = { hueBinNum, saturationBinNum };
	// 定义色调的变化范围为0到179
	float hueRanges[] = { 0, 180 };
	//定义饱和度的变化范围为0（黑、白、灰）到255（纯光谱颜色）
	float saturationRanges[] = { 0, 256 };
	const float* ranges[] = { hueRanges, saturationRanges };
	MatND dstHist;
	//参数准备，calcHist函数中将计算第0通道和第1通道的直方图
	int channels[] = { 0, 1 };

	//【3】正式调用calcHist，进行直方图计算
	calcHist(&hsvImage,//输入的数组 const Mat*类型（深度CV_8U或CV_32F）
		1, //数组个数为1 int 输入数组的个数
		channels,//通道索引 const int* 需要统计的通道（dim）索引 第一个数组通道从0到image[0].channels()-1,第二个数组通道从image[0].channels()计算到image[0].channels()+image[1].channels()-1
		Mat(), //不使用掩膜 若非空必须为8位且与输入数组同尺寸
		dstHist, //输出的目标直方图 二维数组
		2, //需要计算的直方图的维度为2 int 必须为2~32
		histSize, //存放每个维度的直方图尺寸的数组 const int*
		ranges,//每一维数值的取值范围数组 const float** 每一维数值的取值范围
		true, // 指示直方图是否均匀的标识符，true表示均匀的直方图
		false);//累计标识符，false表示直方图在配置阶段会被清零

	//【4】为绘制直方图准备参数
	double maxValue = 0;//最大值
	minMaxLoc(dstHist, 0, &maxValue, 0, 0);//查找数组和子数组的全局最小值和最大值存入maxValue中
	/*
	minMaxLoc(
		1 输入数组 单通
		2 double* 最小值指针 无需返回置为NULL
		3 double* 最大值指针 无需返回置为NULL
		4 point* 最小位置指针（二维情况下）无需返回置为NULL
		5 point* 最大位置指针（二维情况下）无需返回置为NULL
		6 选择子阵列可选掩膜
	)
	*/

	int scale = 10;
	Mat histImg = Mat::zeros(saturationBinNum*scale, hueBinNum * 10, CV_8UC3);

	//【5】双层循环，进行直方图绘制
	for (int hue = 0; hue < hueBinNum; hue++)
		for (int saturation = 0; saturation < saturationBinNum; saturation++)
		{
			float binValue = dstHist.at<float>(hue, saturation);//直方图组距的值
			int intensity = cvRound(binValue * 255 / maxValue);//强度

															   //正式进行绘制
			rectangle(histImg, Point(hue*scale, saturation*scale),
				Point((hue + 1)*scale - 1, (saturation + 1)*scale - 1),
				Scalar::all(intensity), FILLED);
		}
	imshow("原图", srcImage);
	imshow("H-S直方图", histImg);

	printf("按ESC退出");
	while(waitKey(333)!=27){}
    return 0;
}

