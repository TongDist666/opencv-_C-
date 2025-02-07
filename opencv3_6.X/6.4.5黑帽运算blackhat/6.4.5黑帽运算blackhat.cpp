// 6.4.5黑帽运算blackhat.cpp: 定义控制台应用程序的入口点。
//黑帽：闭运算和原图之差，突出了比原图轮廓周围区域更暗的地方，用来分离比邻近点暗一点的斑块

#include "stdafx.h"
#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main()
{
	system("color 9F");//亮一点的蓝色

	Mat image = imread("1.jpg");
	namedWindow("【原始图】黑帽运算", WINDOW_NORMAL);
	namedWindow("【效果图】黑帽运算", WINDOW_NORMAL);

	imshow("【原始图】黑帽运算", image);
	//定义核
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));
	//进行黑帽运算
	morphologyEx(image, image, MORPH_BLACKHAT, element);

	imshow("【效果图】黑帽运算", image);

	printf("按q键退出");
	while (char(waitKey(333)) != 'q') {}
	return 0;
}