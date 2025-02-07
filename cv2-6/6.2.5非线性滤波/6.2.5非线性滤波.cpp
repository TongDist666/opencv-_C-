// 6.2.5非线性滤波.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include<opencv2\imgproc\imgproc.hpp>
using namespace cv;
using namespace std;

#define WIN_MID "中值滤波"
#define WIN_BILATER "双边滤波"

void mid_change(int, void*);
int mid_value = 3;
void bilater_change(int, void*);
int bilater_value = 10;

Mat srcImage, dstmid, dstbilater;

int main()
{
	srcImage = imread("1.jpg",CV_LOAD_IMAGE_GRAYSCALE);
	dstmid = srcImage.clone();
	dstbilater = srcImage.clone();

	namedWindow(WIN_MID, 1);
	namedWindow(WIN_BILATER, 1);

	createTrackbar("中值滤波 内核数：", WIN_MID, &mid_value, 30, mid_change);
	createTrackbar("双边滤波 参数：", WIN_BILATER, &bilater_value, 50, bilater_change);
	mid_change(mid_value, 0);
	bilater_change(bilater_value, 0);

	while (waitKey(0) != 27) {}
	return 0;
}
void mid_change(int, void*) {
	medianBlur(srcImage, dstmid, mid_value*2+1);
	/*
	void medianBlur( 
		InputArray src, //输入图像，1、3、4通道，ksize为3或5时，图像深度必须为 : CV_8U,CV_16U,CV_32F。对于较大孔径，深度只能是CV_8U
		OutputArray dst, //输出图像
		int ksize );//孔径线性尺寸 >1且为奇数
	*/
	imshow(WIN_MID, dstmid);
}
void bilater_change(int, void*) {
	bilateralFilter(srcImage, dstbilater, bilater_value,bilater_value*2,bilater_value/2);
	/*
	void bilateralFilter( 
		InputArray src, //输入图像，8位或浮点型 单通或三通
		OutputArray dst, //输出图像
		int d,//过滤时像素邻域直径 若<0，根据sigmaSpace计算出来
        double sigmaColor, //颜色空间滤波器的sigma值，越大表示邻域内有越宽广的颜色会被混合在一起，产生较大的半相等颜色区域
		double sigmaSpace,//坐标空间滤波器的sigma值，坐标空间的标注方差，值越大，越远的像素会互相影响，越大区域中足够相似的颜色获取相同颜色
							d>0，d指邻域大小，与sigmaSpace；否则，d正比于sigmaSpace
        int borderType = BORDER_DEFAULT );
	*/
	imshow(WIN_BILATER, dstbilater);
}