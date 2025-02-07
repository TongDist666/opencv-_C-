// 3.1.7创建窗口namedWindow.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
using namespace cv;


int main()
{
	system("color 8A");//背景黑灰色，字绿色
	printf("hello");

	//滑动条必须先创建窗口，再把滑动条依附在窗口上，再显示

	//函数原型:  void namedWindow(const string& winname,int flag=WINDOW_AUTOSIZE);
	//第一个参数 const string&类型窗口名，不可重名
	//第二个参数 int类型flag
	//WINDOW_AUTOSIZE,窗口大小不可改变，为默认值
	//WINDOW_NORMAL，窗口大小可变
	//WINDOW_OPENGL窗口支持opengl
	namedWindow("WINDOW_NORMAL", WINDOW_NORMAL);
	namedWindow("WINDOW_AUTOSIZE", WINDOW_AUTOSIZE);
	//namedWindow("WINDOW_OPENGL", WINDOW_OPENGL);//不支持opengl，可能有点问题
	Mat a = imread("1.jpg");
	Mat b = imread("1.jpg");
	//Mat c = imread("1.jpg");
	imshow("WINDOW_NORMAL", a);
	imshow("WINDOW_AUTOSIZE", b);
	//imshow("WINDOW_OPENGL", c);
	//多个imshow函数不能共同占用一个mat，会出错

	while (waitKey(0) != 27) {}
	return 0;
}