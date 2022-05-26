#pragma once
/*
	Vec3��Ϊ�ռ���ά�����RGB��ɫ�ĳ�����
	E[3]����Ϊ�����ľ�����ֵ

*/
#include<iostream>
#include<stdlib.h>
#include <Math.h>

class Vec3
{
public:
	Vec3() {};
	Vec3(double E0, double E1, double E2)
	{
		E[0] = E0;
		E[1] = E1;
		E[2] = E2;
	}
	//���ص���Ԫ�ص�ֵ
	//��Ϊλ��
	inline double X() const { return E[0]; }
	inline double Y() const { return E[1]; }
	inline double Z() const { return E[2]; }
	//��ΪRGB��ɫ
	inline double R() const { return E[0]; }
	inline double G() const { return E[1]; }
	inline double B() const { return E[2]; }

	//����Ϊ���������
	inline const Vec3& operator+() const { return *this; }
	inline Vec3 operator-() const { return Vec3(-E[0], -E[1], -E[2]); }
	inline double operator[](int i)const { return E[i]; } //����i��ȡԪ��
	inline double& operator[](int i ) { return E[i]; }	//�����±�i��ȡԪ������

	inline Vec3& operator+=(const Vec3 &V2);
	inline Vec3& operator-=(const Vec3 &V2);
	inline Vec3& operator*=(const Vec3 &V2);
	inline Vec3& operator/=(const Vec3 &V2);
	inline Vec3& operator*=(const double T);
	inline Vec3& operator/=(const double T);

	//�����������ȣ���ģ��
	inline double Vec3Length() const {
		return sqrt(E[0] * E[0] + E[1] * E[1] + E[2] * E[2]);
	 } 

	//����������ƽ��
	inline double SquaredLength() const {
		return E[0] * E[0] + E[1] * E[1] + E[2] * E[2];
	 }

	//��õ�λ����
	inline void  MakeUnitVector();


	//����ΪVec3�����Ԫ���������������������ⶨ�壬��Ԫ�����������κ���
	friend inline Vec3 UnitVector(Vec3 V);
	friend inline std::istream& operator>>(std::istream& IS, Vec3& T);
	friend inline std::ostream& operator<<(std::ostream& OS, const Vec3& T);
	friend inline Vec3 operator+(const Vec3& V1, const Vec3& V2);
	friend inline Vec3 operator-(const Vec3& V1, const Vec3& V2);
	friend inline Vec3 operator*(const Vec3& V1, const Vec3& V2);
	friend inline Vec3 operator/(const Vec3& V1, const Vec3& V2);
	friend inline Vec3 operator*(double T, const Vec3& V);
	friend inline Vec3 operator/(const Vec3& V, double T);
	friend inline Vec3 operator*(const Vec3& V, double T);
	friend inline double Dot(const Vec3& V1, const Vec3& V2);
	friend inline Vec3 Cross(const Vec3& V1, const Vec3& V2);

	//����������Ԫ��
	double E[3];

protected:
private:
	
};

//����Ϊ��ķǳ�Ա����

//������������� ���������Vec3Ԫ������
inline std::istream& operator>>(std::istream& IS, Vec3& T)
{
	IS >> T.E[0] >> T.E[1] >> T.E[2];
	return IS;
}
//�����������أ���������Vec3Ԫ������
inline std::ostream& operator<<(std::ostream& OS, const Vec3& T)
{
	OS << T.E[0] << " " << T.E[1] << " " << T.E[2];
	return OS;
}
//��ȡ�����ĵ�λ����
inline void Vec3::MakeUnitVector()
{
	double k = 1.0 / sqrt(E[0] * E[0] + E[1] * E[1] + E[2] * E[2]);
	E[0] *= k;
	E[1] *= k;
	E[2] *= k;
}

inline Vec3 operator+(const Vec3& V1, const Vec3& V2)
{
	return Vec3(V1.E[0] + V2.E[0], V1.E[1] + V2.E[1], V1.E[2] + V2.E[2]);
}
inline Vec3 operator-(const Vec3& V1, const Vec3& V2)
{
	return Vec3(V1.E[0] - V2.E[0], V1.E[1] - V2.E[1], V1.E[2] - V2.E[2]);
}
inline Vec3 operator*(const Vec3& V1, const Vec3& V2)
{
	return Vec3(V1.E[0] * V2.E[0], V1.E[1] * V2.E[1], V1.E[2] * V2.E[2]);
}
inline Vec3 operator/(const Vec3& V1, const Vec3& V2)
{
	return Vec3(V1.E[0] / V2.E[0], V1.E[1] / V2.E[1], V1.E[2] / V2.E[2]);
}

inline Vec3 operator*(double T, const Vec3& V)
{
	return Vec3(T * V.E[0], T * V.E[1], T * V.E[2]);
}
inline Vec3 operator/(const Vec3& V, double T)
{
	return Vec3(V.E[0]/T,V.E[1]/T,V.E[2]/T);
}
inline Vec3 operator*(const Vec3& V, double T)
{
	return Vec3(T * V.E[0], T * V.E[1], T * V.E[2]);
}

//���������ˣ���������� C = |a|��|b|��cos(a^b);	C = a1 * b1 + a2 * b2 + a3 * b3;
inline double Dot(const Vec3& V1, const Vec3& V2)
{
	return V1.E[0] * V2.E[0] + V1.E[1] * V2.E[1] + V1.E[2] * V2.E[2];
}


//�����Ĳ�ˣ������һ����ֱ��V1��V2����ƽ�����������ģ��Ϊ |a��b|=|a|��|b|��sin<a,b
inline Vec3 Cross(const Vec3& V1, const Vec3& V2)
{
	return Vec3(
		(V1.E[1] * V2.E[2] - V1.E[2] * V2.E[1]),
		(-(V1.E[0] * V2.E[2] - V1.E[2] * V2.E[0])),
		(V1.E[0] * V2.E[1] - V1.E[1] * V2.E[0])
	);
}
inline Vec3& Vec3::operator+=(const Vec3& V)
{
	E[0] += V.E[0];
	E[1] += V.E[1];
	E[2] += V.E[2];
	return *this;
}
inline Vec3& Vec3::operator*=(const Vec3& V)
{
	E[0] *= V.E[0];
	E[1] *= V.E[1];
	E[2] *= V.E[2];
	return *this;
}
inline Vec3& Vec3::operator-=(const Vec3& V)
{
	E[0] -= V.E[0];
	E[1] -= V.E[1];
	E[2] -= V.E[2];
	return *this;
}
inline Vec3& Vec3::operator/=(const Vec3& V)
{
	E[0] /= V.E[0];
	E[1] /= V.E[1];
	E[2] /= V.E[2];
	return *this;
}
inline Vec3& Vec3::operator*=(const double T)
{
	E[0] *= T;
	E[1] *= T;
	E[2] *= T;
	return *this;
}
inline Vec3& Vec3::operator/=(const double T)
{
	double K = 1.0 / T;
	E[0] *= K;
	E[1] *= K;
	E[2] *= K;
	return *this;
}

//����/ģ�� = ��λ��������
//�������������
inline Vec3 UnitVector(Vec3 V)
{
	return V / V.Vec3Length();
}