#include "stdafx.h"
#include "Point.h"

Point::Point()
{
	X = 0;
	Y = 0;
};

Point::Point(int x, int y)
{
	X = x;
	Y = y;
}

Point::Point(const Point& inPoint)
{
	X = inPoint.X;
	Y = inPoint.Y;
}

Point::~Point()
{

}

Point& Point::operator+(Point& inPoint)
{
	X += inPoint.X;
	Y += inPoint.Y;
	return *this;
}

Point& Point::operator-(Point& inPoint)
{
	X -= inPoint.X;
	Y -= inPoint.Y;
	return *this;
}

bool Point::operator==(Point& inPoint)
{
	if (this->X == inPoint.X && this->Y == inPoint.Y)
		return true;
	return false;
}

int Point::getVectorDist()
{
	return abs(X) + abs(Y);
}