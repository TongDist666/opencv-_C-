// 8.4.4查找和绘制图像轮廓矩.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "【原始图】"	
#define WINDOW_NAME2 "【图像轮廓】" 

Mat g_srcImage; Mat g_grayImage;
int g_nThresh = 100;
int g_nMaxThresh = 255;
RNG g_rng(12345);
Mat g_cannyMat_output;
vector<vector<Point> > g_vContours;
vector<Vec4i> g_vHierarchy;

void on_ThreshChange(int, void*);

int main(int argc, char** argv)
{
	system("color 4C");//背景猩红色，字红色

	// 读入原图像, 返回3通道图像数据
	g_srcImage = imread("1.jpg", 1);

	// 把原图像转化成灰度图像并进行平滑
	cvtColor(g_srcImage, g_grayImage, COLOR_BGR2GRAY);
	blur(g_grayImage, g_grayImage, Size(3, 3));

	// 创建新窗口
	namedWindow(WINDOW_NAME1, WINDOW_AUTOSIZE);
	namedWindow(WINDOW_NAME2, WINDOW_NORMAL);
	imshow(WINDOW_NAME1, g_srcImage);

	//创建滚动条并进行初始化
	createTrackbar(" 阈值", WINDOW_NAME2, &g_nThresh, g_nMaxThresh, on_ThreshChange);
	on_ThreshChange(0, 0);

	waitKey(0);
	return(0);
}

void on_ThreshChange(int, void*)
{
	// 使用Canndy检测边缘
	Canny(g_grayImage, g_cannyMat_output, g_nThresh, g_nThresh * 2, 3);

	// 找到轮廓
	findContours(g_cannyMat_output, g_vContours, g_vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0));

	// 计算矩
	vector<Moments> mu(g_vContours.size());
	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		mu[i] = moments(g_vContours[i], false);
		/*计算多边形和光栅形状的最高达3阶的所有矩
		moments(
			1 输入参数 可以是光栅图像（单通 8位或浮点的二维数组）或二维数组（1N或N1）
			2 bool 默认false 取TRUE时所有非零像素置为1（仅对图像使用）
		)
		函数返回运行结果
		*/
	}

	//  计算中心矩
	vector<Point2f> mc(g_vContours.size());
	for (unsigned int i = 0; i < g_vContours.size(); i++)
	{
		mc[i] = Point2f(static_cast<float>(mu[i].m10 / mu[i].m00), static_cast<float>(mu[i].m01 / mu[i].m00));
	}

	// 绘制轮廓
	Mat drawing = Mat::zeros(g_cannyMat_output.size(), CV_8UC3);
	for (unsigned int i = 0; i< g_vContours.size(); i++)
	{
		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));//随机生成颜色值
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());//绘制外层和内层轮廓
		circle(drawing, mc[i], 4, color, -1, 8, 0);;//绘制圆
	}

	// 显示到窗口中
	namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME2, drawing);

	// 通过m00计算轮廓面积并且和OpenCV函数比较
	printf("\t 输出内容: 面积和轮廓长度\n");
	for (unsigned int i = 0; i< g_vContours.size(); i++)
	{
		printf(" >通过m00计算出轮廓[%d]的面积: (M_00) = %.2f \n OpenCV函数计算出的面积=%.2f , 长度: %.2f \n\n", i, mu[i].m00, contourArea(g_vContours[i]), arcLength(g_vContours[i], true));
		/*计算轮廓面积
		contourArea（输入向量 mat或std：：vector，bool 默认false—面积绝对值  为TRUE轮廓顺逆时针决定面积正负）

		计算封闭轮廓或曲线长度
		arcLength（输入 二维点集mat或std：：vector，bool类型的closed，默认TRUE曲线封闭）
		*/

		Scalar color = Scalar(g_rng.uniform(0, 255), g_rng.uniform(0, 255), g_rng.uniform(0, 255));
		drawContours(drawing, g_vContours, i, color, 2, 8, g_vHierarchy, 0, Point());
		circle(drawing, mc[i], 4, color, -1, 8, 0);
	}
}