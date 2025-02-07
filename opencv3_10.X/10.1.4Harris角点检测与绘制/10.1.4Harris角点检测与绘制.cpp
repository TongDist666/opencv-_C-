// 10.1.4Harris角点检测与绘制.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;

int main()
{
	system("color 3B");//背景暗靛色，字靛色

	Mat srcImage = imread("1.jpg", 0);
	imshow("harris角点检测原图", srcImage);

	Mat cornerStrength;
	cornerHarris(srcImage, cornerStrength, 2, 3, 0.01);
	/*
	cornerHarris(
	1 输入图像 必须为单通 8位或浮点型
	2 运算结果
	3 int 邻域大小
	4 int sobel算子孔径
	5 double Harris参数
	6 int 边界模式 默认BORDER_DEFAULT
	)
	*/

	Mat harrisCorner;
	threshold(cornerStrength, harrisCorner, 0.00001, 255, THRESH_BINARY);
	imshow("harris角点检测效果图", harrisCorner);

	printf("按q或ESC退出");
	while (waitKey(333) != 'q') {}
	return 0;
}
