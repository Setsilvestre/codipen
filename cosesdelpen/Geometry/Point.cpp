#include "Point.h"

Point::Point() :coord(0.0f, 0.0f, 0.0f){

}

Point::~Point(){

}
Point::Point(const Point &p){
	this->coord.x = p.coord.x;
	this->coord.y = p.coord.y;
	this->coord.z = p.coord.z;
}
Point::Point(float x, float y, float z){
	this->coord.x = x;
	this->coord.y = y;
	this->coord.z = z;
}
void Point::setCoord(const float& x, const float& y, const float & z){
	coord = vec3(x, y, z);
}

float Point::distanceToPoint(const Point& q){
	return length(coord - q.coord);
}

Point Point::pointInSegment(const Point& q, const float & alfa){
	Point pp;
	pp.coord = coord*(1 - alfa) + alfa*q.coord;
	return pp;
}


vec3 Point::operator-(const Point&p){
	Point point;
	point.coord.x = this->coord.x - p.coord.x;
	point.coord.y = this->coord.y - p.coord.y;
	point.coord.z = this->coord.z - p.coord.z;
	vec3 vector;
	vector = vec3(point.coord.x, point.coord.y, point.coord.z);
	return vector;
}

