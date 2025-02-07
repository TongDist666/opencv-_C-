// 6.3.2膨胀.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;

#define WIN_YUAN "膨胀操作原图"
#define WIN_XIAO "膨胀操作效果图"
#define WIN_SIZE "size"

Mat srcImage, dstImage, kernel;

void size_change(int, void*);
int size_0=3;//size（3，3）
int size_max = 20;

void iterations_change(int, void*);
int iteration_count=1;//迭代次数初值
int iteration_max = 10;

void size_change2(int, void*);
int size_time666 = 3;

int main()
{
	srcImage = imread("1.jpg");
	if (!srcImage.data) printf("图片读取错误！");
	namedWindow(WIN_XIAO);
	namedWindow(WIN_SIZE);
	imshow(WIN_YUAN, srcImage);

	createTrackbar("膨胀核尺寸", WIN_XIAO, &size_0, size_max, size_change);
	createTrackbar("迭代次数", WIN_XIAO, &iteration_count, iteration_max, iterations_change);
	createTrackbar("size", WIN_SIZE, &size_time666, 30, size_change2);
	size_change(size_0, 0);
	iterations_change(iteration_count, 0);
	size_change2(size_time666, 0);

	while (waitKey(0) != 27);
    return 0;
}
/*
void dilate( 
	InputArray src, //源图像，通道数任意数，深度：CV_8U,CV_16U,CV_16S,CV_32F,CV_64F
	OutputArray dst, //输出图像
	InputArray kernel,//膨胀操作内核，为NULL时，使用3x3    该变量一般用getStructuringElement获取
	Point anchor = Point(-1,-1), //锚点
	int iterations = 1,//迭代次数
	int borderType = BORDER_CONSTANT,
	const Scalar& borderValue = morphologyDefaultBorderValue() );
*/
void size_change(int, void*) {
	/*
	Mat getStructuringElement(
		int shape, //MORPH_RECT 矩形   MORPH_CROSS交叉形    MORPH_ELLIPSE椭圆形
		Size ksize, //内核尺寸   eg：3X3  要用size（2*3+1，2*3+1）
		Point anchor = Point(-1,-1));//锚点
	*/
	kernel = getStructuringElement(MORPH_RECT, Size(2 * size_0 + 1, 2 * size_0 + 1));
	dilate(srcImage, dstImage, kernel, Point(-1, -1), iteration_count);
	imshow(WIN_XIAO, dstImage);
}
void iterations_change(int, void*) {
	kernel = getStructuringElement(MORPH_RECT, Size(2 * size_0 + 1, 2 * size_0 + 1));
	dilate(srcImage, dstImage, kernel, Point(-1, -1), iteration_count);
	imshow(WIN_XIAO, dstImage);
}
void size_change2(int, void*) {
	kernel = getStructuringElement(MORPH_RECT, Size(size_time666, size_time666));
	dilate(srcImage, dstImage, kernel, Point(-1, -1), iteration_count);
	imshow(WIN_SIZE, dstImage);
}
