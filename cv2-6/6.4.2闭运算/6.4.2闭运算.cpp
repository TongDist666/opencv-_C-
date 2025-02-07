// 6.4.2闭运算.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<iostream>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;
using namespace std;

#define WIN_YUAN "闭运算原图"
#define WIN_XIAO "闭运算效果图"

Mat srcImage, dstImage, kernel;

void size_change(int, void*);
int size_0 = 3;//内核尺寸
int size_max = 20;

void iterations_change(int, void*);
int iteration_count = 1;//迭代次数初值
int iteration_max = 10;

void morph_change(int, void*);
int morph_dst = 0;
string dst(int d);

int main()
{
	srcImage = imread("1.jpg");
	if (!srcImage.data) printf("图片读取错误！");
	namedWindow(WIN_XIAO);
	imshow(WIN_YUAN, srcImage);

	createTrackbar("闭运算核尺寸", WIN_XIAO, &size_0, size_max, size_change);
	createTrackbar("迭代次数", WIN_XIAO, &iteration_count, iteration_max, iterations_change);
	createTrackbar("内核形状", WIN_XIAO, &morph_dst, 2, morph_change);

	size_change(size_0, 0);
	iterations_change(iteration_count, 0);
	morph_change(morph_dst, 0);

	while (waitKey(0)!=27) {	}
	return 0;
}

void size_change(int, void*) {
	kernel = getStructuringElement(morph_dst, Size(2 * size_0 + 1, 2 * size_0 + 1));
	morphologyEx(srcImage, dstImage, MORPH_CLOSE, kernel, Point(-1, -1), iteration_count);
	imshow(WIN_XIAO, dstImage);
	cout << "闭运算\n内核尺寸：（" << 2 * size_0 + 1 << "," << 2 * size_0 + 1 << "）\t内核形状：" << dst(morph_dst) << "\t迭代次数" << iteration_count << endl;
}
void iterations_change(int, void*) {
	kernel = getStructuringElement(morph_dst, Size(2 * size_0 + 1, 2 * size_0 + 1));
	morphologyEx(srcImage, dstImage, MORPH_CLOSE, kernel, Point(-1, -1), iteration_count);
	imshow(WIN_XIAO, dstImage);
	cout << "闭运算\n内核尺寸：（" << 2 * size_0 + 1 << "," << 2 * size_0 + 1 << "）\t内核形状：" << dst(morph_dst) << "\t迭代次数" << iteration_count << endl;
}
void morph_change(int, void*) {
	kernel = getStructuringElement(morph_dst, Size(2 * size_0 + 1, 2 * size_0 + 1));
	morphologyEx(srcImage, dstImage, MORPH_CLOSE, kernel, Point(-1, -1), iteration_count);
	imshow(WIN_XIAO, dstImage);
	cout << "闭运算\n内核尺寸：（" << 2 * size_0 + 1 << "," << 2 * size_0 + 1 << "）\t内核形状：" << dst(morph_dst) << "\t迭代次数" << iteration_count << endl;
}
string dst(int d) {
	switch (d)
	{
	case 0:
		return "MORPH_RECT";
	case 1:
		return "MORPH_CROSS";
	case 2:
		return "MORPH_ELLIPSE";
	default:
		break;
	}
}