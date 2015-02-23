#pragma once
#include <iostream>

using namespace std;
class Object{
protected:
	//The name of the object
	string name;
	//The X position of the object
	int XPosition;
	//The Y position of the object
	int YPosition;
public:
	//Constructor
	Object();
	//Destructor
	~Object();
	//Set the values of the sword
	void setvaluesSword();
	//Set the values of the fireball
	void setvaluesFireball();
	//Get the X of the object
	int getX();
	//Set the Y of the object
	int getY();
};

class Sword :public Object{
	//Variable for the attack
	int attack;
	//Variable for the range
	int range;
public:
	//Constructor
	Sword(){
		attack = 6;
		range = 1;
	}
	//Destructor
	~Sword(){

	}
	//Get the attack
	int getAttack(){
		return attack;
	}
};


class Fireball :public Object{
	//Attack variable
	int attack;
	//Range variable
	int range;
public:
	//Constructor
	Fireball(){
		attack = 2;
		range = 8;
	}
	//Get the attack
	int getAttack(){
		return attack;
	}
};
