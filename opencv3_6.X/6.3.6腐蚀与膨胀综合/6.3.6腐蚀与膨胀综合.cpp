// 6.3.6腐蚀与膨胀综合.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>

using namespace cv;
using namespace std;

Mat srcImg, dstImg;//原始图和效果图
int TrackbarNumer = 0;//0表示腐蚀erode，1表示膨胀dilate
int StructElementSize = 3; //结构元素(内核矩阵)的尺寸

void Process();//腐蚀和膨胀的处理函数
void TrackbarNumerChange(int, void *);//回调函数
void StructElementSizeChange(int, void *);//回调函数


int main()
{
	system("color 3F");//3F靛蓝色

	srcImg = imread("1.jpg");
	if (!srcImg.data) {
		printf("图片读取错误！");
		return false;
	}

	namedWindow("原始图", WINDOW_NORMAL);
	imshow("原始图", srcImg);

	namedWindow("效果图", WINDOW_NORMAL);

	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * StructElementSize + 1, 2 * StructElementSize + 1), Point(StructElementSize, StructElementSize));
	erode(srcImg, dstImg, element);

	//进行初次腐蚀操作并显示效果图
	imshow("效果图", dstImg);
	//创建轨迹条
	createTrackbar("腐蚀/膨胀", "效果图", &TrackbarNumer, 1, TrackbarNumerChange);
	createTrackbar("内核尺寸", "效果图", &StructElementSize, 21, StructElementSizeChange);

	cout << endl << "\t运行成功\n" << "\t按下ESC退出" << endl;
	while (waitKey(1)!=27){}

    return 0;
}

void Process() {
	//获取自定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(2 * StructElementSize + 1, 2 * StructElementSize + 1), Point(StructElementSize, StructElementSize));

	//进行腐蚀或膨胀操作
	if (TrackbarNumer == 0) erode(srcImg, dstImg, element);
	else dilate(srcImg, dstImg, element);
	imshow("效果图", dstImg);
}
//腐蚀和膨胀之间效果已经切换，回调函数体内需调用一次Process函数，使改变后的效果立即生效并显示出来
void TrackbarNumerChange(int, void *) { Process(); }

//内核尺寸已改变，回调函数体内需调用一次Process函数，使改变后的效果立即生效并显示出来
void StructElementSizeChange(int, void *) { Process(); }