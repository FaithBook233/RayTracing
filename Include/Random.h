#pragma once

class Random
{
public:
	friend inline double RandDbl01();
};

inline double RandDbl01()//生成0-1之间的随机浮点数
{
	return (rand() % 1000) / 1000.0;
}

