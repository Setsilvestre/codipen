#pragma once
#include "Map.h"	

class MapObjects : public Map{
	//Variable of the number of objects
	int objects;
public:
	//Create the objects
	void CreateObjects();
	//Elminiate the sword from map
	void EliminateSword();
	//Eliminate the fireball from map
	void EliminateFireball();
};