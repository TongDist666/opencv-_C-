// 4.1.4显式创建MAT.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\core\core.hpp>
#include<iostream>
using namespace cv;
using namespace std;

int main()
{
	//[方法一]使用Mat（）构造函数

	//   行 列 数据类型  Scalar是个短向量

	Mat A(2, 2, CV_8UC3, Scalar(0, 0, 255));
	//数据类型：CV_[位数][是否带符号][类型前缀]C[通道]
	//eg：CV_8UC3就是8位unsigned char类型，每个像素三个通道

	printf("[方法一]使用Mat（）构造函数\n");
	cout << "A=" << endl << "" << A << endl;

	//[方法二]使用构造函数初始化

	//int sz[2] = { 2,3 };
	//Mat B(2,sz, CV_8UC3, Scalar::all(0));
	//可以创建多维矩阵

	//[方法三]为已存在的IplImage指针创建信息头
	//IplImage* C = cvLoadImage("1.jpg", 1);
	//Mat mtx(C);C报错，说类型不对

	//[方法四]利用Create（）函数（mat类的）
	Mat D;
	D.create(4, 4, CV_8U(2));
	//此方法不能为矩阵设初值，只是在改变尺寸时重新为矩阵数据开辟内存
	printf("[方法四]利用Create（）函数（mat类的）\n");
	cout << "D=" << endl << "" << D << endl;

	//[方法五]MATLAB式初始化
	printf("[方法五]MATLAB式初始化\n");

	//单元矩阵
	Mat E1 = Mat::eye(4, 4, CV_64F);
	cout << "E1=" << endl << "" << E1 << endl;
	//全1矩阵
	Mat E2 = Mat::ones(4, 4, CV_64F);
	cout << "E2=" << endl << "" << E2 << endl;
	//零矩阵
	Mat E3 = Mat::zeros(4, 4, CV_64F);
	cout << "E3=" << endl << "" << E3 << endl;

	//[方法六]对小矩阵用逗号分隔式初始化
	printf("[方法六]对小矩阵用逗号分隔式初始化\n");

	Mat F = (Mat_<double>(3, 3) << 0, 1, 2, 1, 2, 3, 2, 3, 4);
	cout << "F=" << endl << "" << F << endl;

	//[方法七]为已存在最对象创建新信息头
	printf("[方法七]为已存在最对象创建新信息头\n");

	//复制G矩阵第一行
	Mat G = F.row(1).clone();
	cout << "G=" << endl << "" << G << endl;


	system("pause");
    return 0;
}

