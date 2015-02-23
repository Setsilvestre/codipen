#pragma once
#include "Driver.h"

class Tank :
	public Driver
{
public:
	Tank(int id, int positionX);
	~Tank();
	void move(int contenCell);
	string getName();
};

