#pragma once
#include "Vec3.h"

class Ray
{
public:
	Ray();
	Ray(const Vec3& a, const Vec3& b) { A = a; B = b; }	 //���캯������ʼ��ԭ������A�ͷ�������B
	Vec3 Origin() const { return A; } //����ԭ������A
	Vec3 Direction() const { return B; }//���ط�������B
	Vec3 PointAtParameter(float T)const { return A + T * B; }//ͨ��T�������P(t) = A + t * B
	//A��BΪ��ĳ�Ա����
	Vec3 A;
	Vec3 B;
};