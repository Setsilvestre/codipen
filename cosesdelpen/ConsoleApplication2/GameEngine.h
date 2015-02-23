using namespace std;
#pragma once
#include "SDLHelpers.h"
#include "Map.h"
#include "Character.h"
#include "Hero.h"
#include "Object.h"
#include "MapObjects.h"
#include "Ranking.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <time.h>
#include "MapEnemies.h"
#include "Enemy.h"
#include <fstream>
#include "Ranking.h"
#include "FSM.h"
//Information related to the tile maps
int CONST_TILESIZE = 64;
int CONST_MAX_TILES = 26;

//Information used to know the position of the surfaces
int CONST_GRASS1_SURFACE = 0;
int CONST_GRASS2_SURFACE = 1;
int CONST_GRASS3_SURFACE = 2;
int CONST_GRASS4_SURFACE = 3;
int CONST_ROADH_SURFACE = 4;
int CONST_ROADV_SURFACE = 5;
int CONST_ROADTOPLEFT_SURFACE = 6;
int CONST_ROADTOPRIGHT_SURFACE = 7;
int CONST_ROADBOTTOMLEFT_SURFACE = 8;
int CONST_ROADBOTTOMRIGHT_SURFACE = 9;
int CONST_SNOW1_SURFACE = 10;
int CONST_SNOW2_SURFACE = 11;
int CONST_HEROE_SURFACE = 12;
int CONST_BAR = 13;
int CONST_SWORD = 14;
int CONST_EMPTY = 15;
int CONST_FIREBALL = 16;
int CONST_RIGHTSNOW = 17;
int CONST_STARTBUTTON = 18;
int CONST_GAMEOVER = 19;
int CONST_WIN = 20;
int CONST_ENEMY = 21;
int CONST_LOADGAME = 22;
int CONST_SAVEGAME = 23;
int CONST_EXIT = 24;
int CONST_LIFE = 25;
int CONST_BOSS = 26;

class GameEngine {
	//Class for the management of the SDL API
	SDLHelper graphics;
	//Class for the managment of the ranking
	Ranking file;
	//Class for the managment of the map
	Map m1;
	//Class for the managkment of the transition map
	Map secondLayer;
	//Class for the managment of the enemies map
	MapEnemies enemies;
	//Class for the managment of the object map
	MapObjects m2;
	//Class for the managment of the hero
	Hero hero;
	//Classes for the managment of the enemies
	Enemy enemy1;
	Enemy enemy2;
	Enemy boss;
	//Class for the managment of the sword
	Sword sword;
	//Class for the managment of the fireball
	Fireball fireball;
	//Class for the managment of the ranking
	Ranking ranking;
	//Class for the managment of the state machine
	FSM statemachine;
	//Classes for the managment of the timers
	clock_t start, timer;
	clock_t START, TIMER;
	//Info related to the camera
	int widthScreenResolution;
	int heightScreenResolution;
	int maxXWindowBlocks;
	int maxYWindowBlocks;
	
	//Variable for the timers
	double DIFF;
	//Variable for the score
	int score;
	//Variable for the fireball
	int FIREBALL;
	//Variables for the menu
	bool menu = true;
	bool win = false;
	bool GameOver = false;
	//Variables About the camera
	int xScreen;
	int yScreen;
	

	//information about how big is the map
	int width;
	int height;
public:
	//Constructor of the GameEngine
	GameEngine(char caption[100], int wResolution, int hResolution);
	//Executes the game
	void Run();
	//Draws the world
	void DrawWorld();
	//Processes the key pressed
	void ProcessKeyPressed(int keyType);
	//Load the state machine
	void loadDefaultGraph();
};