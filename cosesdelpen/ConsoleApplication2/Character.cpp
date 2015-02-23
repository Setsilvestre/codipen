#include "Character.h"
/**
* Ghost Constructor.It initialize the character class
*/
Character::Character(){
	name = "ghost";
	health = 0;
	Xposition = 0;
	Yposition = 0;
	attack = 0;
}
/**
* Destructor. 
*/
Character::~Character(){

}
/**
* Overload Constructor. It initialize the character class
* @param _name is the name of the character
* @param _health is the health of the character
* @param _x is the x position of the character
* @param _y is the y position of the character
* @param _attack is the attack of the character
*/
Character::Character(string _name, int _health, int _x, int _y, int _attack){
	name = _name;
	health = _health;
	Xposition = _x;
	Yposition = _y;
	attack = _attack;
}
/**
* Set the X position of the character
* @param x is the new x position of the character
*/
void Character::setX(int x){
	Xposition = x;
}
/**
* Set the Y position of the character
* @param y is the new y position of the character
*/
void Character::setY(int y){
	Yposition = y;
}
/**
* Return the health value of the character
*/
int Character::getHealth(){
	return health;
}
/**
* Return the attack value of the character
*/
int Character::getAttack(){
	return attack;
}
/**
* Remove health of the character
* @param x is the health value that will be removed
*/
void Character::lossHealth(int x){
	health = health - x;
}
/**
* Set health of the character
* @param health is the health value that will be set
*/
void Character::setHealth(int health){
	this->health = health;
}
/**
* Get the x position of the character
*/
int Character::getX(){
	return Xposition;
}
/**
*Get the y position of the character
*/
int Character::getY(){
	return Yposition;
}