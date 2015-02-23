#pragma once
#include <string>
using namespace std;

class Driver
{
protected:
	int id, speed, positionX, positionY;
public:
	Driver();
	~Driver();
	int getDriver();
	int getPosX();
	int getPosY();
	virtual void move(int contenCell)=0;
	virtual string getName() = 0;
};

