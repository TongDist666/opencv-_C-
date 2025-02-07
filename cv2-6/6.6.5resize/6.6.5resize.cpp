// 6.6.5resize.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;

#define WIN_DST "resize效果图"
#define TRACK_X "x方向缩放"
#define TRACK_Y "y方向缩放"
#define TRACK_INTER "插值方式"

int x_0 = 10;
int x_max = 30;
void x_change(int, void*);

int y_0 = 10;
int y_max = 30;
void y_change(int, void*);

int inter_0 = INTER_LINEAR;
int inter_max = WARP_FILL_OUTLIERS;
void inter_change(int, void*);

Mat srcImage, dstImage;

int main()
{
	srcImage = imread("1.jpg");
	if (!srcImage.data) {
		printf("读取图片失败");
		return -1;
	}

	namedWindow(WIN_DST,WINDOW_NORMAL);
	imshow(WIN_DST, srcImage);
	createTrackbar(TRACK_X, WIN_DST, &x_0, x_max, x_change);
	createTrackbar(TRACK_Y, WIN_DST, &y_0, y_max, y_change);
	createTrackbar(TRACK_INTER, WIN_DST, &inter_0, inter_max, inter_change);
	x_change(x_0, 0);
	y_change(y_0, 0);
	inter_change(inter_0, 0);

	while (waitKey(0)!=27){}
    return 0;
}
void x_change(int, void*) {
	/*
	void resize( 
		InputArray src, //源图像
		OutputArray dst,//目标图像，非零时，有着dsize的尺寸或有src.size()计算出来
        Size dsize, //输出图像大小，=0时，dsize=size（round（fx * src.cols）,round（fy * src.rows））
		double fx = 0, //水平轴缩放系数  =0时取  （double）dsize.width/src.cols
		double fy = 0,//垂直轴缩放系数   =0时取  （double）dsize.height/src.rows
        int interpolation = INTER_LINEAR );//插值方式
			INTER_NEAREST		= 0,最近邻插值
			INTER_LINEAR		= 1,线性插值（默认）								放大 效率高，快
			INTER_CUBIC			= 2,三次样条插值（超过4X4像素邻域内的双三次插值）	放大 效率不高，慢
			INTER_AREA			= 3,区域插值（利用像素区域关系的重采样插值）		缩小 推荐使用
			INTER_LANCZOS4		= 4,Lanzos插值（超过8X8像素邻域内的Lanzos插值）
			INTER_LINEAR_EXACT	= 5,
			INTER_MAX			= 7,

	*/
	resize(srcImage, dstImage, Size(), double(x_0 )/ 10,double(y_0)/10,inter_0 );
	imshow("DST", dstImage);
	waitKey(0);
	destroyWindow("DST");
}
void y_change(int, void*) {
	resize(srcImage, dstImage, Size(), double(x_0 )/ 10, double(y_0 )/ 10, inter_0);
	imshow("DST", dstImage);
	waitKey(0);
	destroyWindow("DST");
}
void inter_change(int, void*) {
	resize(srcImage, dstImage, Size(), double(x_0 )/ 10, double(y_0 )/ 10, inter_0);
	imshow("DST", dstImage);
	waitKey(0);
	destroyWindow("DST");
}