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

int main()
{
	int nx = 200;//图片宽度（单位为像素）
	int ny = 100;//图片宽度（单位为像素）
	//文件头写入
	std::cout << "P3" << std::endl << nx << " " << ny << std::endl << "255" << std::endl;

	for (int j = ny - 1; j >= 0; j--)//行信息
	{
		for (int i = 0; i < nx; i++)//列信息
		{
			//注意原书上的类型为float，以后的代码中会整体采用double
			//计算每个像素上的RGB信息
			double r = double(i) / double(nx);
			double g = double(j) / double(ny);
			//每个像素的蓝色通道固定为0.2
			double b = 0.2;
			//因为ppm文件中RGB通道值为0-255，而上面计算出来的r,g,b范围为0-1，这里进行转换
			int ir = int(255.99 * r);
			int ig = int(255.99 * g);
			int ib = int(255.99 * b);
			//将当前像素的三个通道值写入文件
			std::cout << ir << " " << ig << " " << ib << std::endl;
		}
	}
}