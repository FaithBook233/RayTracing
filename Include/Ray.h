#pragma once
#include "Vec3.h"
#include "Random.h"

class Ray
{
public:
	Ray() { A = Vec3(0, 0, 0), B = Vec3(0, 0, 0); }
	Ray(const Vec3& a, const Vec3& b) { A = a; B = b; }	 //构造函数，初始化原点向量A和方向向量B
	Vec3 Origin() const { return A; } //返回原点向量A
	Vec3 Direction() const { return B; }//返回方向向量B
	Vec3 PointAtParameter(double T)const { return A + T * B; }//通过T计算光线P(t) = A + t * B
	//A和B为类的成员变量

	friend inline Vec3 RandomInUnitSphere();//单位球体内的随机点
	friend inline Vec3 Reflect(const Vec3& V, const Vec3& N);//反射光线

	Vec3 A;
	Vec3 B;
};

Vec3 RandomInUnitSphere() {
	Vec3 P;
	do {
		P = 2.0 * Vec3(RandDbl01(), RandDbl01(), RandDbl01()) - Vec3(1, 1, 1);
	} while (P.SquaredLength() >= 1.0);
	return P;
}

inline Vec3 Reflect(const Vec3& V, const Vec3& N)
{
	return V - 2 * Dot(V, N) * N;
}