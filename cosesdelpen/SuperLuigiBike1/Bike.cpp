#include "Bike.h"


Bike::Bike(int id, int positionX)
{
	this->id = id;
	this->positionX = positionX;
}


Bike::~Bike()
{
}

void Bike::move(int contenCell){
	if (contenCell == -2){
		positionY = positionY + 2;
	}
	else{
		positionY++;
	}
}

string Bike::getName(){
	return "Bike";
}


