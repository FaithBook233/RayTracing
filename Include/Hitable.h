#pragma once

#include "Ray.h"
struct HitRecord   //���н��
{
	double T;		//�����������T
	Vec3 P;			//�����
	Vec3 Normal;	//����
};

class Hitable
{
public:
	//TMin��TMax�ֱ��ʾ������ߵĿ�ʼ��������Ӧ��ϵ��T
	//Ҳ���Ǽ������ΪR = P(TMin)��R=P(TMax��֮����������
	virtual bool Hit(const Ray& R, double TMin, double TMax, HitRecord& Rec) const = 0;//�麯��
};