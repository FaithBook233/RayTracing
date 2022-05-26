#pragma once

//#include "Reflect.h"
#include "Hitable.h"


class Material
{
public:
	/*
		*材料的散射行为
		*参数包括:入射光线、命中信息、衰减，散射。
	*/
	virtual bool Scatter(const Ray& RIn, const HitRecord& Rec, Vec3& Attenuation, Ray& Scattered)const = 0;
};

class Lambertian :
	public Material
{
public:
	Lambertian(const Vec3& A) :Albedo(A) {}
	//散射行为
	virtual bool Scatter(const Ray& RIn, const HitRecord& Rec, Vec3& Attenuation, Ray& Scattered) const
	{
		//入射点单位切球内随机点
		Vec3 Target = Rec.P + Rec.Normal + RandomInUnitSphere();

		Scattered = Ray(Rec.P, Target - Rec.P);//光线Ray的散射光线
		Attenuation = Albedo;//返回衰减变量
		return true;
	}

	Vec3 Albedo;  //反射率
};

/*
*	金属材质
*/
class Metal :
	public Material
{
public:

	Metal(const Vec3& A) :Albedo(A), Fuzz(0.5) {}
	Metal(const Vec3& A, double F) :Albedo(A) {
		Fuzz = F > 1 ? 1 : F < 0 ? 0 : F; //控制粗糙度在0和1之间
	}
	virtual bool Scatter(const Ray& RIn, const HitRecord& Rec, Vec3& Attenuation, Ray& Scattered) const
	{
		Vec3 Reflected = Reflect(UnitVector(RIn.Direction()), Rec.Normal);//获得反射光线
		//Scattered = Ray(Rec.P, Reflected);//得到从入射点反射的光线

		//根据粗糙度获取随机反射光线，粗糙度越大，反射光线离散性更大
		Scattered = Ray(Rec.P, Reflected + Fuzz * RandomInUnitSphere());
		Attenuation = Albedo;//返回 衰减
		return (Dot(Scattered.Direction(), Rec.Normal) > 0); //如果反射光线与法线的夹角为锐角则retur true
	}

	Vec3 Albedo; //反射率
	double Fuzz;//粗糙度
};


//用于返回当前角度下反射率
double Schlick(double Cosine, double Ref)
{
	double R0 = (1 - Ref) / (1 + Ref);
	R0 = R0 * R0;
	return R0 + (1 - R0) * pow((1 - Cosine), 5);
}

class Dielectric :
	public Material
{
public:
	Dielectric(double Ri) :RefIdx(Ri) {}
	virtual bool Scatter(const Ray& RIn, const HitRecord& Rec, Vec3& Attenuation, Ray& Scattered) const
	{
		Vec3 OutwardNormal;
		Vec3 Reflected = Reflect(RIn.Direction(), Rec.Normal);
		double NiOverNt;

		//玻璃本身透光颜色
		Attenuation = Vec3(1.0, 1.0, 1.0);
		Vec3 Refracted;
		double ReflectProb;
		double Cosine;//计算入射光线与法线的余弦值
		if (Dot(RIn.Direction(), Rec.Normal) > 0)
		{
			OutwardNormal = -Rec.Normal;
			NiOverNt = RefIdx;
			Cosine = Dot(RIn.Direction(), Rec.Normal) / RIn.Direction().Vec3Length();

		}
		else
		{
			OutwardNormal = Rec.Normal;
			NiOverNt = 1.0 / RefIdx;
			Cosine = -Dot(RIn.Direction(), Rec.Normal) / RIn.Direction().Vec3Length();
		}

		if (Refract(RIn.Direction(), OutwardNormal, NiOverNt, Refracted))//可以发生折射
		{
			ReflectProb = Schlick(Cosine, RefIdx);//反射率
		}
		else
		{
			//不能发生折射，则发生反射
			Scattered = Ray(Rec.P, Reflected);
			ReflectProb = 1.0;
		}

		if (RandDbl01() < ReflectProb)	//当可以发生折射时，有一定几率执行反射
		{
			Scattered = Ray(Rec.P, Reflected);//处理成反射
		}
		else//当不能发生折射时，一定会执行这里，
		{
			Scattered = Ray(Rec.P, Refracted);//处理成折射
		}
		return true;
	}


	inline friend double Schlick(double Cosine, double RefIdx_);

	double RefIdx;

};


