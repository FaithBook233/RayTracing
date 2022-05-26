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

	Metal(const Vec3& A) :Albedo(A){}
	virtual bool Scatter(const Ray& RIn, const HitRecord& Rec, Vec3& Attenuation, Ray& Scattered) const
	{
		Vec3 Reflected = Reflect(UnitVector(RIn.Direction()), Rec.Normal);//获得反射光线

		//根据粗糙度获取随机反射光线，粗糙度越大，反射光线离散性更大
		Scattered = Ray(Rec.P, Reflected);
		Attenuation = Albedo;//返回 衰减
		return (Dot(Scattered.Direction(), Rec.Normal) > 0); //如果反射光线与法线的夹角为锐角则retur true
	}

	Vec3 Albedo; //反射率
};
