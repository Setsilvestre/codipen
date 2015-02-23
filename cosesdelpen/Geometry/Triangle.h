#pragma once
#include "Point.h"
class Triangle
{
	Point p, q, r;
public:
	Triangle();
	~Triangle();
	Triangle(Point p, Point q, Point r);
	bool InsideorOut(Point point);
	float ComputeArea(Point k, Point l, Point j);
};

