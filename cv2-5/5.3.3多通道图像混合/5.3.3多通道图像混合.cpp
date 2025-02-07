// 5.3.3多通道图像混合.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
using namespace cv;
using namespace std;

void blue() {
	Mat srcImage = imread("1-1.jpg");
	Mat logo = imread("2.jpg", 0);

	vector<Mat> channels;//mat容器
	split(srcImage, channels);//通道分离
	Mat blueChannel = channels.at(0);//蓝色通道，此处是引用

	addWeighted(blueChannel(Rect(10, 10, logo.cols, logo.rows)), 0.0, logo, 1.0, 0, blueChannel(Rect(10, 10, logo.cols, logo.rows)));
	merge(channels, srcImage);//合并通道
	imshow("原图+logo蓝色通道", srcImage);
}
void green() {
	Mat srcImage = imread("1-1.jpg");
	Mat logo = imread("2.jpg", 0);

	vector<Mat> channels;
	split(srcImage, channels);//通道分离
	Mat greenChannel = channels.at(1);//绿色通道，此处是引用

	addWeighted(greenChannel(Rect(10, 10, logo.cols, logo.rows)), 0.0, logo, 1.0, 0, greenChannel(Rect(10, 10, logo.cols, logo.rows)));
	merge(channels, srcImage);//合并通道
	imshow("原图+logo绿色通道", srcImage);
}
void red() {
	Mat srcImage = imread("1-1.jpg");
	Mat logo = imread("2.jpg", 0);

	vector<Mat> channels;
	split(srcImage, channels);//通道分离
	Mat redChannel = channels.at(2);//红色通道，此处是引用

	addWeighted(redChannel(Rect(10, 10, logo.cols, logo.rows)), 0.0, logo, 1.0, 0, redChannel(Rect(10, 10, logo.cols, logo.rows)));
	merge(channels, srcImage);//通道合并
	imshow("原图+logo红色通道", srcImage);
}
int main()
{
	blue();
	green();
	red();
	while (waitKey(0) != 27) {}
    return 0;
}

