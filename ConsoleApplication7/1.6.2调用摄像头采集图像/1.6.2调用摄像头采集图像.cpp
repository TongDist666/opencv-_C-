// 1.6.2调用摄像头采集图像.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
using namespace cv;


int main()
{
	//VideoCapture是opencv 2.X新增的，用于从摄像机或视频文件捕获视频
	//输入为字符串，就是视频文件捕获视频；输入为：0，就是摄像机捕获视频
	VideoCapture capture(0);

	while (1) {
		Mat frame;
		capture >> frame;//读取当前帧图像
		imshow("摄像头视频", frame);//显示当前帧
		waitKey(30);//延时30ms
	}
    return 0;
}

