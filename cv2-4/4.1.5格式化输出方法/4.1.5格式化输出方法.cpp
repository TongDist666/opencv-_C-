// 4.1.5格式化输出方法.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<opencv2\core.hpp>
using namespace cv;
using namespace std;

int main()
{
	Mat m = Mat(3,4,CV_8UC2);
	randu(m,Scalar::all(0),Scalar(8));

	cout <<"m=\n"<< "一.opencv默认风格\n" << m << endl;
	cout << "\n二.python风格\n" << format(m,Formatter::FMT_PYTHON)<< endl;
	cout << "\n三.逗号分隔CSV风格\n" << format(m, Formatter::FMT_CSV) << endl;
	cout << "\n四.Numpy风格\n" << format(m, Formatter::FMT_NUMPY) << endl;
	cout << "\n五.c语言风格\n" << format(m, Formatter::FMT_C) << endl;
	
	system("pause");
    return 0;
}

