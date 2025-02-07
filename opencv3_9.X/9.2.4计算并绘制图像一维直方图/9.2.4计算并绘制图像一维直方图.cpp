// 9.2.4计算并绘制图像一维直方图.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>//cout
using namespace cv;
using namespace std;

int main()
{	
	system("color 8C");//背景暗一点的灰色，字红色

	Mat srcImage = imread("1.jpg", 0);
	imshow("原图", srcImage);
	if (!srcImage.data) { cout << "fail to load image" << endl; 	return 0; }


	//【2】定义变量
	MatND dstHist;       // 在cv中用CvHistogram *hist = cvCreateHist
	int dims = 1;
	float hranges[] = { 0, 255 };
	const float *ranges[] = { hranges };   // 这里需要为const类型
	int size = 256;
	int channels = 0;

	//【3】计算图像的直方图
	calcHist(&srcImage, 1, &channels, Mat(), dstHist, dims, &size, ranges);    // cv 中是cvCalcHist
	int scale = 1;

	Mat dstImage(size * scale, size, CV_8U, Scalar(0));
	//【4】获取最大值和最小值
	double minValue = 0;
	double maxValue = 0;
	minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);  
	//  在cv中用的是cvGetMinMaxHistValue

	//【5】绘制出直方图
	int hpt = saturate_cast<int>(0.9 * size);
	for (int i = 0; i < 256; i++)
	{
		float binValue = dstHist.at<float>(i);           
		//   注意hist中是float类型    而在OpenCV1.0版中用cvQueryHistValue_1D
		
		int realValue = saturate_cast<int>(binValue * hpt / maxValue);
		rectangle(dstImage, Point(i*scale, size - 1), Point((i + 1)*scale - 1, size - realValue), Scalar(255));
	}
	imshow("一维直方图", dstImage);
	
	printf("按ESC退出");
	while (waitKey(333) != 27) {}
	return 0;
}