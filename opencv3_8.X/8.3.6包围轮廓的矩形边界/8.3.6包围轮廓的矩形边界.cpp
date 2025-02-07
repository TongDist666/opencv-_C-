// 8.3.6包围轮廓的矩形边界.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\highgui\highgui.hpp>//imshow,waitKey
#include<opencv2\imgproc\imgproc.hpp>//minAreaRect,circle,line
#include<Windows.h>
using namespace cv;
using namespace std;

int main()
{
	system("color 1C");//背景深一点的蓝色，红色的字
	
	//初始化变量和随机值
	Mat image(600, 600, CV_8UC3);
	RNG& rng = theRNG();

	printf("按ESC退出，按其他任意键更新点");

	//循环，按下ESC键程序退出，否则每1秒更新
	while (waitKey(333) != 27) {
		int count = rng.uniform(3, 103);//随机生成点的数量
		vector<Point> points;//点值

		//随机生成点坐标
		for (int i = 0; i < count; i++) {
			Point point;
			point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
			point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);

			points.push_back(point);
		}

		//对给定的 2D 点集，寻找最小面积的包围矩形
		RotatedRect box = minAreaRect(Mat(points));
		//minAreaRect(2D点集 mat或std：：vector)

		Point2f vertex[4];
		box.points(vertex);

		//绘制出随机颜色的点
		image = Scalar::all(0);
		for (int i = 0; i < count; i++)
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);//相当于画小的实心圆
		
		//绘制出最小面积的包围矩形
		for (int i = 0; i < 4; i++) 
			line(image,vertex[i],vertex[(i+1)%4],Scalar(100,200,211),2,LINE_AA);
		
		imshow("矩形包围示例", image);
		Sleep(2000);
	}
    return 0;
}

