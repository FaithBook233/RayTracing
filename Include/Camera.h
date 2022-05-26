#pragma once

#include "Ray.h"

class Camera
{
public:
	Camera()
	{
		LowerLeftCorner = Vec3(-2.0, -1.0, -1.0);	 //���½�����
		Horizontal = Vec3(4.0, 0.0, 0.0);			 //��Ļˮƽ���
		Vertical = Vec3(0.0, 2.0, 0.0);			 //��Ļ��ֱ�߶�
		Origin = Vec3(0.0, 0.0, 0.0);
	}
	Ray GetRay(double U, double V)
	{
		//RΪ��ǰ�ļ������
		return Ray(Origin, LowerLeftCorner + U * Horizontal + V * Vertical -Origin);
	}

	Vec3 LowerLeftCorner;//���½�����
	Vec3 Horizontal;//��Ļˮƽ���
	Vec3 Vertical;//��Ļ��ֱ�߶�
	Vec3 Origin;//�ӵ�
};