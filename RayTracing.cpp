/*
  * 作者（B站UP主，感谢三连！！！）：FaithBook-_-
  * GitHub：FaithBook233
  * 技术交流群（非粉丝群）：815093873
  *
  *
  * 本项目是我学习C++与渲染算法的一个小Demo，代码开源供广大网友学习
  * 有问题尽量自己解决，知识不够先问度娘，加油少年！
  *
  * 运行环境：Windows 10 Visual Studio 2019
  * 代码参考《Ray Tracing in One Weekend》
  * 文献中并未提及运行环境等信息，我见到有人用Visual Studio Code实现了，但我更热衷于用VS，所以决定用Visual Studio实现代码
  * 文献中代码为偏C风格，我将代码改为纯C++代码，并对算法和代码命名风格进行了升级与整理
  * 原文为单精度浮点，我整体改为双精度浮点了
  *
  * 运行此项目必须的步骤：
  *       ①准备Visual Studio 2019或更高的版本，低版本可能有兼容问题
  *       ②（已实现）在项目属性->调试->命令行调试中输入 >Image.ppm  可以将控制台程序输出到Image.ppm
  *       ③用ppm viewer打开Image.ppm即可看到效果
  *
  * 参考文献《Ray Tracing in One Weekend》 Peter Shirley Version 1.54 Copyright 2018. Peter Shirley. All rights reserved

*/



#include <iostream>
#include <opencv.hpp>
#include <highgui.hpp>
#include "Vec3.h"

using namespace cv;
int main()
{
	int nx = 200;//图片宽度（单位为像素）
	int ny = 100;//图片宽度（单位为像素）

	//文件头写入
	std::cout << "P3" << std::endl << nx << " " << ny << std::endl << "255" << std::endl;

	//预览窗口相关
	int WindowWidth;//窗口宽度
	int WindowHeight;//窗口高度
	if (nx > ny)  //如果渲染的图片为横版，计算窗口宽度与高度
	{
		WindowHeight = 1080 - 200;
		WindowWidth = (int)((double)WindowHeight * (double)nx / (double)ny);
	}
	else //如果渲染的图片为竖版，计算窗口宽度与高度
	{
		WindowWidth = 1920 - 200;
		WindowHeight = (int)((double)WindowWidth * (double)ny / (double)nx);

	}
	Mat RenderingImage(ny, nx, CV_8UC3, Scalar(50, 50, 50)); //创建一张图片
	namedWindow("图像预览（渲染中）", WINDOW_NORMAL);//设置标题
	moveWindow("图像预览（渲染中）", (int)((1920.0 - WindowWidth) / 2), (int)((1080.0 - WindowHeight) / 2) - 50);//设置窗口位置
	resizeWindow("图像预览（渲染中）", WindowWidth, WindowHeight);//设置窗口大小

	for (int j = ny - 1; j >= 0; j--)//行信息
	{
		for (int i = 0; i < nx; i++)//列信息
		{
			Vec3 Col(float(i)/float(nx),float(j)/float(ny),0.2);
			//下面三个将射线检测到的颜色拆分为红、绿、蓝三个通道
			int ir = int(255.99 * Col[0]);
			int ig = int(255.99 * Col[1]);
			int ib = int(255.99 * Col[2]);
			//将当前像素的三个通道值写入文件
			std::cout << ir << " " << ig << " " << ib << std::endl;

			RenderingImage.at<cv::Vec3b>(ny - 1 - j, i)[0] = ib;
			RenderingImage.at<cv::Vec3b>(ny - 1 - j, i)[1] = ig;
			RenderingImage.at<cv::Vec3b>(ny - 1 - j, i)[2] = ir;
		}
		//每行计算完以后刷新预览窗口
		if (!(j%(ny/100))) //每渲染ny/100行后更新预览窗口图片
		{
			imshow("图像预览（渲染中）", RenderingImage);
			waitKey(1);//等待1毫秒事件让窗口刷新完毕
		}
		
	}
	imshow("图像预览（渲染中）", RenderingImage);
	waitKey(3000); //等待3000毫秒
	destroyAllWindows();//关闭窗口
	return 0;
}