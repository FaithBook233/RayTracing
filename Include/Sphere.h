#pragma once

#include "Hitable.h"
#include "Material.h"

class Sphere :
	public Hitable //�̳�Hitable
{
public:
	Sphere() {}
	Sphere(Vec3 Cen, double R) :Center(Cen), Radius(R) {};//���캯������ʼ��������뾶
	Sphere(Vec3 Cen, double R, Material* MaterialPtr) :Center(Cen), Radius(R), MatPtr(MaterialPtr) {};// ��ʼ������
	inline virtual bool Hit(const Ray& R, double TMin, double TMax, HitRecord& Rec)const;//�̳�Hitable��Hit

	Vec3 Center; //����
	double Radius;//�뾶
	Material* MatPtr;//����ָ��
};

//�������R��Tmin��Tmax��Χ�����е�ǰ���壬�򷵻�true
bool Sphere::Hit(const Ray& R, double TMin, double TMax, HitRecord& Rec)const
{
	//��һԪ���η���
	Vec3 OC = R.Origin() - Center;//�����ĵ����߷���������
	double A = Dot(R.Direction(), R.Direction());
	double B = Dot(OC, R.Direction());
	double C = Dot(OC, OC) - Radius * Radius;
	double Discriminant = B * B - A * C;

	if (Discriminant > 0) //�����������
	{

		Rec.MatPtr = MatPtr;
		//����Ƚ�С�Ľ�
		double Temp = (-B - sqrt(B * B - A * C)) / A;
		if (Temp < TMax && Temp >TMin) //�����������T��TMin��TMax֮�䣬��������Ҫ��ֵ
		{
			//���������Ľ⡢�����λ�ú�����㷨�ߵ�Rec��
			Rec.T = Temp;
			Rec.P = R.PointAtParameter(Rec.T);
			Rec.Normal = (Rec.P - Center) / Radius;
			return true;
		}
		//����ϱߵĵ㲻�����ǵļ�ⷶΧ�ڣ�����ȥ��ͬ���ķ��������һ����
		Temp = (-B + sqrt(B * B - A * C)) / A;
		if (Temp < TMax && Temp >TMin)
		{
			//���������Ľ⡢�����λ�ú�����㷨�ߵ�Rec��
			Rec.T = Temp;
			Rec.P = R.PointAtParameter(Rec.T);
			Rec.Normal = (Rec.P - Center) / Radius;
			return true;
		}
	}
	//�������û���������򷵻�false
	return false;
}
