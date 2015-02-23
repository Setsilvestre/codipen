#pragma once
#include "Driver.h"
class Bike :
	public Driver
{
public:
	Bike(int id, int positionX);
	~Bike();
	void move(int contenCell);
	string getName();
};

