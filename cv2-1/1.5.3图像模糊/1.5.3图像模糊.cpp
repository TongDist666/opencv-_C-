// 1.5.3图像模糊.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\highgui\highgui.hpp>//imread,imshow,waitKey
#include<opencv2\imgproc\imgproc.hpp>//blur
using namespace cv;

int main()
{
	system("color 2A");//背景深绿色，字绿色
	printf("hello");
	//数据结构准备
	Mat srcImage, dstImage;
	srcImage = imread("1.jpg");
	//处理
	blur(srcImage, dstImage, Size(6,6));
	//显示
	imshow("【原图】", srcImage);
	imshow("【模糊效果图】", dstImage);

	while (waitKey(0) != 27) {}
	return 0;
}
