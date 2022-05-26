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
	friend inline bool Refract(const Vec3& V, const Vec3& N, double NiOverNt, Vec3& Refracted);//折射光线

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

//判断是否可以生成折射光线
//参数分别是入射点，入射点法线，折射率，折射后的光线
inline bool Refract(const Vec3& V, const Vec3& N, double NiOverNt, Vec3& Refracted)
{
	Vec3 UV = UnitVector(V);//入射点位置的单位向量
	double Dt = Dot(UV, N);	//Dt为UV在法线N正方向上的投影长度。
	double Discriminant = 1.0 - NiOverNt * NiOverNt * (1 - Dt * Dt);//1-sin(theta1)^2

	//这里要注意的是，DIscriminant>0才执行折射
	if (Discriminant > 0)  //表示满足折射条件
	{
		Refracted = NiOverNt * (UV - N * Dt) - N * sqrt(Discriminant);	//得到折射后的光线
		return true;
	}
	else
		return false;
}