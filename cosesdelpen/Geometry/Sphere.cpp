#include "Sphere.h"


Sphere::Sphere()
{
}


Sphere::~Sphere()
{
}
Sphere::Sphere(Point center, float radius){
	this->center = center;
	this->radius = radius;
}
//functions
bool Sphere::InsideorOut(Point p){
	if (length(p.coord - center.coord) > radius){
		return false;
	}
	else if (length(p.coord - center.coord) < radius){
		return true;
	}
}
float Sphere::ComputeArea(){
	
	return  4 * M_PI*radius*radius;
}
float Sphere::ComputeVolume(){
	return (4 / 3)*M_PI*radius*radius*radius;
}

Point Sphere::returnCenter(){
	return center;
}

float Sphere::returnRadius(){
	return radius;
}

