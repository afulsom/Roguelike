#ifndef POINT_H
#define POINT_H
#include "stdafx.h"


class Point
{
private:

public:
	int X;
	int Y;
	Point();
	Point(int, int);
	Point(const Point&);
	~Point();
	Point& operator+(Point&);
	Point& operator-(Point&);
	bool operator==(Point&);
	int getVectorDist();


};

#endif