// 1.6.2_2摄像头配合canny边缘检测.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
using namespace cv;


int main()
{
	VideoCapture capture(0);
	Mat edges;

	while (1) {
		Mat frame;
		capture >> frame;//读取当前帧图像

		//转化BGR彩色图为灰度图
		cvtColor(frame,edges,CV_BGR2GRAY);

		//使用3*3内核降噪（2*3+1=7）
		blur(edges,edges,Size(7,7));//进行模糊

		//进行canny边缘检测
		Canny(edges,edges,0,30,3);
		imshow("canny处理摄像头视频", edges);//显示当前帧
		waitKey(30);//延时30ms
	}
    return 0;
}

