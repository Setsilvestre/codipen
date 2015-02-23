#pragma once
#include "Driver.h"
class Car :
	public Driver
{
public:
	Car(int id, int positionX);
	~Car();
	void move(int contenCell);
	string getName();
};

