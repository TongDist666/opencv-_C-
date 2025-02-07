// 5.1.5访问图像中像素的三种方法.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<highgui\highgui.hpp>
#include<iostream>
using namespace cv;
using namespace std;

void colorReduce1(Mat& inputImage, Mat& outputImage, int div);
void colorReduce2(Mat& inputImage, Mat& outputImage, int div);
void colorReduce3(Mat& inputImage, Mat& outputImage, int div);

int main()
{
	Mat srcImage = imread("1.jpg");
	Mat dstImage;
	dstImage.create(srcImage.rows,srcImage.cols,srcImage.type());
	cout << srcImage.isContinuous() << endl;

	double time1 = static_cast<double>(getTickCount());
	colorReduce1(srcImage,dstImage,32);
	time1 = ((double)getTickCount() - time1) / getTickFrequency();
	imshow("指针访问像素",dstImage);
	cout << " 运行时间：" << time1 << endl;

	double time2 = static_cast<double>(getTickCount());
	colorReduce2(srcImage, dstImage, 32);
	time2 = ((double)getTickCount() - time2) / getTickFrequency();
	imshow("迭代器访问像素", dstImage);
	cout << " 运行时间：" << time2 << endl;

	double time3 = static_cast<double>(getTickCount());
	colorReduce3(srcImage, dstImage, 32);
	time3 = ((double)getTickCount() - time3) / getTickFrequency();
	imshow("动态地址访问像素", dstImage);
	cout << " 运行时间：" << time3 << endl;

	while (waitKey(0) != 27) {}
    return 0;
}
//指针访问像素
void colorReduce1(Mat& inputImage, Mat& outputImage, int div) {
	outputImage = inputImage.clone();
	int rowNum = outputImage.rows;//行数
	int colNum = outputImage.cols*outputImage.channels();//每一行元素个数=列数*通道数

	for (int i = 0; i < rowNum; i++) {
		uchar* data = outputImage.ptr<uchar>(i);//获取第i行首地址
		for (int j = 0; j < colNum; j++) {
			data[j] = data[j] / div * div + div / 2;
		}
	}
}
//迭代器访问像素
void colorReduce2(Mat& inputImage, Mat& outputImage, int div) {
	outputImage = inputImage.clone();
	Mat_<Vec3b>::iterator start = outputImage.begin<Vec3b>();//初始位置迭代器
	Mat_<Vec3b>::iterator end = outputImage.end<Vec3b>();//终止位置迭代器

	for (; start != end; ++start) {
		(*start)[0] = (*start)[0] / div * div + div / 2;
		(*start)[1] = (*start)[1] / div * div + div / 2;
		(*start)[2] = (*start)[2] / div * div + div / 2;
	}
}
//动态地址访问像素
void colorReduce3(Mat& inputImage, Mat& outputImage, int div) {
	outputImage = inputImage.clone();
	int rowNum = outputImage.rows;
	int colNum = outputImage.cols;

	for (int i = 0; i < rowNum; i++) {
		for (int j = 0; j < colNum; j++) {
			outputImage.at<Vec3b>(i, j)[0] = outputImage.at<Vec3b>(i, j)[0] / div * div + div / 2;//蓝色通道
			outputImage.at<Vec3b>(i, j)[1] = outputImage.at<Vec3b>(i, j)[1] / div * div + div / 2;//绿色通道
			outputImage.at<Vec3b>(i, j)[2] = outputImage.at<Vec3b>(i, j)[2] / div * div + div / 2;//红色通道
		}
	}
}