#include "Car.h"


Car::Car(int id, int positionX)
{
	this->id = id;
	this->positionX = positionX;
}


Car::~Car()
{
}

void Car::move(int contenCell){
	if (contenCell == -1){
		positionY = positionY + 2;
	}
}

string Car::getName(){
	return"Car";
}

