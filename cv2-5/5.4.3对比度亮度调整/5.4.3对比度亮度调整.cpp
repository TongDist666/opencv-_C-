// 5.4.3对比度亮度调整.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
using namespace cv;
using namespace std;

#define WINDOW_NAME "对比度亮度调整"

void on_change(int,void*);

int duibi, liang;
Mat srcImage, dstImage;

int main()
{
	srcImage = imread("1.jpg");
	if (!srcImage.data) { printf("图片读取错误"); return false; }
	dstImage = Mat::zeros(srcImage.size(),srcImage.type());

	duibi = liang = 80;

	namedWindow(WINDOW_NAME, 1);
	createTrackbar("对比度", WINDOW_NAME, &duibi, 300, on_change);
	createTrackbar("亮度", WINDOW_NAME, &liang, 200, on_change);
	on_change(80, 0);

	while(waitKey(0)!=27){}
    return 0;
}

void on_change(int, void*) {
	for (int x = 0; x < srcImage.rows; x++) {
		for (int y = 0; y < srcImage.cols; y++) {
			for (int c = 0; c < 3; c++) {
				dstImage.at<Vec3b>(x, y)[c] = static_cast<uchar>((duibi*0.01)*(srcImage.at<Vec3b>(x, y)[c]) + liang);
				//此处 static_cast<uchar>表示  后边值必须在uchar范围内，即最大为255
			}
		}
	}
	imshow(WINDOW_NAME, dstImage);
}