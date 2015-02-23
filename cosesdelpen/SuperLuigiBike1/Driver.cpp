#include "Driver.h"


Driver::Driver()
{
	positionY = 0;
}


Driver::~Driver()
{

}

int Driver::getDriver(){
	return id;
}

int Driver::getPosX(){
	return positionX;
}

int Driver::getPosY(){
	return positionY;
}
