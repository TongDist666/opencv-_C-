// 1.6.1读取并播放视频.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
using namespace cv;


int main()
{
	/*VideoCapture是opencv 2.X新增的，用于从摄像机或视频文件捕获视频
	1. 先实例化再初始化
	VideoCapture capture;
	capture.open("1.mp4");
	2.实例化时同时初始化
	VideoCapture capture("1.mp4");
	*/

	//一.读入视频
	VideoCapture capture("1.mp4");

	//二.循环显示每一帧
	while (1) {
		Mat frame;
		capture >> frame;//读取当前帧图像

		//若视频播放完成，退出循环
		if (frame.empty()) {
			break;
		}
		imshow("读取视频", frame);//显示当前帧
		waitKey(60);//延时60ms
	}
    return 0;
}
