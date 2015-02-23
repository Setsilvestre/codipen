#pragma once 
#include "Character.h"
#include "Object.h"
class Hero : public Character{
	//Variable for the number of objects
	int numObjects;
	//Variable for the hero level
	int level;
	//Variable for the hero surface
	int idSurface;
	//Variable for pick the sword
	int sword;
	//Variable for pick the fireball
	int fireball;
	//Class for the inventory managment
	Object* inventory;
public:
	//Constructor
	Hero();
	//Destructor
	~Hero();
	//Overload constructor
	Hero(string _name, int _health, int _x, int _y, int _attack, int _numObjects, int _level, int _idSurface, int _sword);
	//Create the inventory function
	void createInventory();
	//Pick object
	void pickObject();
	//Move up the hero
	void MoveUp();
	//Move down the hero
	void MoveDown();
	//Move to the left the hero
	void MoveLeft();
	//Move to the right the hero
	void MoveRight();
	//Set the information abaout the hero function
	void setInformation(string _name, int _health, int _x, int _y, int _attack, int _numObjects, int _level, int _idSurface,int _sword);
	//Set the sowrd information
	int getSword();
	//Set the fireball information
	int getFireball();
	//Get the name
	string getName();
	//Pick the sword
	void pickSword();
	//Pick the fireball
	void pickFireball();
	//Set the sword variable
	void setSword(int x);
	//Set the fireball variable
	void setFireball(int x);
};