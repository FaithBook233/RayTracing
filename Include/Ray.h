#pragma once
#include "Vec3.h"

class Ray
{
public:
	Ray();
	Ray(const Vec3& a, const Vec3& b) { A = a; B = b; }	 //构造函数，初始化原点向量A和方向向量B
	Vec3 Origin() const { return A; } //返回原点向量A
	Vec3 Direction() const { return B; }//返回方向向量B
	Vec3 PointAtParameter(float T)const { return A + T * B; }//通过T计算光线P(t) = A + t * B
	//A和B为类的成员变量
	Vec3 A;
	Vec3 B;
};