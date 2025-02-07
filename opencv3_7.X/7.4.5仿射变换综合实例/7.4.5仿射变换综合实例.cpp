// 7.4.5仿射变换综合实例.cpp: 定义控制台应用程序的入口点。
/*
仿射变换：
	1）旋转rotation（线性变换）
	2）平移translation（向量家）
	3）缩放scale（线性变换）
*/

#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "【原始图窗口】"					//为窗口标题定义的宏 
#define WINDOW_NAME2 "【经过Warp后的图像】"        //为窗口标题定义的宏 
#define WINDOW_NAME3 "【经过Warp和Rotate后的图像】"        //为窗口标题定义的宏 

static void ShowHelpText();

int main()
{
	system("color 5D");//背景暗紫色，字粉红色

	//【1】参数准备
	//定义两组点，代表两个三角形
	Point2f srcTriangle[3];
	Point2f dstTriangle[3];
	//定义一些Mat变量
	Mat rotMat(2, 3, CV_32FC1);
	Mat warpMat(2, 3, CV_32FC1);
	Mat srcImage, dstImage_warp, dstImage_warp_rotate;

	//【2】加载源图像并作一些初始化
	srcImage = imread("1.jpg", 1);
	if (!srcImage.data) { printf("读取图片错误，请确定目录下是否有imread函数指定的图片存在~！ \n"); return false; }
	// 设置目标图像的大小和类型与源图像一致
	dstImage_warp = Mat::zeros(srcImage.rows, srcImage.cols, srcImage.type());

	//【3】设置源图像和目标图像上的三组点以计算仿射变换
	srcTriangle[0] = Point2f(0, 0);
	srcTriangle[1] = Point2f(static_cast<float>(srcImage.cols - 1), 0);
	srcTriangle[2] = Point2f(0, static_cast<float>(srcImage.rows - 1));

	dstTriangle[0] = Point2f(static_cast<float>(srcImage.cols*0.0), static_cast<float>(srcImage.rows*0.33));
	dstTriangle[1] = Point2f(static_cast<float>(srcImage.cols*0.65), static_cast<float>(srcImage.rows*0.35));
	dstTriangle[2] = Point2f(static_cast<float>(srcImage.cols*0.15), static_cast<float>(srcImage.rows*0.6));

	//【4】求得仿射变换
	warpMat = getAffineTransform(srcTriangle, dstTriangle);

	//【5】对源图像应用刚刚求得的仿射变换
	warpAffine(srcImage, dstImage_warp, warpMat, dstImage_warp.size());
	/*
	warpAffine(
		1 输入图像 mat
		2 输出图像 mat 和输入同尺寸
		3 M 2x3的变换矩阵
		4 size 输出图像尺寸
		5 int 插值方法
			i）INTER_NEAREST最近邻插值
			ii）INTER_LINEAR双线性插值（默认）
			iii）INTER_AREA区域插值
			iv）INTER_CUBIC双三次样条插值（逾4x4像素邻域内的双三次插值）
			v）INTER_LANCZOS4（逾8x8邻域的Lanczos插值）
			vi）CV_WRAP_FILL_OUTLIERS填充所有输出图像的像素，边界外像素设为fillval
			vii）CV_WRAP_INVERSE_MAP表示M为输出图像到输入图像的反变换
		6 int 边界像素模式 默认 BORDER_CONSTANT
		7 const scalar& 默认scalar（0，0，0）
	)
	*/

	//【6】对图像进行缩放后再旋转
	// 计算绕图像中点顺时针旋转50度缩放因子为0.6的旋转矩阵
	Point center = Point(dstImage_warp.cols / 2, dstImage_warp.rows / 2);
	double angle = -50.0;
	double scale = 0.6;
	// 通过上面的旋转细节信息求得旋转矩阵
	rotMat = getRotationMatrix2D(center, angle, scale);
	/*用于计算二维旋转变换矩阵
	getRotationMatrix2D（
		1 Point2f 源图像旋转中心
		2 double 旋转角度（正值表示逆时针，原点在左上角）
		3 double 缩放系数
	）
	*/
	// 旋转已缩放后的图像
	warpAffine(dstImage_warp, dstImage_warp_rotate, rotMat, dstImage_warp.size());

	//显示结果
	imshow(WINDOW_NAME1, srcImage);
	imshow(WINDOW_NAME2, dstImage_warp);
	imshow(WINDOW_NAME3, dstImage_warp_rotate);

	printf("\t\t键盘按键【ESC】- 退出程序\n");
	while (waitKey(0) != 27) {}
	return 0;
}
