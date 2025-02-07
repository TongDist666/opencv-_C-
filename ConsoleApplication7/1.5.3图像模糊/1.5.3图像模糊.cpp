// 1.5.3图像模糊.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"opencv2/highgui/highgui.hpp"
#include"opencv2/imgproc/imgproc.hpp"
//#include<opencv2\highgui\highgui.hpp>
//#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;
/*均值滤波是典型的线性滤波算法，它是指在图像上对目标像素给一个模板，
该模板包括了其周围的临近像素（以目标像素为中心的周围8个像素，
构成一个滤波模板，即去掉目标像素本身），再用模板中的全体像素的平均值来代替原来像素值。
*/

int main()
{
	Mat srcImage = imread("1.jpg");
	imshow("原图_模糊操作", srcImage);
	Mat dstImage;

	//blur函数进行均值滤波操作
	//   目标图片  结果图片  模糊像素参数
	blur(srcImage, dstImage, Size(7, 7));
	imshow("均值滤波_模糊操作",dstImage);
	waitKey(0);
    return 0;
}

