#pragma once

#include "Ray.h"

class Camera
{
public:
	Camera()
	{
		LowerLeftCorner = Vec3(-2.0, -1.0, -1.0);	 //左下角坐标
		Horizontal = Vec3(4.0, 0.0, 0.0);			 //屏幕水平宽度
		Vertical = Vec3(0.0, 2.0, 0.0);			 //屏幕垂直高度
		Origin = Vec3(0.0, 0.0, 0.0);
	}
	Ray GetRay(double U, double V)
	{
		//R为当前的检测射线
		return Ray(Origin, LowerLeftCorner + U * Horizontal + V * Vertical -Origin);
	}

	Vec3 LowerLeftCorner;//左下角坐标
	Vec3 Horizontal;//屏幕水平宽度
	Vec3 Vertical;//屏幕垂直高度
	Vec3 Origin;//视点
};