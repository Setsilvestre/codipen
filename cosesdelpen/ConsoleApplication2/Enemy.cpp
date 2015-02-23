#include "Enemy.h"
/**
* Constructor.It initialize the enemy class and declare the state to true(alive)
*/
Enemy::Enemy(){
	state = true;
}
/**
* Overload Constructor. It initialize the character class using constructor list
* @param _name is the name of the character
* @param _health is the health of the character
* @param _x is the x position of the character
* @param _y is the y position of the character
* @param _attack is the attack of the character
*set the state to true(alive) and the movement to 0(moving pattern)
*/
Enemy::Enemy(string _name, int _health, int _x, int _y, int _attack) : Character(_name, _health, _x, _y, _attack){
	state = true;
	movement = 0;
}
//Destructor
Enemy::~Enemy(){
	Xposition = NULL;
	Yposition = NULL;
}
/**
* Set the values of the enemy class
* @param _name is the name of the character
* @param _health is the health of the character
* @param _x is the x position of the character
* @param _y is the y position of the character
* @param _attack is the attack of the character
*/
void Enemy::setInformation(string _name, int _health, int _x, int _y, int _attack){
	this->name = _name;
	this->health = _health;
	this->Xposition = _x;
	this->Yposition = _y;
	this->attack = _attack;
}


//Change the state from live to dead
void Enemy::changeState(){
	if (state == false){
		state = true;
	}
	else state = false;
}

/**
* Move those enemies that follow a square pattern. top->left->down->right->top
*/
void Enemy::Move(){
	if (movement == 0){
		setY(getY() - 1);
		movement=1;
	}
	else if (movement == 1){
		setX(getX() + 1);
		movement = 2;
	}
	else if (movement == 2){
		setY(getY() + 1);
		movement = 3;
	}
	else {
		setX(getX() - 1);
		movement = 0;
	}
}