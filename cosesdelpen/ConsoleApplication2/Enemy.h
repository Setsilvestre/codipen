#pragma once
#include "Character.h"
class Enemy : public Character{
	//if is alive
	bool state;
	//for controll the movement
	int movement;
public:
	//Constructor
	Enemy();
	//Overload Constructor
	Enemy(string _name, int _health, int _x, int _y, int _attack);
	//Destructor
	~Enemy();
	//set the info of the enemy
	void setInformation(string _name, int _health, int _x, int _y, int _attack);
	
	//change state
	void changeState();
	//To Move the enemy;
	void Move();
};