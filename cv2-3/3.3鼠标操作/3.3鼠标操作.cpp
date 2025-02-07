// 3.3鼠标操作.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
using namespace cv;

#define WINDOW_NAME "鼠标操作"

void onMouse(int event,int x,int y,int flags,void* param);
void drawRect(cv::Mat& img,cv::Rect box);

Rect draw_box;
bool draw_ornot;
RNG rng(12345);
int main()
{
	draw_box = Rect(-1, -1, 0, 0);
	Mat srcImage(600, 900, CV_8UC3), tempImage;
	srcImage.copyTo(tempImage);
	srcImage = Scalar::all(0);

	namedWindow(WINDOW_NAME);
	setMouseCallback(WINDOW_NAME, onMouse, (void*)&srcImage);

	while (1) {
		srcImage.copyTo(tempImage);//拷贝源图到临时变量
		if (draw_ornot) drawRect(tempImage, draw_box);//当进行绘制的标识符为真，则进行绘制
		imshow(WINDOW_NAME, tempImage);
		if (waitKey(10) == 27) break;//按下ESC键，程序退出
	}
	return 0;
}

/*int main()
{
	draw_box = Rect(-1, -1, 0, 0);
	Mat srcImage(600, 900, CV_8SC3), tempImage;
	srcImage.copyTo(tempImage);
	srcImage = Scalar::all(0);

	namedWindow(WINDOW_NAME);
	setMouseCallback(WINDOW_NAME,onMouse,(void*)&srcImage);

	while (1) {
		srcImage.copyTo(tempImage);
		if (draw_ornot) drawRect(tempImage, draw_box);
		imshow(WINDOW_NAME,tempImage);
		if (waitKey(10) == 27) break;
	}
    return 0;
}*/
void onMouse(int event, int x, int y, int flags, void* param) {
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
			draw_box.width = x - draw_box.x;
			draw_box.height = y - draw_box.y;
		}
		break;

		//左键按下消息
	case EVENT_LBUTTONDOWN:
	{
		draw_ornot = true;
		draw_box = Rect(x, y, 0, 0);//记录起始点
	}
	break;

	//左键抬起消息
	case EVENT_LBUTTONUP: {
		draw_ornot = false;//置标识符为false
							  //对宽和高小于0的处理
		if (draw_box.width < 0) {
			draw_box.x += draw_box.width;
			draw_box.width *= -1;
		}
		if (draw_box.height < 0) {
			draw_box.y += draw_box.height;
			draw_box.height *= -1;
		}
		printf("---------矩形---------\n");
		printf("矩形左上角x坐标：%d \n矩形左上角y坐标：%d \n矩形宽：%d 矩形高：%d\n", draw_box.x, draw_box.y, draw_box.width, draw_box.height);
		printf("矩形左上角坐标：（%d,%d）    矩形右上角坐标：（%d,%d）\n", draw_box.x, draw_box.y, draw_box.x + draw_box.width, draw_box.y);
		printf("矩形左下角坐标：（%d,%d）    矩形右下角坐标：（%d,%d）\n", draw_box.x, draw_box.y + draw_box.height, draw_box.x + draw_box.width, draw_box.y + draw_box.height);
		printf("x坐标：%d y坐标：%d\n", x_0, y_0);
		printf("---------矩形---------\n");
		//调用函数进行绘制
		drawRect(image, draw_box);
	}
	default:
		break;
	}
}
/*void onMouse(int event, int x, int y, int flags, void* param) {
	Mat& image = *(cv::Mat *) param;
	int x_0 = x;
	int y_0 = y;
	printf("x坐标：%d，y坐标：%d\n",x,y);
	switch(event) {
		case EVENT_MOUSEMOVE:
			if (draw_ornot) {
				draw_box.width = x - draw_box.x;
				draw_box.height = y - draw_box.y;
			}
			break; 
		case EVENT_LBUTTONDOWN:
			{	
				draw_ornot = true;
				draw_box = Rect(x, y, 0, 0);
			}
			break;

		case EVENT_LBUTTONUP: {
			draw_ornot = false;
			if (draw_box.width < 0) {
				draw_box.x += draw_box.width;
				draw_box.width *= -1;
			}
			if (draw_box.height < 0) {
				draw_box.y += draw_box.height;
				draw_box.height *= -1;
			}
			printf("-----矩形-----\n");
			printf("矩形左上角x坐标：%d 矩形左上角y坐标：%d 矩形宽：%d 矩形高：%d\n", draw_box.x, draw_box.y, draw_box.width, draw_box.height);
			printf("矩形左上角坐标：（%d,%d） 矩形右上角坐标：（%d,%d）\n", draw_box.x, draw_box.y, draw_box.x + draw_box.width, draw_box.y);
			printf("矩形左下角坐标：（%d,%d） 矩形右下角坐标：（%d,%d）\n", draw_box.x, draw_box.y + draw_box.height, draw_box.x + draw_box.width, draw_box.y + draw_box.height);
			printf("x坐标：%d y坐标：%d\n", x_0, y_0);
			printf("-----矩形-----\n");
			//调用函数进行绘制
			drawRect(image, draw_box);
		}
		default:
			break;
	}
}*/
void drawRect(cv::Mat& img, cv::Rect box) {
	rectangle(img, box.tl(), box.br(), Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)));
}