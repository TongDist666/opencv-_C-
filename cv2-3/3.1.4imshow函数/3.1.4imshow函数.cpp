// 3.1.4imshow函数.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2/core/core.hpp>
#include<opencv2\highgui\highgui.hpp>//imread,imshow,waitKey
using namespace cv;


int main()
{
	system("color 7A");//背景灰白色，字绿色
	printf("hello");

	//Mat imread(const string& filename,int flag=1);
	//第一个参数 const string&类型，即图片路径
	//	支持：Windows位图：*.bmp,*.dib
	//		     JPEG文件：*.jpeg,*.jpg,*.jpe
	//		 JPEG2000文件：*.jp2
	//		      PNG图片：*.png
	//       便携文件格式：*.pbm,*.pgm,*.ppm
	//sun rasters光栅文件：*.sr,*.ras
	//           TIFF文件：*.tiff,*.tif

	//第二个参数： int类型flag，制定加载图像的颜色类型,默认为1
	//CV_LOAD_IMAGE_UNCHANGED = -1 
	//CV_LOAD_IMAGE_GRAYSCALE = 0 图像转化为灰度
	//CV_LOAD_IMAGE_COLOR = 1 转换到彩色
	//CV_LOAD_IMAGE_ANYDEPTH = 2 若图像深度为16或32位，返回相应深度；否则返回8位图像
	//CV_LOAD_IMAGE_ANYCOLOR = 4
	//输入有冲突的标志，将采用较小数字值
	//最真实无损的原图像用：CV_LOAD_IMAGE_ANYDEPTH|CV_LOAD_IMAGE_ANYCOLOR	即2|4

	//或者flag>0,返回三通道彩色图像；flag=0返回灰度图像；flag>0，返回包含Alpha通道的图像

	//注意，以彩色模式载入图形，解码后图像会以BGR（蓝，绿，红）的通道顺序进行存储，而不是通常的RGB顺序。
	Mat img_UNCHANGED = imread("1.jpg", CV_LOAD_IMAGE_UNCHANGED);
	Mat img_GRAYSCALE = imread("1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	Mat img_COLOR = imread("1.jpg", CV_LOAD_IMAGE_COLOR);
	Mat img_ANYDEPTH = imread("1.jpg", CV_LOAD_IMAGE_ANYDEPTH);
	Mat img_ANYCOLOR = imread("1.jpg", CV_LOAD_IMAGE_ANYCOLOR);

	//对于imshow函数  void imshow(const string& winname,InputArray mat);
	//第一个参数 const string&类型,即窗口标识名
	//第二个参数是mat类型变量，即要显示的图片
	//注意：
	//1）如果载入图像是8位无符号类型（8-bit unsigned）,就显示原图
	//2）如果是16位无符号数（16 - bit unsigned）或32位整数（32-bit ineger），就用像素值除以256，也就是把值的范围从【0，255*256】映射到【0，255】
	//3）如果图像是32位浮点类型（32-bit floating-point），像素要乘以256，即把值的范围从【0，1】映射到【0，255】

	imshow("CV_LOAD_IMAGE_UNCHANGED = -1", img_UNCHANGED);
	imshow("CV_LOAD_IMAGE_GRAYSCALE = 0", img_GRAYSCALE);
	imshow("CV_LOAD_IMAGE_COLOR = 1", img_COLOR);
	imshow("CV_LOAD_IMAGE_ANYDEPTH = 2", img_ANYDEPTH);
	imshow("CV_LOAD_IMAGE_ANYCOLOR = 4", img_ANYCOLOR);
	
	while (waitKey(0) != 27) {}
	return 0;
}
