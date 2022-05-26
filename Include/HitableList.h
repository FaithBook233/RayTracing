#pragma once

#include "Hitable.h"

class HitableList :
	public Hitable
{
public:
	HitableList() {}
	HitableList(Hitable** L, int N) { List = L, ListSize = N; }	 //���캯��������Hitable�б���б���
	virtual bool Hit(const Ray& R, double TMin, double TMax, HitRecord& Rec)const;

	Hitable** List;//Hitable����
	int ListSize;//���鳤��
};

//���ٵ��ҳ��������еľ�������Ķ�����Ϊ��Ⱦֻ��Ⱦ��ǰ��ģ�����ı�ǰ��ĵ�ס�ˣ�
bool HitableList::Hit(const Ray& R, double TMin, double TMax, HitRecord& Rec)const
{
	HitRecord TempRec; //��¼���н��
	bool HitAnything = false;//��ʾ�Ƿ���������
	double ClosestSoFar = TMax;//��̬���������ߵ�β��

	for (int i = 0; i < ListSize; i++)//�����б�
	{
		if (List[i]->Hit(R, TMin, ClosestSoFar, TempRec))//�����ǰ���б�Ԫ�ر�����R����
		{
			HitAnything = true;	//��HitAnything����Ϊtrue����ʾ����R����������
			ClosestSoFar = TempRec.T;
			Rec = TempRec;
		}
	}
	return HitAnything;
}