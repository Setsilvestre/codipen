#pragma once
#include <iostream>
using namespace std;
#include <string>

class Character{
protected:
	string name;
	int health;
	int Xposition;
	int Yposition;
	int attack;
public:
	Character();
	~Character();
	Character(string _name, int _health, int _x, int _y, int _attack);
	void setX(int x);
	void setY(int y);
	int getHealth();
	int getAttack();
	void lossHealth(int x);
	void setHealth(int health);
	int getX();
	int getY();
};
