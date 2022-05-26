#pragma once
#include "Vec3.h"
#include "Random.h"

class Ray
{
public:
	Ray() { A = Vec3(0, 0, 0), B = Vec3(0, 0, 0); }
	Ray(const Vec3& a, const Vec3& b) { A = a; B = b; }	 //���캯������ʼ��ԭ������A�ͷ�������B
	Vec3 Origin() const { return A; } //����ԭ������A
	Vec3 Direction() const { return B; }//���ط�������B
	Vec3 PointAtParameter(double T)const { return A + T * B; }//ͨ��T�������P(t) = A + t * B
	//A��BΪ��ĳ�Ա����

	friend inline Vec3 RandomInUnitSphere();//��λ�����ڵ������
	friend inline Vec3 Reflect(const Vec3& V, const Vec3& N);//�������
	friend inline bool Refract(const Vec3& V, const Vec3& N, double NiOverNt, Vec3& Refracted);//�������

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

//�ж��Ƿ���������������
//�����ֱ�������㣬����㷨�ߣ������ʣ������Ĺ���
inline bool Refract(const Vec3& V, const Vec3& N, double NiOverNt, Vec3& Refracted)
{
	Vec3 UV = UnitVector(V);//�����λ�õĵ�λ����
	double Dt = Dot(UV, N);	//DtΪUV�ڷ���N�������ϵ�ͶӰ���ȡ�
	double Discriminant = 1.0 - NiOverNt * NiOverNt * (1 - Dt * Dt);//1-sin(theta1)^2

	//����Ҫע����ǣ�DIscriminant>0��ִ������
	if (Discriminant > 0)  //��ʾ������������
	{
		Refracted = NiOverNt * (UV - N * Dt) - N * sqrt(Discriminant);	//�õ������Ĺ���
		return true;
	}
	else
		return false;
}