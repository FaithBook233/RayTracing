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
  *       ②（已实现）在项目属性->调试->命令行调试中输入 >data.ppm  可以将控制台程序输出到data.ppm
  *       ③用ppm viewer打开data.ppm即可看到效果
  *
  * 压缩包包含文件：
  *       ①项目所需文件
  *       ②ppm viewer（ppm图片查看器）
  *
  * 参考文献《Ray Tracing in One Weekend》 Peter Shirley Version 1.54 Copyright 2018. Peter Shirley. All rights reserved

*/



#include <iostream>
#include <windows.h>
#include <opencv.hpp>
#include <highgui.hpp>
#include "Vec3.h"
#include "Ray.h"
#include "Sphere.h"
#include "HitableList.h"
#include "Random.h"
#include "Camera.h"

using namespace cv;


Vec3 Color(const Ray& R, Hitable* World, int Depth)
{
	HitRecord Rec;///命中结果


	if (World->Hit(R, 0.001, DBL_MAX, Rec))	 //如果能检测到这个World对象
	{
		Ray Scattered;	//散射光线
		Vec3 Attenuation;//衰减
		 //保证执行color的次数不超过50次,
		//查看Scatter函数，Attenuation 与Scattered传引用进去，函数执行完
		//这两个变量得到命中对象的衰减率（Attenuation）和散射光线（或反射光线Scattered）
		if (Depth < 50 && Rec.MatPtr->Scatter(R, Rec, Attenuation, Scattered))
		{
			//下面递归地运行，检测从散射光线Scattered检测到的颜色
			//每次调用都加了衰减参数Attenuation
			//每次都从新的散射光线开始检测。
			return  Attenuation * Color(Scattered, World, Depth + 1);
		}
		else
		{
			return Vec3(0, 0, 0);
		}
	}
	else
	{
		//返回背景色
		Vec3 UnitDirection = UnitVector(R.Direction());		 //获取单位方向向量
		double T = 0.5 * (UnitDirection.Y() + 1.0);			 //插值量，范围[0,1]
		return (1.0 - T) * Vec3(1.0, 1.0, 1.0) + T * Vec3(0.5, 0.7, 1.0); //返回一个颜色
	}
}

int main()
{
	int nx = 800;//图片宽度（单位为像素）
	int ny = 400;//图片高度（单位为像素）
	int ns = 100;//扫描次数
	//文件头写入
	std::cout << "P3" << std::endl << nx << " " << ny << std::endl << "255" << std::endl;

	//保存世界中的球体
	Hitable* List[4];
	List[0] = new Sphere(Vec3(0, 0, -1), 0.5, new Lambertian(Vec3(0.1, 0.2, 0.5))); //中间的球
	List[1] = new Sphere(Vec3(0, -100.5, -1), 100, new Lambertian(Vec3(0.8, 0.8, 0.0)));//下面
	List[2] = new Sphere(Vec3(1, 0, -1), 0.5, new Metal(Vec3(0.8, 0.6, 0.2), 0.5));//右边
	List[3] = new Sphere(Vec3(-1, 0, -1), 0.5, new Dielectric(1.5)); //左边
	List[3] = new Sphere(Vec3(-1, 0, -1), -0.45, new Dielectric(1.5)); //负半径，曲面法线指向内部
	Hitable* World = new HitableList(List, 4);

	Camera Cam;//摄像机对象

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
			Vec3 Col(0, 0, 0);//保存当前像素颜色

			for (int s = 0; s < ns; s++)  //循环ns次用来计算ns次
			{
				//获取屏幕扫描像素
				//注意下面UV获取时加了0-1随机浮点
				//可以获取当前像素和右下方1像素之间的随机UV
				//因为RandDbl01只产生0-1之间的随机数
				//所以每个像素只会跟右边1像素和下边1像素之间的像素混合颜色。
				double U = double(i + RandDbl01()) / double(nx);
				double V = double(j + RandDbl01()) / double(ny);

				//获取当前扫描射线
				Ray R = Cam.GetRay(U, V);
				Vec3 P = R.PointAtParameter(2.0);

				//将随机UV得到的颜色相加
				Col += Color(R, World, 0);
			}
			//计算Col的平均数
			Col /= double(ns);
			//将得到的颜色变亮
			Col = Vec3(sqrt(Col[0]), sqrt(Col[1]), sqrt(Col[2]));
			//下面三个将射线检测到的颜色拆分为红、绿、蓝三个通道
			int ir = int(255.99 * Col[0]);
			int ig = int(255.99 * Col[1]);
			int ib = int(255.99 * Col[2]);
			//将当前像素的三个通道值写入文件
			std::cout << ir << " " << ig << " " << ib << std::endl;
			//实时显示渲染帧
			RenderingImage.at<cv::Vec3b>(ny - 1 - j, i)[0] = ib;
			RenderingImage.at<cv::Vec3b>(ny - 1 - j, i)[1] = ig;
			RenderingImage.at<cv::Vec3b>(ny - 1 - j, i)[2] = ir;
			//Sleep(0);

		}
		//每行计算完以后刷新预览窗口
		if (!(j % (ny / 100))) //每渲染ny/100行后更新预览窗口图片
		{
			imshow("图像预览（渲染中）", RenderingImage);
			waitKey(1);//等待1毫秒事件让窗口刷新完毕
		}

	}
	imshow("图像预览（渲染中）", RenderingImage);
	waitKey(5000); //等待3000毫秒
	destroyAllWindows();//关闭窗口
	return 0;
}