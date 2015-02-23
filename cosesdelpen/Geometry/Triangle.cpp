#include "Triangle.h"


Triangle::Triangle()
{
}


Triangle::~Triangle()

{
}

Triangle::Triangle(Point p, Point q, Point r){
	this->p = p;
	this->q = q;
	this->r = r;
}

float Triangle::ComputeArea(Point k, Point l, Point j){
	return 1 / 2 * (length(cross(l.coord - k.coord, j.coord - k.coord)));
}

bool Triangle::InsideorOut(Point point){
	if ((ComputeArea(point, p, q) + ComputeArea(point, p, r) + ComputeArea(point, r, q) - ComputeArea(p, q, r) )> 0.0){
		return false;
	}
	else true;
}