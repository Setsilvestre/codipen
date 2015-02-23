#pragma once

using namespace std;
#include <exception>			//Management of exceptions
#include <iostream>				//Management of cin and cout
#include <stdlib.h>				//Management of random numbers: srand, rand 
#include <time.h>				//Management of time features
#include <cstdlib>				//Management of system functions such as pause
#include <fstream>				//Managment of the save/load game

//create the class map
class Map{
//attributes for the class map
protected:
	//Data of each cell
	int ** data;
	//Variables for the data to save/load
	int temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9, temp10, temp11;
public:
	int rows;
	int cols;
	//constructor
	Map();
	//destructor
	~Map();
	//Overload Constructor
	Map(int x, int y);
	//Create the map, the first parameter is the number of columns, and the second parameter is the number of rows
	void CreateMap(int x, int y);
	//Use the function create map and assign to each field a number for the surface
	void LoadMap();
	//Use the function create map and assign to each field a number for the surface for a transition beetwen surfaces
	void LoadSecondLayer();
	//return the number of the surface stored on the position x,y
	int getSurface(int x, int y);
	//Return the number of columns
	int getColumns();
	//return the number of rows
	int getRows();
	//Set the surface
	void Set(int x, int y, int _data);
	//Save the map
	void SaveMap( int x, int y, int sword, int fireball, int xenemy, int yenemy, int xenemy2, int yenemy2,int xboss, int yboss, int health, int map);
	//Load the map
	void LoadMap( int map);
	//Return the X hero position
	int HeroPosX();
	//Return the Y hero position
	int HeroPosY();
	//Return the health
	int HeroHealth();
	//Return the sword variable
	int Sword();
	//Return the fireball variable
	int Fireball();
	//Return the X enemy position
	int EnemyX();
	//Return the Y enemy position
	int EnemyY();
	//Return the X enemy2 position
	int EnemyX2();
	//Return the Y enemy2 position
	int EnemyY2();
	//Get the X boss position
	int getXBoss();
	//Get the Y boss position
	int getYBoss();

};