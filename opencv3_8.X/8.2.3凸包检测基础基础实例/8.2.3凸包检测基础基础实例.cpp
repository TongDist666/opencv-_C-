// 8.2.3凸包检测基础基础实例.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
using namespace cv;
using namespace std;

static void ShowHelpText()
{
	printf("\n\t按键操作说明: \n\n"
		"\t\t键盘按键【ESC】、【Q】、【q】- 退出程序\n\n"
		"\t\t键盘按键任意键 - 重新生成随机点，并进行凸包检测\n");
}

int main()
{
	system("color 9D");//蓝色背景，字粉色

	ShowHelpText();

	//初始化变量和随机值
	Mat image(600, 600, CV_8UC3);
	RNG& rng = theRNG();

	//循环，按下ESC,Q,q键程序退出，否则有键按下便一直更新
	while (1)
	{
		//参数初始化
		char key;//键值
		int count = (unsigned)rng % 100 + 3;//随机生成点的数量
		vector<Point> points; //点值

							  //随机生成点坐标
		for (int i = 0; i < count; i++)
		{
			Point point;
			point.x = rng.uniform(image.cols / 4, image.cols * 3 / 4);
			point.y = rng.uniform(image.rows / 4, image.rows * 3 / 4);

			points.push_back(point);
		}

		//检测凸包
		vector<int> hull;
		convexHull(Mat(points), hull, true);
		/*
		convexHull（
			1 输入二维点集 Mat或std：：vector
			2 输出 找到的凸包
			3 bool 操作方向标识符 TRUE凸包为顺时针。假定x轴向右，y轴向上
			4 bool 操作标识符 默认TRUE 返回凸包各个点/false返回各点指数，当输入为std：：vector忽略此标志
		）
		*/

		//绘制出随机颜色的点
		image = Scalar::all(0);
		for (int i = 0; i < count; i++)
			circle(image, points[i], 3, Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), FILLED, LINE_AA);

		//准备参数
		int hullcount = (int)hull.size();//凸包的边数
		Point point0 = points[hull[hullcount - 1]];//连接凸包边的坐标点

		//绘制凸包的边
		for (int i = 0; i < hullcount; i++)
		{
			Point point = points[hull[i]];
			line(image, point0, point, Scalar(255, 255, 255), 2, LINE_AA);
			point0 = point;
		}

		//显示效果图
		imshow("凸包检测示例", image);

		//按下ESC,Q,或者q，程序退出
		key = (char)waitKey();
		if (key == 27 || key == 'q' || key == 'Q')
			break;
	}

	return 0;
}