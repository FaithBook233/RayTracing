#pragma once

#include "Hitable.h"

class HitableList :
	public Hitable
{
public:
	HitableList() {}
	HitableList(Hitable** L, int N) { List = L, ListSize = N; }	 //构造函数，传入Hitable列表和列表长度
	virtual bool Hit(const Ray& R, double TMin, double TMax, HitRecord& Rec)const;

	Hitable** List;//Hitable数组
	int ListSize;//数组长度
};

//快速地找出射线命中的距离最近的对象（因为渲染只渲染最前面的，后面的被前面的挡住了）
bool HitableList::Hit(const Ray& R, double TMin, double TMax, HitRecord& Rec)const
{
	HitRecord TempRec; //记录命中结果
	bool HitAnything = false;//表示是否命中物体
	double ClosestSoFar = TMax;//动态的设置射线的尾端

	for (int i = 0; i < ListSize; i++)//遍历列表
	{
		if (List[i]->Hit(R, TMin, ClosestSoFar, TempRec))//如果当前的列表元素被射线R命中
		{
			HitAnything = true;	//将HitAnything设置为true，表示射线R命中了物体
			ClosestSoFar = TempRec.T;
			Rec = TempRec;
		}
	}
	return HitAnything;
}