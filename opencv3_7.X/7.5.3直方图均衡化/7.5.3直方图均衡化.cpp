// 7.5.3直方图均衡化.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
using namespace cv;

int main()
{
	system("color 6D");//背景暗黄色，字粉色
	Mat srcImage, dstImage;
	srcImage = imread("1.jpg", 1);
	if (!srcImage.data) { printf("读取图片错误，请确定目录下是否有imread函数指定图片存在~！ \n"); return false; }

	// 转为灰度图并显示出来
	cvtColor(srcImage, srcImage, COLOR_BGR2GRAY);
	imshow("原始图", srcImage);

	// 进行直方图均衡化
	equalizeHist(srcImage, dstImage);
	//equalizeHist（输入图像 8位单通，输出图像）

	imshow("经过直方图均衡化后的图", dstImage);

	printf("\t\t键盘按键【ESC】- 退出程序\n");
	while (waitKey(0) != 27) {}
	return 0;
}