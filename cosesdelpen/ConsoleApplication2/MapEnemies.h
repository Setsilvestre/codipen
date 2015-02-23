#pragma once

using namespace std;
#include <exception>			//Management of exceptions
#include <iostream>				//Management of cin and cout
#include <stdlib.h>				//Management of random numbers: srand, rand 
#include <time.h>				//Management of time features
#include <cstdlib>				//Management of system functions such as pause
#include <fstream>

class MapEnemies{
	//Variable for the information of each cell
	int ** data;
	
public:
	//Rows and columns variables
	int rows;
	int cols;
	//constructor
	MapEnemies();
	//destructor
	~MapEnemies();
	//Create the map, the first parameter is the number of columns, and the second parameter is the number of rows
	void CreateMap(int x, int y);
	//Use the function create map and assign to each field a number for the surface
	void LoadMap();
	//return the number of the surface stored on the position x,y
	int getSurface(int x, int y);
	//change the value of a position
	void change(int x, int y, int value);
	//Save the map
	void SaveMap(int x, int y, int sword, int fireball, int xenemy, int yenemy, int map);
	//Load the map
	void LoadMapEnemies();
};