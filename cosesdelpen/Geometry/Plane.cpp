#include "Plane.h"
//Constructor
Plane::Plane()
{
}
//Destructor
Plane::~Plane()
{
}
//Setters
void Plane::setPlanePoint(const float& x, const float& y, const float& z){
	this->point.coord.x = x;
	this->point.coord.y = y;
	this->point.coord.z = z;
}

void Plane::setPlaneNormal(const float& x, const float& y, const float& z){
	this->normal.x = x;
	this->normal.y = y;
	this->normal.z = z;
}

void Plane::setPlaneDirect1(const float& x, const float& y, const float& z){
	this->direc1.x = x;
	this->direc1.y = y;
	this->direc1.z = z;
}
void Plane::setPlaneDirect2(const float& x, const float& y, const float& z){
	this->direc2.x = x;
	this->direc2.y = y;
	this->direc2.z = z;
}
void Plane::setPlaneFrom3Points(Point p1, Point p2, Point p3){
	this->point.coord.x = p1.coord.x;
	this->point.coord.y = p1.coord.y;
	this->point.coord.z = p1.coord.z;
	direc1.x = p2.coord.x - p1.coord.x;
	direc1.y = p2.coord.y - p1.coord.y;
	direc1.z = p2.coord.z - p1.coord.z;
	direc2.x = p3.coord.x - p1.coord.x;
	direc2.y = p3.coord.y - p1.coord.y;
	direc2.z = p3.coord.z - p1.coord.z;
	normal=cross(direc1, direc2);
}
void Plane::setDirectFromNormal(){
	setPlaneDirect1(-normal.y, normal.x, 0);
	setPlaneDirect2(normal.y, -normal.x, 0);
}
void Plane::computeD(){
	this->d = dot(-normal, point.coord);
}
//Functions
float Plane::distPlaneToPoint(Point q){
	d = dot(-normal, point.coord);
	return (length(normal.x*q.coord.x + normal.y*q.coord.y + normal.z*q.coord.z + d)) / length(normal);
}

vec3 Plane::computePlaneNormal(){
	normal = cross(direc1, direc2);
	return normal;
}

Point Plane::closestPointInPlane(Point q){
	Line newLine;
	newLine.setPointLine(q.coord.x, q.coord.y, q.coord.z);
	newLine.setDirectionLine(normal.x, normal.y, normal.z);
	vec3 newPoint;
	newPoint.x = point.coord.x;
	newPoint.y = point.coord.y;
	newPoint.z = point.coord.z;
	d = dot(-normal, newPoint);
	newPoint.x = q.coord.x;
	newPoint.y = q.coord.y;
	newPoint.z = q.coord.z;
	float alfa = (-d - dot(normal, newPoint)) / dot(normal, normal);
	return newLine.pointwithAlfa(alfa);
}

Point Plane::entryPointSegmentPlane(Point p, Point q){
	Line newLine;
	newLine.setPointLine(p.coord.x, p.coord.y, p.coord.z);
	newLine.setDirectionLine(q.coord.x - p.coord.x, q.coord.y - p.coord.y, q.coord.z - p.coord.z);
	float alfa = (-d - dot(normal, p.coord)) / dot(normal, newLine.returnDirection());
	return newLine.pointwithAlfa(alfa);
}

bool Plane::changePosition(Point p){
	if ((normal.x*p.coord.x + normal.y*p.coord.y + normal.z*p.coord.z + d) / sqrt(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z) < 0){
		return false;
	}
	else return true;
}