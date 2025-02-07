// 4.1.6输出其他常用数据结构.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>
#include<opencv2\core.hpp>
using namespace cv;
using namespace std;

int main()
{
	Point2f p(3, 4);
	cout << "输出二维点\n" << p<<endl;

	Point3f p3(3, 4, 5);
	cout << "\n输出三维点\n" << p3 << endl;
	
	vector<float> v;
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);
	cout << "\n基于mat的vector\n" << Mat(v) << endl;

	vector<Point2f> points(2);
	points[0] = Point2f(float(3),float(4));
	points[1] = Point2f(float(5), float(6));
	cout << "\n二维点向量\n" << points << endl;
	
	system("pause");
    return 0;
}

