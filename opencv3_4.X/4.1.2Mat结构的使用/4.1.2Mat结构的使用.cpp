// 4.1.2Mat结构的使用.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
using namespace cv;

//Mat类型是一个类，由两个数据部分构成：矩阵头（包含矩阵尺寸，存储方法，存储地址等信息）和指向存储所有像素值矩阵的指针
//大图复制影响运行速度


int main()
{
	/*
	Mat a, b;/仅创建信息头
	a = imread("i.jpg", CV_LOAD_IMAGE_COLOR);/为矩阵开辟内存
	Mat c(a);/使用拷贝构造函数
	b = a;/赋值
	以上两种方法只复制信息头和矩阵指针，不复制矩阵
	
	想要复制矩阵本身要用 clone（）或copyTo（）

	eg：b=a.clone()  or  a.copyTo(b)

	创建感兴趣区域ROI
	1:使用矩形定义
	Mat b(a,RECT(10,10,100,100));
	2:使用行和列定义
	Mat c=a(Range:all(),Range(1,3));
	*/
    return 0;
}

