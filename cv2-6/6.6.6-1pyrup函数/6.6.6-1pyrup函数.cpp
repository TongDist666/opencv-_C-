// 6.6.6-1pyrup函数.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\opencv.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;

#define WIN_PYRUP "pyrUp"

int size_0 = 1;

Mat srcImage, dstImage;

int main()
{
	srcImage = imread("1.jpg");
	if (!srcImage.data)
	{
		printf("读取图片出错！");
		return -1;
	}
	namedWindow(WIN_PYRUP);
	
	/*
	void pyrUp( 
		InputArray src, //源图
		OutputArray dst,
        const Size& dstsize = Size(),//输出图像尺寸  默认size（）   即：size（src.cols*2,src.rows*2）
										且必须一直满足：
											|dstsize.width-src.cols|<=dstsize.width mod 2
											|dstsize.height-src.rows|<=dstsize.height mod 2
		int borderType = BORDER_DEFAULT );
	*/
	pyrUp(srcImage, dstImage, Size(srcImage.cols*size_0*2, srcImage.rows*size_0*2));
	imshow(WIN_PYRUP, dstImage);

	while (waitKey(0)!=27){}
    return 0;
}