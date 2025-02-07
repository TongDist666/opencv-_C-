// 4.3-1图形绘制.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;


int main()
{

	Mat src = Mat::zeros(600,600,CV_8UC3);

	/*画椭圆
	void ellipse(
		InputOutputArray img, //输入输出图像图像
		Point center, //椭圆圆心
		Size axes,//椭圆大小
        double angle, //椭圆旋转角度 顺时针转
		double startAngle,// 画图像的起始角坐标 
		double endAngle,//画图像的结束角坐标      这两个值互换位置不影响  逆时针画
        const Scalar& color,// 图像颜色
		int thickness = 1,//线条粗细
        int lineType = LINE_8,//线性  4——4联通 ；8——8联通；LINE_AA——抗锯齿 
		int shift = 0);//缩小比例
	*/
	ellipse(src, Point(300, 300), Size(150, 600 / 16), 45, 270, 0, Scalar(255, 0, 0), 2, 8);
	ellipse(src, Point(300, 300), Size(120, 80), 45, 30, 180, Scalar(255, 0, 0), 2, 8,1);
	ellipse(src, Point(300, 300), Size(120, 80), 45, 30, 180, Scalar(255, 0, 0), 2, 8, 2);
	ellipse(src, Point(300, 300), Size(120, 80), 45, 30, 180, Scalar(255, 0, 0), 2, 8, 3);
	ellipse(src, Point(300, 300), Size(150, 600 / 16), 15, 0, 360, Scalar(0, 255, 0), 2, 8);


	/*画圆
	void circle(
		InputOutputArray img, //输入输出图像
		Point center, //圆心坐标
		int radius,//半径
        const Scalar& color,//线条颜色 
		int thickness = 1,//线宽
        int lineType = LINE_8, //线性
		int shift = 0);//缩小比例
	*/
	circle(src,Point(50,50),25,Scalar(0,0,255),2,8);
	circle(src, Point(150, 150), 35, Scalar(0, 0, 255), -1, 8);
	circle(src, Point(150, 150), 35, Scalar(0, 0, 255), -1, 8,1);

	/*画多边形
	void fillPoly(
		Mat& img, //输入输出图像
		const Point** pts,//顶点集
		const int* npts, //定点个数
		int ncontours,//绘制多边形个数
		const Scalar& color, //线条颜色
		int lineType = LINE_8, //线型
		int shift = 0,//
		Point offset = Point() );//
		注意各类型的定义方法
	*/
	Point poly[1][3];
	poly[0][0] = Point(1, 1);
	poly[0][1] = Point(1,22);
	poly[0][2] = Point(33, 1);
	const Point* ppt[1] = { poly[0] };
	int npt[] = { 3 };
	fillPoly(src, ppt, npt,1,Scalar(255,255,255),8);

	/*画线条
	void line(
		InputOutputArray img, //输入输出图像
		Point pt1, //线条起点
		Point pt2, //线条终点
		const Scalar& color,//线条颜色
		int thickness = 1, //线宽
		int lineType = LINE_8, //线性
		int shift = 0);//缩小比例
	*/
	line(src,Point(33,44),Point(550,66),Scalar(255,255,255),8);
	line(src, Point(33, 144), Point(550, 166), Scalar(255, 255, 255), 3, LINE_AA);

	imshow("绘图",src);

	waitKey(0);
	return 0;
}

