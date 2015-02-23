#pragma once
#include "Line.h"
class Plane
{
	// variables
	Point point;
	vec3 direc1;
	vec3 direc2;
	vec3 normal;
	float d;
public:
	// setters
	void setPlanePoint(const float& x, const float& y, const float& z);
	void setPlaneNormal(const float& x, const float& y, const float& z);
	void setPlaneDirect1(const float& x, const float& y, const float& z);
	void setPlaneDirect2(const float& x, const float& y, const float& z);
	void setPlaneFrom3Points(Point p1, Point p2, Point p3);
	void setDirectFromNormal();
	void computeD();
	// functions
	float distPlaneToPoint(Point q);
	vec3 computePlaneNormal();
	Point closestPointInPlane(Point q);
	Point entryPointSegmentPlane(Point p, Point q);
	bool changePosition(Point p);
	//Constructor
	Plane();
	//Destructor
	~Plane();
};

