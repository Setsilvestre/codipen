#include "Object.h"

Object::Object(){
	name = "ghost";
	XPosition = 0;
	YPosition = 0;
}

Object::~Object(){

}

void Object::setvaluesSword(){
	XPosition = 6;
	YPosition = 9;
}

void Object::setvaluesFireball(){
	XPosition = 9;
	YPosition = 13;
}

int Object::getX(){
	return XPosition;
}

int Object::getY(){
	return YPosition;
}