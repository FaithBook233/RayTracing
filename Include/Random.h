#pragma once

class Random
{
public:
	friend inline double RandDbl01();
};

inline double RandDbl01()//����0-1֮������������
{
	return (rand() % 1000) / 1000.0;
}

