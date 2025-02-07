// 7.2.4标准霍夫变换HoughLines函数.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<imgproc\imgproc.hpp>
using namespace cv;
using namespace std;

const int g_nMaxAlphaValue = 200;//Alpha值的最大值
int g_nAlphaValueSlider=66;//滑动条对应的变量
Mat midImage, dstImage;
vector<Vec2f> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合


void on_Trackbar(int, void *) {
	HoughLines(midImage, lines, 1, CV_PI / 180, g_nAlphaValueSlider, 0, 0);
	Mat dstimge;
	dstImage.copyTo(dstimge);
	//依次在图中绘制出每条线段
	for (size_t i = 0; i < lines.size(); i++) {
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		line(dstimge, pt1, pt2, Scalar(55, 100, 195), 1, LINE_AA);
		//Scalar(G,B,R)控制颜色
	}
	imshow("效果图", dstimge);
}

int main()
{
	system("color 9E");//背景亮蓝色，字是黄色

	Mat srcImage = imread("1.jpg");
	
	Canny(srcImage, midImage, 50, 200, 3);//进行一次canny边缘检测
	cvtColor(midImage, dstImage, CV_GRAY2BGR);//转化为灰度图

	imshow("原始图", srcImage);
	imshow("边缘检测后的图", midImage);
	namedWindow("效果图", WINDOW_NORMAL);
	
	//滑动条设置
	char TrackbarName[50];//滑动条名称
	sprintf_s(TrackbarName, "阈值 %d", g_nMaxAlphaValue);
	createTrackbar(TrackbarName, "效果图", &g_nAlphaValueSlider, g_nMaxAlphaValue, on_Trackbar);
	on_Trackbar(g_nAlphaValueSlider, 0);

	printf("按ESC退出");
	while(waitKey(333)!=27){}
    return 0;
}

