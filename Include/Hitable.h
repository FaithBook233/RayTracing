#pragma once

#include "Ray.h"
struct HitRecord   //命中结果
{
	double T;		//入射点解出来的T
	Vec3 P;			//入射点
	Vec3 Normal;	//法线
};

class Hitable
{
public:
	//TMin与TMax分别表示检测射线的开始与结束点对应地系数T
	//也就是检测射线为R = P(TMin)到R=P(TMax）之间得这段射线
	virtual bool Hit(const Ray& R, double TMin, double TMax, HitRecord& Rec) const = 0;//虚函数
};