#include "Tank.h"


Tank::Tank(int id, int positionX)
{
	this->id = id;
	this->positionX = positionX;
}


Tank::~Tank()
{
}

void Tank::move(int contenCell){
	positionY++;
}

string Tank::getName(){
	return "Tank";
}
