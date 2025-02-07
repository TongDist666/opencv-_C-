// 7.2.5累计概率霍夫变换HoughLinesP函数.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<imgproc\imgproc.hpp>
using namespace cv;
using namespace std;

const int g_nMaxAlphaValue = 200;//Alpha值的最大值
const int min_line = 100;//min_line最大值
const int max_line = 50;//max_line最小值
int g_min, g_max;
int g_nAlphaValueSlider = 66;//滑动条对应的变量
Mat midImage, dstImage;
vector<Vec4i> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合


void on_Trackbar(int, void *) {
	HoughLinesP(midImage, lines, 1, CV_PI / 180, g_nAlphaValueSlider, g_min, g_max);
	/*HoughLinesP(
		1 输入图像 8位单通二进制，
		2 线条输出矢量 4个元素，
		3 double 以像素为单位的距离精度，
		4 double 以弧度为单位的角度精度，
		5 int 累加平面阈值参数，
		6 double 最小线段长，
		7 double 点与点连接起来的最大距离)
	*/
	Mat dstimge;
	dstImage.copyTo(dstimge);
	//依次在图中绘制出每条线段
	for (size_t i = 0; i < lines.size(); i++) {
		Vec4i l = lines[i];
		line(dstimge, Point(l[0],l[1]), Point(l[2], l[3]), Scalar(55, 100, 195), 1, LINE_AA);
		//Scalar(G,B,R)控制颜色
	}
	imshow("效果图", dstimge);
}

int main()
{
	system("color 0D");//背景黑色，字是粉色

	Mat srcImage = imread("1.jpg");

	Canny(srcImage, midImage, 50, 200, 3);//进行一次canny边缘检测
	cvtColor(midImage, dstImage, CV_GRAY2BGR);//转化为灰度图

	imshow("原始图", srcImage);
	imshow("边缘检测后的图", midImage);
	namedWindow("效果图", WINDOW_NORMAL);

	//滑动条设置
	char TrackbarName[50], TrackbarName2[50], TrackbarName3[50];//滑动条名称
	sprintf_s(TrackbarName, "阈值 %d", g_nMaxAlphaValue);
	sprintf_s(TrackbarName2, "min_line %d", min_line);
	sprintf_s(TrackbarName3, "max_line %d", max_line);

	g_min = 50;//min初始值
	g_max = 10;//max初始值
	createTrackbar(TrackbarName, "效果图", &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);//阈值的滑动条
	createTrackbar(TrackbarName2, "效果图", &g_min, min_line, on_Trackbar);//min_line的滑动条
	createTrackbar(TrackbarName3, "效果图", &g_max, max_line, on_Trackbar);//max_line的滑动条
	on_Trackbar(g_nAlphaValueSlider, 0);

	printf("按ESC退出");
	while (waitKey(333) != 27) {}
	return 0;
}