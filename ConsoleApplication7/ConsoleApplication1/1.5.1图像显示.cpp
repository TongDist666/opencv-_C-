// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2/opencv.hpp>
using namespace cv;


int main()
{
	Mat img = imread("1.jpg");
	//Mat 图像存储数据结构，imread函数载入图像

	imshow("td", img);
	//imshow显示图像

	waitKey(6000);
	//等待按键按下，6000毫秒后或者有按键输入，就关闭
    return 0;
}

