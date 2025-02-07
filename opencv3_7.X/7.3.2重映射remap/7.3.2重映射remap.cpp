// 7.3.2重映射remap.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;

int main() {
	system("color 3D");//暗靛色

	Mat srcImage, dstImage;
	Mat map_x, map_y;

	srcImage = imread("1.jpg");
	if (!srcImage.data) {printf("图片读取错误"); return 0;}
	imshow("原图", srcImage);

	//创建和原始图一样的效果图，x重映射图，y重映射图
	dstImage.create(srcImage.size(), srcImage.type());
	map_x.create(srcImage.size(), CV_32FC1);
	map_y.create(srcImage.size(), CV_32FC1);

	//双层循环，遍历每一个像素点，改变map_x & map_y的值
	for (int j = 0; j < srcImage.rows; j++) {
		for (int i = 0; i < srcImage.cols; i++) {
			//列数不变，行数倒一下
			map_x.at<float>(j, i) = static_cast<float>(i);
			map_y.at<float>(j, i) = static_cast<float>(srcImage.rows - j);
		}
	}
	remap(srcImage, dstImage, map_x, map_y, CV_INTER_LINEAR, BORDER_CONSTANT, Scalar(0, 0, 0));
	/*
	remap(
		1 输入图像 单通 8位或浮点型
		2 输出图像
		3 map1
			i）表示点（x，y）的第一个映射
			ii）表示CV_16SC2,CV_32FC1或CV_32FC2类型的C值
		4 map2
			i）若map1表示点（x，y）时，这个参数无意义
			ii）表示CV_16UC1,CV_32FC1类型的Y值（第二个值）
		5 int 类型 插值方式
			i）CV_INTER_NEAREST最近邻插值
			ii）CV_INTER_LINEAR双线性插值（默认）
			iii）CV_INTER_CUBIC双三次样条插值（逾4x4像素邻域内的双三次插值）
			iv）CV_INTER_LANCZOS4（逾8x8邻域的Lanczos插值）
		6 int 边界模式 默认BORDER_CONSTANT 表示离散点像素不会被修改
		7 const scalar& 有常数边界时使用的值 默认scalar（0，0，0） 
	)
	*/

	imshow("效果图", dstImage);

	printf("按ESC退出");
	while(waitKey(333)!=27){}
	return 0;
}
