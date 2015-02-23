#include "Line.h"

Line::Line(){

}

Line::~Line(){

}

void Line::setPointLine(const float& x, const float& y, const float & z){
	this->p.coord.x = x;
	this->p.coord.y = y;
	this->p.coord.z = z;
}

void Line::setDirectionLine(const float& x, const float& y, const float & z){
	this->direction.x = x;
	this->direction.y = y;
	this->direction.z = z;
}

float Line::distPointToLine(Point q){
	float _x = p.coord.x - q.coord.x;
	float _y = p.coord.y - q.coord.y;
	float _z = p.coord.z - q.coord.z;
	vec3 newvector(_x,_y,_z);
	return length(cross(direction,newvector))/length(direction);
}

vec3 Line::returnDirection(){
	return direction;
}

Point Line::pointwithAlfa(float alfa){
	Point newPoint;
	newPoint.coord.x = p.coord.x + alfa*direction.x;
	newPoint.coord.y = p.coord.y + alfa*direction.y;
	newPoint.coord.z = p.coord.z + alfa*direction.z;
	return newPoint;
}

float Line::intersectionwithSphere(Point pAnt, Point pAct, Point center, float radi){
	vec3 vector = (pAct.coord - pAnt.coord) / length(pAct.coord - pAnt.coord);
	float a, b, c;
	a = dot(vector, vector);
	b = 2 * dot(vector, pAnt.coord - center.coord);
	c = dot(pAnt.coord, pAnt.coord) - (2* dot(center.coord,pAnt.coord)) - (radi*radi) + dot(center.coord,center.coord);
	return (-b + sqrt(b*b - 4 * a*c)) / (2*a);
}
