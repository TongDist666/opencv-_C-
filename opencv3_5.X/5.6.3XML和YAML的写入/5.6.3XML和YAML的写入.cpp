// 5.6.3XML和YAML的写入.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "opencv2/opencv.hpp"  
#include <time.h>  
using namespace cv;

int main()
{
	//改变console字体颜色
	system("color 5F");

	//初始化
	FileStorage fs("test.yaml", FileStorage::WRITE);
	//此处文件改成XML,YML,TXT,DOC都能运行

	//开始文件写入
	fs << "frameCount" << 5;
	time_t rawtime; time(&rawtime);
	fs << "calibrationDate" << asctime(localtime(&rawtime));
	Mat cameraMatrix = (Mat_<double>(3, 3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
	Mat distCoeffs = (Mat_<double>(5, 1) << 0.1, 0.01, -0.001, 0, 0);
	fs << "cameraMatrix" << cameraMatrix << "distCoeffs" << distCoeffs;
	fs << "features" << "[";
	for (int i = 0; i < 3; i++)
	{
		int x = rand() % 640;
		int y = rand() % 480;
		uchar lbp = rand() % 256;

		fs << "{:" << "x" << x << "y" << y << "lbp" << "[:";
		for (int j = 0; j < 8; j++)
			fs << ((lbp >> j) & 1);
		fs << "]" << "}";
	}
	fs << "]";
	fs.release();

	printf("\n文件读写完毕，请在工程目录下查看生成的文件~");
	getchar();

	return 0;
}