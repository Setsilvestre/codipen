#pragma once
#include <glm/glm.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
using namespace std;
using namespace glm;
class Point{
public:
	Point();
	~Point();
	Point(float x, float y, float z);
	Point(const Point &p);
	//a vector
	vec3 coord;
	//setters
	void setCoord(const float& x, const float& y, const float & z);
	//functions
	//Return the distance beetwen Point and q
	virtual float distanceToPoint(const Point& q);
	//Return the point in the segment beetwen Pont and Point q
	Point pointInSegment(const Point& q, const float & alfa);
	//Overload 

	vec3 operator-(const Point&p);
};