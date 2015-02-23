#include "Hero.h"
/**
* Ghost Constructor. Initialize the parameters to 0
*/
Hero::Hero(){
	numObjects = 0;
	level = 0;
	idSurface = 0;
}
/**
* Overload constructor. It pass the parameters to the internal data structures
* @param _name is the name of the character
* @param _health is the health of the character
* @param _x is the x position of the character
* @param _y is the y position of the character
* @param _attack is the attack of the character
* @param _numObjects is the number of objects that hero contains
* @param _level is the level of the hero, in the case of the game is always 1
* @param _idSurface is the number of surface that contains the hero
* @param _sword is for if the hero starts with sword or not
*/
Hero::Hero(string _name, int _health, int _x, int _y, int _attack, int _numObjects, int _level, int _idSurface,int _sword) : Character(_name, _health, _x, _y, _attack){
	numObjects = _numObjects;
	level = _level;
	idSurface = _idSurface;
	sword = _sword;
}

//Destructor
Hero::~Hero() {
}
/**
* Set the info for the hero, and always starts with no fireball
* @param _name is the name of the character
* @param _health is the health of the character
* @param _x is the x position of the character
* @param _y is the y position of the character
* @param _attack is the attack of the character
* @param _numObjects is the number of objects that hero contains
* @param _level is the level of the hero, in the case of the game is always 1
* @param _idSurface is the number of surface that contains the hero
* @param _sword is for if the hero starts with sword or not
*/
void Hero::setInformation(string _name, int _health, int _x, int _y, int _attack, int _numObjects, int _level, int _idSurface,int _sword){
	this->name = _name;
	this->health = _health;
	this->Xposition = _x;
	this->Yposition = _y;
	this->attack = _attack;
	this->numObjects = _numObjects;
	this->level = _level;
	this->idSurface = _idSurface;
	this->sword = _sword;
	this->fireball = 0;
}

/**
* Moves up the hero, changing the Yposition
*/
void Hero::MoveUp(){
	Yposition--;
	if (Yposition < 0){
		Yposition = 0;
	}
}
/**
* Moves down the hero, changing the Yposition
*/
void Hero::MoveDown(){
	Yposition++;
	if (Yposition>15){	
		Yposition = 15;
	}
}
/**
* Moves left the hero, changing the Xposition
*/
void Hero::MoveLeft(){
	Xposition--;
	if (Xposition < 0){
		Xposition = 0;
	}
}
/**
* Moves right the hero, changing the Xposition
*/
void Hero::MoveRight(){
	Xposition++;
	if (Xposition > 15){
		Xposition = 15;
	}
}

/**
*Create the inventory of the hero
*/
void Hero::createInventory(){
	inventory = new Object[numObjects];
}

/**
* Return if the hero has the sword (1) or not (0)
*/
int Hero::getSword(){
	return sword;
}

/**
* Set the sword to 1
*/
void Hero::pickSword(){
	this->sword = 1;
}

/**
* Set the fireball to 1
*/
void Hero::pickFireball(){
	this->fireball = 1;
}

/**
* Return the name of the hero
*/
string Hero::getName(){
	return name;
}

/**
* Return the fireball value (1 has it) (0 doesn't)
*/
int Hero::getFireball(){
	return fireball;
}

/**
* Set the sword to the x paramater
* @param x is the value assigned to sword(picks it or not)
*/
void Hero::setSword(int x){
	sword = x;
}
/**
* Set the fireball to the x paramater
* @param x is the value assigned to fireball(picks it or not)
*/
void Hero::setFireball(int x){
	fireball = x;
}