// 6.1.12线性滤波.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;
using namespace std;

#define WIN_BOX "方框滤波"
#define WIN_BLUR "均值滤波"
#define WIN_GAUSSIAN "高斯滤波"

void box_change(int, void*);
int box_value = 3;
void blur_change(int, void*);
int blur_value = 3;
void gaussian_change(int, void*);
int gaussian_value = 3;

Mat srcImage, dstbox, dstblur, dstGaussian;

int main()
{
	srcImage = imread("1.jpg");
	dstblur = srcImage.clone();
	dstbox = srcImage.clone();
	dstGaussian = srcImage.clone();

	namedWindow(WIN_BOX, 1);
	namedWindow(WIN_BLUR, 1);
	namedWindow(WIN_GAUSSIAN, 1);

	createTrackbar("方框滤波 内核数：", WIN_BOX, &box_value, 30, box_change);
	createTrackbar("均值滤波 内核数：", WIN_BLUR, &blur_value, 30, blur_change);
	createTrackbar("高斯滤波 内核数：", WIN_GAUSSIAN, &gaussian_value, 30, gaussian_change);
	box_change(box_value,0);
	blur_change(blur_value, 0);
	gaussian_change(gaussian_value, 0);

	while(waitKey(0)!=27){}
    return 0;
}
void box_change(int, void*) {
	boxFilter(srcImage, dstbox, -1, Size(box_value + 1, box_value + 1),Point(-1,-1));
	/*
	void boxFilter( 
		InputArray src, //输入图像 对通道单独处理，任意通道数 深度必须为：CV_8U,CV_16U,CV_32F,CV_64F
		OutputArray dst, //输出图像
		int ddepth,//深度 -1表示用src的深度
        Size ksize, //内核大小
		Point anchor = Point(-1,-1),//锚点（被平滑的点），point（-1，-1）表示核的中心
        bool normalize = true,//内核是否被其区域归一化   归一化就变成了均值滤波
        int borderType = BORDER_DEFAULT );
	*/
	imshow(WIN_BOX, dstbox);
}
void blur_change(int, void*) {
	blur(srcImage, dstblur, Size(blur_value + 1, blur_value + 1),Point(-1,-1));
	/*
	void blur( 
		InputArray src, //输入图像 对通道单独处理，任意通道数 深度必须为：CV_8U,CV_16U,CV_32F,CV_64F
		OutputArray dst,//输出图像
        Size ksize, //内核大小
		Point anchor = Point(-1,-1),//锚点（被平滑的点），point（-1，-1）表示核的中心
        int borderType = BORDER_DEFAULT );
	*/
	imshow(WIN_BLUR, dstblur);
}
void gaussian_change(int, void*) {
	GaussianBlur(srcImage, dstGaussian, Size(gaussian_value * 2 + 1, gaussian_value * 2 + 1),0,0);
	/*
	void GaussianBlur( 
		InputArray src, //输入图像 对通道单独处理，任意通道数 深度必须为：CV_8U,CV_16U,CV_32F,CV_64F
		OutputArray dst, //输出图像
		Size ksize,//高斯内核尺寸，width可以不等于height，但必须为正奇数或0。 内核值为a，则size（2a+1，2a+1）
		double sigmaX, //高斯核函数在x方向的标准偏差
		double sigmaY = 0,//高斯核函数在y方向的标准偏差 若sigmaY=0，则sigmaY=sigmaX；若sigmaX=sigmaY=0，则由ksize计算出来
		int borderType = BORDER_DEFAULT );
	*/
	imshow(WIN_GAUSSIAN, dstGaussian);
}