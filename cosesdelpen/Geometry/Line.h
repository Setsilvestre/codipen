#pragma once
#include "Point.h"
class Line{
	Point p;
	vec3 direction;
	float alfa;
public:
	Line();
	~Line();
	//setters
	void setPointLine(const float& x, const float& y, const float & z);
	void setDirectionLine(const float& x, const float& y, const float & z);

	//functions
	float distPointToLine(Point q);
	float intersectionwithSphere(Point pAnt, Point pAct, Point center, float radi  );
	Point pointwithAlfa(float alfa);
	vec3 returnDirection();
};