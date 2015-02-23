#pragma once
#include "Line.h"
class Sphere
{
	Point center;
	float radius;
public:
	Sphere();
	~Sphere();
	Sphere(Point center, float radius);
	//functions
	bool InsideorOut(Point p);
	float ComputeArea();
	float ComputeVolume();
	Point returnCenter();
	float returnRadius();
};

