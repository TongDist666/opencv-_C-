// 3.3鼠标操作.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
using namespace cv;

#define WINDOW_NAME "[鼠标操作]"//窗口名称

void on_MouseHandle(int event,int x,int y,int flags,void* param);
void DrawRectangle(cv::Mat& img, cv::Rect box);

Rect g_rectangle;
bool draw_ornot = false;
RNG g_rng(12345);

int main()
{
	//【1】准备参数
	g_rectangle = Rect(-1, -1, 0, 0);
	Mat srcImage(600, 900,CV_8UC3), tempImage;
	srcImage.copyTo(tempImage);
	g_rectangle = Rect(-1, -1, 0, 0);
	srcImage = Scalar::all(0);

	//【2】设置鼠标操作回调函数
	namedWindow(WINDOW_NAME);
	setMouseCallback(WINDOW_NAME, on_MouseHandle, (void*)&srcImage);

	//【3】程序主循环，当进行绘制的标识符为真时，进行绘制
	while (1) {
		srcImage.copyTo(tempImage);//拷贝源图到临时变量
		if (draw_ornot) DrawRectangle(tempImage, g_rectangle);//当进行绘制的标识符为真，则进行绘制
		imshow(WINDOW_NAME, tempImage);
		if (waitKey(10) == 27) break;//按下ESC键，程序退出
	}
    return 0;
}

void on_MouseHandle(int event, int x, int y, int flags, void* param) {
	Mat& image = *(cv::Mat*) param;
	int x_0 = x;
	int y_0 = y;
	printf("x坐标：%d y坐标：%d\n", x, y);
	switch (event)
	{
		//鼠标移动消息
	case EVENT_MOUSEMOVE:
		//printf("x坐标：%d y坐标：%d\n",x,y);
		if (draw_ornot) //如果是否进行绘制的标识符为真，则记录下长和宽到RECT型变量中
		{
			g_rectangle.width = x - g_rectangle.x;
			g_rectangle.height = y - g_rectangle.y;
		}
		break;

		//左键按下消息
	case EVENT_LBUTTONDOWN:
		{
			draw_ornot = true;
			g_rectangle = Rect(x, y, 0, 0);//记录起始点
		}
		break;

		//左键抬起消息
	case EVENT_LBUTTONUP: {
		draw_ornot = false;//置标识符为false
		//对宽和高小于0的处理
		if (g_rectangle.width < 0) {
			g_rectangle.x += g_rectangle.width;
			g_rectangle.width *= -1;
		}
		if (g_rectangle.height < 0) {
			g_rectangle.y += g_rectangle.height;
			g_rectangle.height *= -1;
		}
		printf("-----矩形-----\n");
		printf("矩形左上角x坐标：%d 矩形左上角y坐标：%d 矩形宽：%d 矩形高：%d\n",g_rectangle.x,g_rectangle.y,g_rectangle.width,g_rectangle.height);
		printf("矩形左上角坐标：（%d,%d） 矩形右上角坐标：（%d,%d）\n", g_rectangle.x, g_rectangle.y, g_rectangle.x+g_rectangle.width, g_rectangle.y);
		printf("矩形左下角坐标：（%d,%d） 矩形右下角坐标：（%d,%d）\n", g_rectangle.x, g_rectangle.y+g_rectangle.height, g_rectangle.x+g_rectangle.width, g_rectangle.y+g_rectangle.height);
		printf("x坐标：%d y坐标：%d\n", x_0, y_0);
		printf("-----矩形-----\n");
		//调用函数进行绘制
		DrawRectangle(image, g_rectangle);
	}
	default:
		break;
	}
}

void DrawRectangle(cv::Mat& img, cv::Rect box) {
	rectangle(img, box.tl(), box.br(), Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255)));
}