#pragma once
#include <fstream>	
#include <iostream>
#include <exception>
#include <string>
using namespace std;
//class for managing the ranking
class Ranking{
	//where the name of the players will be stored
	string players[10];
	//score of the players
	int score[10];
public:
	//Ghost Constructor
	Ranking();
	//Destructor
	~Ranking();
	//Update the name
	void declareName(string name);
	//Update the score
	void declarescore(int x, string name);
	//print the ranking
	void DrawRanking();
	//create a bin file
	void CreateRanking(char filename[100]);
};

