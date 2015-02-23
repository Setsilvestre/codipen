#include "GameEngine.h"

const int DYING = 0;
const int SEE = 1;
const int RECOVERANDSEE= 2;
const int RECOVERANDNOTSEE = 3;

/**
* Create the state machine graph for the boss. It has three nodes(steady, run, attack) and four edges(dying, seeing, recover and see, recover and not see)
*/
void GameEngine::loadDefaultGraph() {
	statemachine.addEdge(0, 0, DYING);
	statemachine.addEdge(0, 0, SEE);
	statemachine.addEdge(0, 2, RECOVERANDSEE);
	statemachine.addEdge(0, 1, RECOVERANDNOTSEE);
	statemachine.addEdge(1, 0, DYING);
	statemachine.addEdge(1, 2, SEE);
	statemachine.addEdge(1, 2, RECOVERANDSEE);
	statemachine.addEdge(1, 1, RECOVERANDNOTSEE);
	statemachine.addEdge(2, 0, DYING);
	statemachine.addEdge(2, 2, RECOVERANDSEE);
	statemachine.addEdge(2, 1, RECOVERANDNOTSEE);
}


/**
* Constructor. It initialize all the engine
* @param caption is the window title
* @param wResolution is the with resolution
* @param hResolution is the height resolution
* @param statemachine(3,4,-1) create the state machine graph
*/
GameEngine::GameEngine(char caption[100], int wResolution, int hResolution) :statemachine(3, 4, -1) {
	//initialize the height and width of the screen.
	width = 16;
	height = 16;
	//initialize the score
	score = 0;
	//initialize the variables for controlling game logic
	TIMER = 0;
	FIREBALL = 0;
	//Copy the window size properties
	widthScreenResolution = wResolution;
	heightScreenResolution = hResolution;
	
	//set the values for the object classes
	sword.setvaluesSword();
	fireball.setvaluesFireball();

	//Compute how many blocks will be drawn on the screen
	maxXWindowBlocks = wResolution / CONST_TILESIZE;
	maxYWindowBlocks = hResolution / CONST_TILESIZE;
	
	//Load the surface map
	m1.LoadMap();

	//Load the object map
	m2.CreateObjects();

	//Load the transition map
	secondLayer.LoadSecondLayer();

	//Load the enemies map
	enemies.LoadMap();

	//Set the hero values, and create the name and score for the ranking
	hero.setInformation("Player", 100, 0, 0, 10, 1, 1, 12, 0);
	ranking.declareName(hero.getName());
	ranking.declarescore(score,hero.getName());

	//Set the enemies values
	enemy1.setInformation("Enemy", 20, 13, 5, 20);
	enemy2.setInformation("Enemy", 20, 5, 4, 20);
	boss.setInformation("Boss", 50, 13, 13, 35);

	//Create the state machine
	loadDefaultGraph();

	
	//Initialize the video mode
	graphics.InitializeVideo(caption, widthScreenResolution, heightScreenResolution);

	//Allocate memory for the different kind of images that game will use
	graphics.setNumSurfaces(CONST_MAX_TILES);

	//Load the different surfaces
	graphics.LoadImageintoSurface(CONST_GRASS1_SURFACE, "./images/grass1.bmp");
	graphics.LoadImageintoSurface(CONST_GRASS2_SURFACE, "./images/grass2.bmp");
	graphics.LoadImageintoSurface(CONST_GRASS3_SURFACE, "./images/grass3.bmp");
	graphics.LoadImageintoSurface(CONST_GRASS4_SURFACE, "./images/grass4.bmp");
	graphics.LoadImageintoSurface(CONST_ROADH_SURFACE, "./images/roadh.bmp");
	graphics.LoadImageintoSurface(CONST_ROADV_SURFACE, "./images/roadv.bmp");
	graphics.LoadImageintoSurface(CONST_ROADTOPLEFT_SURFACE, "./images/roadtopleft.bmp");
	graphics.LoadImageintoSurface(CONST_ROADTOPRIGHT_SURFACE, "./images/roadtopright.bmp");
	graphics.LoadImageintoSurface(CONST_ROADBOTTOMLEFT_SURFACE, "./images/roadbottomleft.bmp");
	graphics.LoadImageintoSurface(CONST_ROADBOTTOMRIGHT_SURFACE, "./images/roadbottomright.bmp");
	graphics.LoadImageintoSurface(CONST_SNOW1_SURFACE, "./images/snow1.bmp");
	graphics.LoadImageintoSurface(CONST_SNOW2_SURFACE, "./images/snow2.bmp");
	graphics.LoadImageintoSurface(CONST_HEROE_SURFACE, "./images/character.bmp");
	graphics.LoadImageintoSurface(CONST_BAR, "./images/objects/bar.bmp");
	graphics.LoadImageintoSurface(CONST_SWORD, "./images/objects/wepicon-sword.bmp");
	graphics.LoadImageintoSurface(CONST_EMPTY, "./images/vacio.bmp");
	graphics.LoadImageintoSurface(CONST_FIREBALL, "./images/objects/fireball.bmp");
	graphics.LoadImageintoSurface(CONST_RIGHTSNOW, "./images/terrain/snowright.bmp");
	graphics.LoadImageintoSurface(CONST_STARTBUTTON, "./images/Start.bmp");
	graphics.LoadImageintoSurface(CONST_SAVEGAME, "./images/Save.bmp");
	graphics.LoadImageintoSurface(CONST_LOADGAME, "./images/Load.bmp");
	graphics.LoadImageintoSurface(CONST_EXIT, "./images/Exit.bmp");
	graphics.LoadImageintoSurface(CONST_GAMEOVER, "./images/GameOver.bmp");
	graphics.LoadImageintoSurface(CONST_WIN, "./images/Win.bmp");
	graphics.LoadImageintoSurface(CONST_ENEMY, "./images/enemigo.bmp");
	graphics.LoadImageintoSurface(CONST_LIFE, "./images/life.bmp");
	graphics.LoadImageintoSurface(CONST_BOSS, "./images/boss.bmp");
}


/**
Draw all the information of the world from dataGame
*/
void GameEngine::DrawWorld() {
	//Clear the screen to white.
	graphics.ClearWindow();
	//Display win screen
	if (win){
		graphics.DrawSurface(CONST_WIN, 0, 2 * 64);
	}
	//Display Game Over screen
	else if (GameOver){
		graphics.DrawSurface(CONST_GAMEOVER, 0, 3* 64);
	}
	//Print the menu if it so
	else if (menu){
		graphics.DrawSurface(CONST_STARTBUTTON, 0, 0);
		graphics.DrawSurface(CONST_SAVEGAME, 0, 2*64);
		graphics.DrawSurface(CONST_LOADGAME, 0, 4*64);
		graphics.DrawSurface(CONST_EXIT, 0, 6*64);
	}
	//Draw the game
	else{
		//Check every position of the hero in the map to draw the world in each case so the screen never leaves the map
		//Top left
		if (hero.getX() < floor(10 / 2) && hero.getY() < floor(8 / 2)){
			for (int i = 0; i < 10; i++){
				for (int j = 0; j < 8; j++){
					graphics.DrawSurface(m1.getSurface(i, j), i * 64, j * 64);
				}
			}
		}
		//top
		else if (hero.getX() >= floor(10 / 2) && hero.getX() <= 16 - 5 && hero.getY() < floor(8 / 2)){
			for (int i = hero.getX() - floor(10 / 2); i < hero.getX() + floor(10 / 2); i++){
				for (int j = 0; j < 8; j++){
					graphics.DrawSurface(m1.getSurface(i, j), (i - (hero.getX() - floor(10 / 2))) * 64, j * 64);
				}
			}
		}
		//top right
		else if (hero.getX() > 16 - floor(10 / 2) && hero.getY() < floor(8 / 2)){
			for (int i = 16 - 10; i < 16; i++){
				for (int j = 0; j < 8; j++){
					graphics.DrawSurface(m1.getSurface(i, j), (i - (16 - 10)) * 64, j * 64);
				}
			}
		}
		//left
		else if (hero.getX() < floor(10 / 2) && hero.getY() >= floor(8 / 2) && hero.getY() <= 16 - 4){
			for (int i = 0; i < 10; i++){
				for (int j = hero.getY() - floor(8 / 2); j < hero.getY() + floor(8 / 2); j++){
					graphics.DrawSurface(m1.getSurface(i, j), i * 64, (j - (hero.getY() - floor(8 / 2))) * 64);
				}
			}
		}
		//bottom left
		else if (hero.getY() > 16 - floor(8 / 2) && hero.getX() < floor(10 / 2)){
			for (int i = 0; i < 10; i++){
				for (int j = 16 - 8; j < 16; j++){
					graphics.DrawSurface(m1.getSurface(i, j), i * 64, (j - (16 - 8)) * 64);
				}
			}
		}
		//bottom
		else if (hero.getX() >= floor(10 / 2) && hero.getX() <= 16 - 5 && hero.getY() > 16 - floor(8 / 2)){
			for (int i = hero.getX() - floor(10 / 2); i < hero.getX() + floor(10 / 2); i++){
				for (int j = 16 - 8; j < 16; j++){
					graphics.DrawSurface(m1.getSurface(i, j), (i - (hero.getX() - floor(10 / 2))) * 64, (j - 8) * 64);
				}
			}
		}
		//right
		else if (hero.getX() > 16 - floor(10 / 2) && hero.getY() >= floor(8 / 2) && hero.getY() <= 16 - 4){
			for (int i = 16 - 10; i < 16; i++){
				for (int j = hero.getY() - floor(8 / 2); j < hero.getY() + floor(8 / 2); j++){
					graphics.DrawSurface(m1.getSurface(i, j), (i - 6) * 64, (j - (hero.getY() - floor(8 / 2))) * 64);
				}
			}
		}
		//bottom right
		else if (hero.getY() > 16 - floor(8 / 2) && hero.getX() > 16 - floor(10 / 2)){
			for (int i = 16 - 10; i < 16; i++){
				for (int j = 16 - 8; j < 16; j++){
					graphics.DrawSurface(m1.getSurface(i, j), (i - (16 - 10)) * 64, (j - (16 - 8)) * 64);
				}
			}
		}
		//center
		else{
			for (int i = hero.getX() - floor(10 / 2); i < hero.getX() + floor(10 / 2); i++){
				for (int j = hero.getY() - floor(8 / 2); j < hero.getY() + floor(8 / 2); j++){
					graphics.DrawSurface(m1.getSurface(i, j), (i - (hero.getX() - floor(10 / 2))) * 64, (j - (hero.getY() - floor(8 / 2))) * 64);
				}
			}
		}
		//Draw the objects, hero, the second layer and the enemies using the same logic as before. It draws the fireball spell if we press Space using the FIREBALL variable
		//top left
		if (hero.getX() < floor(10 / 2) && hero.getY() < floor(8 / 2)){
			for (int i = 0; i < 10; i++){
				for (int j = 0; j < 8; j++){
					if (secondLayer.getSurface(i, j) != 15){
						graphics.DrawSurface(secondLayer.getSurface(i, j), i * 64, j * 64);
					}

					if (m2.getSurface(i, j) != 15){
						graphics.DrawSurface(m2.getSurface(i, j), i * 64, j * 64);
					}

					if (enemies.getSurface(i, j) !=-1){
						graphics.DrawSurface(enemies.getSurface(i, j), i * 64, j * 64);
					}
					if (FIREBALL == 1){
						for (int i = 0; i < 4; i++){
							graphics.DrawSurface(CONST_FIREBALL, hero.getX() * 64 + i * 64, hero.getY() * 64);
							graphics.DrawSurface(CONST_FIREBALL, hero.getX() * 64 - i * 64, hero.getY() * 64);
						}
					}
					graphics.DrawSurface(CONST_HEROE_SURFACE, hero.getX() * 64, hero.getY() * 64);
				}
			}

		}
		//top
		else if (hero.getX() >= floor(10 / 2) && hero.getX() <= 16 - 5 && hero.getY() < floor(8 / 2)){
			for (int i = hero.getX() - floor(10 / 2); i < hero.getX() + floor(10 / 2); i++){
				for (int j = 0; j < 8; j++){
					if (secondLayer.getSurface(i, j) != 15){
						graphics.DrawSurface(secondLayer.getSurface(i, j), (i - (hero.getX() - floor(10 / 2))) * 64, j * 64);
					}
					if (m2.getSurface(i, j) != 15){
						graphics.DrawSurface(m2.getSurface(i, j), (i - (hero.getX() - floor(10 / 2))) * 64, j * 64);
					}
					if (enemies.getSurface(i, j) != -1){
						graphics.DrawSurface(enemies.getSurface(i, j), (i - (hero.getX() - floor(10 / 2))) * 64, j * 64);
					}
					if (FIREBALL == 1){
						for (int i = 0; i < 4; i++){
							graphics.DrawSurface(CONST_FIREBALL, floor(10 / 2) * 64 + i * 64, hero.getY() * 64);
							graphics.DrawSurface(CONST_FIREBALL, floor(10 / 2) * 64 - i * 64, hero.getY() * 64);
						}
					}
					graphics.DrawSurface(CONST_HEROE_SURFACE, floor(10 / 2) * 64, hero.getY() * 64);
				}
			}
		}
		//top right
		else if (hero.getX() > 16 - floor(10 / 2) && hero.getY() < floor(8 / 2)){
			for (int i = 16 - 10; i < 16; i++){
				for (int j = 0; j < 8; j++){
					if (secondLayer.getSurface(i, j) != 15){
						graphics.DrawSurface(secondLayer.getSurface(i, j), (i - (16 - 10)) * 64, j * 64);
					}
					if (m2.getSurface(i, j) != 15){
						graphics.DrawSurface(m2.getSurface(i, j), (i - (16 - 10)) * 64, j * 64);
					}
					if (enemies.getSurface(i, j) != -1){
						graphics.DrawSurface(enemies.getSurface(i, j), (i - (16 - 10)) * 64, j * 64);
					}
					if (FIREBALL == 1){
						for (int i = 0; i < 4; i++){
							graphics.DrawSurface(CONST_FIREBALL, (hero.getX() - 6) * 64 + i * 64, hero.getY() * 64);
							graphics.DrawSurface(CONST_FIREBALL, (hero.getX() - 6) * 64 - i * 64, hero.getY() * 64);
						}
					}
					graphics.DrawSurface(CONST_HEROE_SURFACE, (hero.getX() - 6) * 64, hero.getY() * 64);
				}
			}
		}
		//left
		else if (hero.getX() < floor(10 / 2) && hero.getY() >= floor(8 / 2) && hero.getY() <= 16 - 4){
			for (int i = 0; i < 10; i++){
				for (int j = hero.getY() - floor(8 / 2); j < hero.getY() + floor(8 / 2); j++){
					if (secondLayer.getSurface(i, j) != 15){
						graphics.DrawSurface(secondLayer.getSurface(i, j), i * 64, (j - (hero.getY() - floor(8 / 2))) * 64);
					}
					if (m2.getSurface(i, j) != 15){
						graphics.DrawSurface(m2.getSurface(i, j), i * 64, (j - (hero.getY() - floor(8 / 2))) * 64);
					}
					if (enemies.getSurface(i, j) != -1){
						graphics.DrawSurface(enemies.getSurface(i, j), i * 64, (j - (hero.getY() - floor(8 / 2))) * 64);
					}
					if (FIREBALL == 1){
						for (int i = 0; i < 4; i++){
							graphics.DrawSurface(CONST_FIREBALL, hero.getX() * 64 + i * 64, floor(8 / 2) * 64);
							graphics.DrawSurface(CONST_FIREBALL, hero.getX() * 64 - i * 64, floor(8 / 2) * 64);
						}
					}
					graphics.DrawSurface(CONST_HEROE_SURFACE, hero.getX() * 64, floor(8 / 2) * 64);
				}
			}
		}
		//bottom left
		else if (hero.getY() > 16 - floor(8 / 2) && hero.getX() < floor(10 / 2)){
			for (int i = 0; i < 10; i++){
				for (int j = 16 - 8; j < 16; j++){
					if (secondLayer.getSurface(i, j) != 15){
						graphics.DrawSurface(secondLayer.getSurface(i, j), i * 64, (j - (16 - 8)) * 64);
					}
					if (m2.getSurface(i, j) != 15){
						graphics.DrawSurface(m2.getSurface(i, j), i * 64, (j - (16 - 8)) * 64);
					}
					if (enemies.getSurface(i, j) != -1){
						graphics.DrawSurface(enemies.getSurface(i, j), i * 64, (j - (16 - 8)) * 64);
					}
					if (FIREBALL == 1){
						for (int i = 0; i < 4; i++){
							graphics.DrawSurface(CONST_FIREBALL, hero.getX() * 64 + i * 64, (hero.getY() - 8) * 64);
							graphics.DrawSurface(CONST_FIREBALL, hero.getX() * 64 - i * 64, (hero.getY() - 8) * 64);
						}
					}
					graphics.DrawSurface(CONST_HEROE_SURFACE, hero.getX() * 64, (hero.getY() - 8) * 64);
				}
			}
		}
		//bottom
		else if (hero.getX() >= floor(10 / 2) && hero.getX() <= 16 - 5 && hero.getY() > 16 - floor(8 / 2)){
			for (int i = hero.getX() - floor(10 / 2); i < hero.getX() + floor(10 / 2); i++){
				for (int j = 16 - 8; j < 16; j++){
					if (secondLayer.getSurface(i, j) != 15){
						graphics.DrawSurface(secondLayer.getSurface(i, j), (i - (hero.getX() - floor(10 / 2))) * 64, (j - 8) * 64);
					}
					if (m2.getSurface(i, j) != 15){
						graphics.DrawSurface(m2.getSurface(i, j), (i - (hero.getX() - floor(10 / 2))) * 64, (j - 8) * 64);
					}
					if (enemies.getSurface(i, j) != -1){
						graphics.DrawSurface(enemies.getSurface(i, j), (i - (hero.getX() - floor(10 / 2))) * 64, (j - 8) * 64);
					}
					if (FIREBALL == 1){
						for (int i = 0; i < 4; i++){
							graphics.DrawSurface(CONST_FIREBALL, floor(10 / 2) * 64 + i * 64, (hero.getY() - 8) * 64);
							graphics.DrawSurface(CONST_FIREBALL, floor(10 / 2) * 64 - i * 64, (hero.getY() - 8) * 64);
						}
					}
					graphics.DrawSurface(CONST_HEROE_SURFACE, floor(10 / 2) * 64, (hero.getY() - 8) * 64);
				}
			}
		}
		//right
		else if (hero.getX() > 16 - floor(10 / 2) && hero.getY() >= floor(8 / 2) && hero.getY() <= 16 - 4){
			for (int i = 16 - 10; i < 16; i++){
				for (int j = hero.getY() - floor(8 / 2); j < hero.getY() + floor(8 / 2); j++){
					if (secondLayer.getSurface(i, j) != 15){
						graphics.DrawSurface(secondLayer.getSurface(i, j), (i - 6) * 64, (j - (hero.getY() - floor(8 / 2))) * 64);
					}
					if (m2.getSurface(i, j) != 15){
						graphics.DrawSurface(m2.getSurface(i, j), (i - 6) * 64, (j - (hero.getY() - floor(8 / 2))) * 64);
					}
					if (enemies.getSurface(i, j) != -1){
						graphics.DrawSurface(enemies.getSurface(i, j), (i - 6) * 64, (j - (hero.getY() - floor(8 / 2))) * 64);
					}
					if (FIREBALL == 1){
						for (int i = 0; i < 4; i++){
							graphics.DrawSurface(CONST_FIREBALL, (hero.getX() - 6) * 64 + i * 64, floor(8 / 2) * 64);
							graphics.DrawSurface(CONST_FIREBALL, (hero.getX() - 6) * 64 - i * 64, floor(8 / 2) * 64);
						}
					}
					graphics.DrawSurface(CONST_HEROE_SURFACE, (hero.getX() - 6) * 64, floor(8 / 2) * 64);
				}
			}
		}
		//bottom right
		else if (hero.getY() > 16 - floor(8 / 2) && hero.getX() > 16 - floor(10 / 2)){
			for (int i = 16 - 10; i < 16; i++){
				for (int j = 16 - 8; j < 16; j++){
					if (secondLayer.getSurface(i, j) != 15){
						graphics.DrawSurface(secondLayer.getSurface(i, j), (i - (16 - 10)) * 64, (j - (16 - 8)) * 64);
					}
					if (m2.getSurface(i, j) != 15){
						graphics.DrawSurface(m2.getSurface(i, j), (i - (16 - 10)) * 64, (j - (16 - 8)) * 64);
					}
					if (enemies.getSurface(i, j) != -1){
						graphics.DrawSurface(enemies.getSurface(i, j), (i - (16 - 10)) * 64, (j - (16 - 8)) * 64);
					}
					if (FIREBALL == 1){
						for (int i = 0; i < 4; i++){
							graphics.DrawSurface(CONST_FIREBALL, (hero.getX() - 6) * 64 + i * 64, (hero.getY() - 8) * 64);
							graphics.DrawSurface(CONST_FIREBALL, (hero.getX() - 6) * 64 - i * 64, (hero.getY() - 8) * 64);
						}
					}
					graphics.DrawSurface(CONST_HEROE_SURFACE, (hero.getX() - 6) * 64, (hero.getY() - 8) * 64);
				}
			}
		}
		//center
		else{
			for (int i = hero.getX() - floor(10 / 2); i < hero.getX() + floor(10 / 2); i++){
				for (int j = hero.getY() - floor(8 / 2); j < hero.getY() + floor(8 / 2); j++){
					if (secondLayer.getSurface(i, j) != 15){
						graphics.DrawSurface(secondLayer.getSurface(i, j), (i - (hero.getX() - floor(10 / 2))) * 64, (j - (hero.getY() - floor(8 / 2))) * 64);
					}
					if (m2.getSurface(i, j) != 15){
						graphics.DrawSurface(m2.getSurface(i, j), (i - (hero.getX() - floor(10 / 2))) * 64, (j - (hero.getY() - floor(8 / 2))) * 64);
					}
					if (enemies.getSurface(i, j) != -1){
						graphics.DrawSurface(enemies.getSurface(i, j), (i - (hero.getX() - floor(10 / 2))) * 64, (j - (hero.getY() - floor(8 / 2))) * 64);
					}
					if (FIREBALL == 1){
						for (int i = 0; i < 4; i++){
							graphics.DrawSurface(CONST_FIREBALL, floor(10 / 2) * 64 + i * 64, floor(8 / 2) * 64);
							graphics.DrawSurface(CONST_FIREBALL, floor(10 / 2) * 64 - i * 64, floor(8 / 2) * 64);
						}
					}
					graphics.DrawSurface(CONST_HEROE_SURFACE, floor(10 / 2) * 64, floor(8 / 2) * 64);
				}
			}
		}
		
		if (hero.getX() == fireball.getX() && hero.getY() == fireball.getY()){
			m2.EliminateFireball();
			hero.pickFireball();
		}
		//Draw the bar interface
		graphics.DrawSurface(CONST_BAR, 0 * 64, 7 * 64);
		//Draw the health bar of the hero, drawing the sprites relative to our health
		for (int i = 0; i <hero.getHealth()*1.75; i=i+1.75){
			graphics.DrawSurface(CONST_LIFE, 5 * 64 + 27+i, 7 * 64 + 9);
		}
		//If we had the sword, draw it
		if (hero.getSword() == 1){
			graphics.DrawSurface(14, 0 * 64, 7 * 64);
		}
		//If we had the fireball, draw it
		if (hero.getFireball() == 1){
			graphics.DrawSurface(CONST_FIREBALL, 3 * 64, 7 * 64);
		}
	}
	//Update the entire window.
	graphics.UpdateWindow();
}



/**
* It executes the command associated to the key pressed
*/
void GameEngine::ProcessKeyPressed(int keyType) {
	//for controlling the time logic of the game
	START = clock();
	DIFF = (START - TIMER) / (double)CLOCKS_PER_SEC;

	//If it passes 0.75seconds since the last key pressed, enter the loop
	if (DIFF > 0.75){
		//Actualize the timer
		TIMER = START;
		if (keyType == SDLK_UP) {		//Up key
			//Moves up the hero
			hero.MoveUp();
			//Check for the attack to the enemies keeping in mind the sword item, and if it so, moves to the previous position
			if (hero.getX() == enemy1.getX() && hero.getY() == enemy1.getY()){
				if (hero.getSword() == 1){
					enemy1.lossHealth(hero.getAttack() + sword.getAttack());
				}
				else enemy1.lossHealth(5);
				hero.MoveDown();
			}
			if (hero.getX() == enemy2.getX() && hero.getY() == enemy2.getY()){
				if (hero.getSword() == 1){
					enemy2.lossHealth(hero.getAttack() + sword.getAttack());
				}
				else enemy2.lossHealth(5);
				hero.MoveDown();
			}
			if (hero.getX() == boss.getX() && hero.getY() == boss.getY()){
				if (hero.getSword() == 1){
					boss.lossHealth(hero.getAttack() + sword.getAttack());
				}
				else boss.lossHealth(5);
				hero.MoveDown();
			}
		}
		else if (keyType == SDLK_DOWN) {//Down key
			//Moves down the hero
			hero.MoveDown();
			//Check for the attack to the enemies keeping in mind the sword item, and if it so, moves to the previous position
			if (hero.getX() == enemy1.getX() && hero.getY() == enemy1.getY()){
				if (hero.getSword() == 1){
					enemy1.lossHealth(hero.getAttack() + sword.getAttack());
				}
				else enemy1.lossHealth(hero.getAttack());
				hero.MoveUp();
			}
			if (hero.getX() == enemy2.getX() && hero.getY() == enemy2.getY()){
				if (hero.getSword() == 1){
					enemy2.lossHealth(hero.getAttack() + sword.getAttack());
				}
				else enemy2.lossHealth(hero.getAttack());
				hero.MoveUp();
			}
			if (hero.getX() == boss.getX() && hero.getY() == boss.getY()){
				if (hero.getSword() == 1){
					boss.lossHealth(hero.getAttack() + sword.getAttack());
				}
				else boss.lossHealth(5);
				hero.MoveUp();
			}
		}
		else if (keyType == SDLK_LEFT) {//Left key
			//Moves left the hero
			hero.MoveLeft();
			//Check for the attack to the enemies keeping in mind the sword item, and if it so, moves to the previous position
			if (hero.getX() == enemy1.getX() && hero.getY() == enemy1.getY()){
				if (hero.getSword() == 1){
					enemy1.lossHealth(hero.getAttack() + sword.getAttack());
				}
				else enemy1.lossHealth(hero.getAttack());
				hero.MoveRight();
			}
			if (hero.getX() == enemy2.getX() && hero.getY() == enemy2.getY()){
				if (hero.getSword() == 1){
					enemy2.lossHealth(hero.getAttack() + sword.getAttack());
				}
				else enemy2.lossHealth(hero.getAttack());
				hero.MoveRight();
			}
			if (hero.getX() == boss.getX() && hero.getY() == boss.getY()){
				if (hero.getSword() == 1){
					boss.lossHealth(hero.getAttack() + sword.getAttack());
				}
				else boss.lossHealth(5);
				hero.MoveRight();
			}
		}
		else if (keyType == SDLK_RIGHT){//Right key
			//Moves right the hero
			hero.MoveRight();
			//Check for the attack to the enemies keeping in mind the sword item, and if it so, moves to the previous position
			if (hero.getX() == enemy1.getX() && hero.getY() == enemy1.getY()){
				if (hero.getSword() == 1){
					enemy1.lossHealth(hero.getAttack() + sword.getAttack());
				}
				else enemy1.lossHealth(hero.getAttack());
				hero.MoveLeft();
			}
			if (hero.getX() == enemy2.getX() && hero.getY() == enemy2.getY()){
				if (hero.getSword() == 1){
					enemy2.lossHealth(hero.getAttack() + sword.getAttack());
				}
				else enemy2.lossHealth(hero.getAttack());
				hero.MoveLeft();
			}
			if (hero.getX() == boss.getX() && hero.getY() == boss.getY()){
				if (hero.getSword() == 1){
					boss.lossHealth(hero.getAttack() + sword.getAttack());
				}
				else boss.lossHealth(5);
				hero.MoveLeft();
			}
		}
		else if (keyType == SDLK_SPACE){//Spacebar key
			//If the hero has the fireball, can use it
			if (hero.getFireball() == 1){
				//Actualizes it for the drawing loop
				FIREBALL = 1;
				//Check for the attack to the enemies keeping in mind the sword item, and if it so, moves to the previous position
				if ((hero.getX() + 4) > enemy1.getX() && (hero.getX() - 4 < enemy1.getX())){
					enemy1.lossHealth(fireball.getAttack());
				}
				if ((hero.getX() + 4) > enemy2.getX() && (hero.getX() - 4 < enemy2.getX())){
					enemy2.lossHealth(fireball.getAttack());
				}
				if ((hero.getX() + 4) > boss.getX() && (hero.getX() - 4 < boss.getX())){
					boss.lossHealth(fireball.getAttack());
				}
			}
		}
	}
	//For drawing the ranking on the console command
	if (keyType == SDLK_TAB){//Tabulate key
		ranking.DrawRanking();
	}
	
}

/**
Game loop. Draw world based on the new events that player (or system) generates
*/
void GameEngine::Run() {
	int eventType;
	int keyType;
	
	//Variables for the position of the mouse
	int x, y;
	
	//Timers variables for enemy movement
	double diff;
	timer = clock();

	//Variable that controls the attack of the boss
	int attacked = -1;
	//Variables that controls the states of the boss
	int state=3;
	//Game loop
	while (1) 	{
		//Event handling
		if (graphics.AnyEvent())	{
			//Get the event type (mouse, key, etc.) 
			eventType = graphics.GetEventType();
			if (eventType == SDL_QUIT)	{				//The quit event was generated by player when he pressed the escape key
				menu=true;										//Open the game menu
			}
			if (eventType == SDL_MOUSEBUTTONDOWN) {		//Mouse button was pressed
				//If the menu is open
				if (menu){
					//Store the position of the mouse
					SDL_GetMouseState(&x, &y);
					//Check which button was pressed
					if (x > 0 && x < 640 && y>0 && y < 2*64){
						//Start the game
						menu = false;
					}
					//To save the map
					if (x > 0 && x < 640 && y>2*64 && y < 4*64){
						m1.SaveMap(hero.getX(), hero.getY(), hero.getSword(), hero.getFireball(), enemy1.getX(), enemy1.getY(),enemy2.getX(), enemy2.getY(),boss.getX(), boss.getY(),hero.getHealth(), 1);
						m2.SaveMap(0,0,0,0,0,0,0,0,0,0,0,4);
						secondLayer.SaveMap(0, 0, 0, 0, 0,0, 0,0,0,0,0, 2);
						enemies.SaveMap(0,0,0,0,0,0,3);
					}
					//To load the map
					if (x > 0 && x < 640 && y>64*4 && y < 64*6){
						m1.LoadMap( 1);
						m2.LoadMap(4);
						secondLayer.LoadMap(2);
						enemies.LoadMapEnemies();
						//Set the load data
						hero.setX(m1.HeroPosX());
						hero.setY(m1.HeroPosY());
						hero.setFireball(m1.Fireball());
						hero.setSword(m1.Sword());
						enemy1.setX(m1.EnemyX());
						enemy1.setY(m1.EnemyY());
						hero.setHealth(m1.HeroHealth());
						boss.setX(m1.getXBoss());
						boss.setY(m1.getYBoss());
					}
					//To exit the game
					if (x > 0 && x < 640 && y>64*6 && y < 64*8){
						//exit button
						break;
					}
				}
				//To end the game
				if (win){			//The player win the game
					//Create the ranking 
					file.CreateRanking("ranking");
					break;
				}
				else if (GameOver){//The player lose the game
					//Create the ranking 
					file.CreateRanking("ranking");
					break;
				}
				
			}
			if (eventType == SDL_KEYDOWN)	{			//A key was pressed				
				keyType = graphics.GetKeyType();
				if (keyType == SDLK_ESCAPE)	{
					graphics.PushExitGameEvent();			//If ESC was pressed, quit the program			
				}
				else  {
					ProcessKeyPressed(keyType);				//Some key was pressed (different from escape)
				}
			}			
		}
		//Execute the pending actions
		//If the position of the hero is the same of the sword, picks it.
		if (hero.getX() == sword.getX() && hero.getY() == sword.getY()){
			m2.EliminateSword();
			hero.pickSword();
		}
		//Check if there are enemies and if not win the game and actualize the score
		if (enemy1.getHealth() <= 0 && enemy2.getHealth() <=0 && boss.getHealth()<=0){
			win = true;
			ranking.declarescore(score, hero.getName());
		}
		//Move the enemy each second and check for his attack
		start = clock();
		diff = (start - timer) / (double)CLOCKS_PER_SEC;
		//Check for drawing the fireball
		if (diff > 0.75 && FIREBALL == 1){
			FIREBALL = 0;
		}
		//Check for the time movement if is alive
		if (diff>1 && enemy1.getHealth()>0){
			//Changes the position of the enemy class and the enemy map
			enemies.change(enemy1.getX(), enemy1.getY(), -1);
			enemy1.Move();
			enemies.change(enemy1.getX(), enemy1.getY(), 21);
			//Check if collides with the hero, which means the enemy is attacking and return it to its position
			if (hero.getX() == enemy1.getX() && hero.getY() == enemy1.getY()){
				enemies.change(enemy1.getX(), enemy1.getY(), -1);
				enemy1.Move();
				enemy1.Move();
				enemy1.Move();
				enemies.change(enemy1.getX(), enemy1.getY(), 21);
				hero.lossHealth(enemy1.getAttack());
			}
			//Actualize the timer movement
			timer = start;
		}
		if (diff>1 && enemy2.getHealth()>0){
			//Changes the position of the enemy class and the enemy map
			enemies.change(enemy2.getX(), enemy2.getY(), -1);
			enemy2.Move();
			enemies.change(enemy2.getX(), enemy2.getY(), 21);
			//Check if collides with the hero, which means the enemy is attacking and return it to its position
			if (hero.getX() == enemy2.getX() && hero.getY() == enemy2.getY()){
				enemies.change(enemy2.getX(), enemy2.getY(), -1);
				enemy2.Move();
				enemy2.Move();
				enemy2.Move();
				enemies.change(enemy2.getX(), enemy2.getY(), 21);
				hero.lossHealth(enemy1.getAttack());
			}
			//Actualize the timer movement
			timer = start;
		}
		//IA for the boss
		//Conditions
		//Is not attacking
		attacked = 0;
		//See condition
		if (hero.getX()>(boss.getX() - 4) && (hero.getY() < (boss.getY() + 4)) && hero.getX() < (boss.getX() + 4) && (hero.getY() > (boss.getY() - 4))){
			state = 1;
		}
		//Dying condition
		if (boss.getHealth()<10){
			state = 0;
		}
		//Recover and see condition
		if (hero.getX()>(boss.getX() - 4) && (hero.getY() < (boss.getY() + 4)) && hero.getX() < (boss.getX() + 4) && (hero.getY() > (boss.getY() - 4)) && (boss.getHealth() > 10)){
			state = 2;
		}
		//Recover and not see condition
		if (boss.getHealth() > 10 && !(hero.getX()>(boss.getX() - 4)) && !((hero.getY() < (boss.getY() + 4))) && !(hero.getX() < (boss.getX() + 4)) && !(hero.getY() > (boss.getY() - 4))){
			state = 3;
		}
			//Run->attack
			//The boss moves towards the hero until it collides, removing heroe's health and returning the boss to its position
			if (statemachine.getNode(0, state) == 2){
				if (boss.getX() < hero.getX() && diff>1 ){
					enemies.change(boss.getX(), boss.getY(), -1);
					boss.setX(boss.getX() + 1);
					enemies.change(boss.getX(), boss.getY(), 26);
					attacked = 1;
					if (hero.getX() == boss.getX() && hero.getY() == boss.getY()){
						enemies.change(boss.getX(), boss.getY(), -1);
						boss.setX(boss.getX() - 1);
						enemies.change(boss.getX(), boss.getY(), 26);
						hero.lossHealth(boss.getAttack());
					}
				}
				if (boss.getX() > hero.getX() && diff>1 ){
					enemies.change(boss.getX(), boss.getY(), -1);
					boss.setX(boss.getX() - 1);
					enemies.change(boss.getX(), boss.getY(), 26);
					attacked = 1;
					if (hero.getX() == boss.getX() && hero.getY() == boss.getY()){
						enemies.change(boss.getX(), boss.getY(), -1);
						boss.setX(boss.getX() + 1);
						enemies.change(boss.getX(), boss.getY(), 26);
						hero.lossHealth(boss.getAttack());
					}
				}
				if (boss.getY() < hero.getY() && diff>1 && attacked == 0){
					enemies.change(boss.getX(), boss.getY(), -1);
					boss.setY(boss.getY() + 1);
					enemies.change(boss.getX(), boss.getY(), 26);
					if (hero.getX() == boss.getX() && hero.getY() == boss.getY()){
						enemies.change(boss.getX(), boss.getY(), -1);
						boss.setY(boss.getY() - 1);
						enemies.change(boss.getX(), boss.getY(), 26);
						hero.lossHealth(boss.getAttack());
					}

				}
				if (boss.getY() > hero.getY() && diff>1 && attacked == 0){
					enemies.change(boss.getX(), boss.getY(), -1);
					boss.setY(boss.getY() - 1);
					enemies.change(boss.getX(), boss.getY(), 26);
					if (hero.getX() == boss.getX() && hero.getY() == boss.getY()){
						enemies.change(boss.getX(), boss.getY(), -1);
						boss.setY(boss.getY() + 1);
						enemies.change(boss.getX(), boss.getY(), 26);
						hero.lossHealth(boss.getAttack());
					}
				}
			}
			//steady->attack
			//The boss moves towards the hero until it collides, removing heroe's health and returning the boss to its position
			else if (statemachine.getNode(1, state) == 2 || statemachine.getNode(1,state)==2){
				if (boss.getX() < hero.getX() && diff>1 ){
					enemies.change(boss.getX(), boss.getY(), -1);
					boss.setX(boss.getX()+1);
					enemies.change(boss.getX(), boss.getY(), 26);
					attacked = 1;
				}
				if (boss.getX() > hero.getX() && diff>1 ){
					enemies.change(boss.getX(), boss.getY(), -1);
					boss.setX(boss.getX() - 1);
					enemies.change(boss.getX(), boss.getY(), 26);
					attacked = 1;
				}
				if (boss.getY() < hero.getY() && diff>1 && attacked == 0){
					enemies.change(boss.getX(), boss.getY(), -1);
					boss.setY(boss.getY() + 1);
					enemies.change(boss.getX(), boss.getY(), 26);
				}
				if (boss.getY() > hero.getY() && diff>1 && attacked == 0){
					enemies.change(boss.getX(), boss.getY(), -1);
					boss.setY(boss.getY() - 1);
					enemies.change(boss.getX(), boss.getY(), 26);
				}
			}
			//attack->run
			//The boss runs from the player unitl touches a border
			if (statemachine.getNode(2, state) == 0){
				if (boss.getX() < hero.getX() && diff>1){
					if ((boss.getX() > 0 && boss.getX() < 15) &&( boss.getY() > 0 && boss.getY() < 15)){
						enemies.change(boss.getX(), boss.getY(), -1);
						boss.setX(boss.getX() - 1);
						enemies.change(boss.getX(), boss.getY(), 26);
					}
				}
				if (boss.getX() > hero.getX() && diff>1){
					if ((boss.getX() > 0 && boss.getX() < 15) && (boss.getY() > 0 && boss.getY() < 15)){
						enemies.change(boss.getX(), boss.getY(), -1);
						boss.setX(boss.getX() + 1);
						enemies.change(boss.getX(), boss.getY(), 26);
					}
				}
				if (boss.getY() < hero.getY() && diff>1){
					if ((boss.getX() > 0 && boss.getX() < 15) && (boss.getY() > 0 && boss.getY() < 15)){
						enemies.change(boss.getX(), boss.getY(), -1);
						boss.setY(boss.getY() - 1);
						enemies.change(boss.getX(), boss.getY(), 26);
					}
				}
				if (boss.getY() > hero.getY() && diff>1){
					if ((boss.getX() > 0 && boss.getX() < 15) && (boss.getY() > 0 && boss.getY() < 15)){
						enemies.change(boss.getX(), boss.getY(), -1);
						boss.setY(boss.getY() + 1);
						enemies.change(boss.getX(), boss.getY(), 26);
					}
				}
			}
			//run->steady
			if (statemachine.getNode(0, state) == 1){
				//stay in place
			}

		//Check if the enemy dies and actualize score
		if (enemy1.getHealth()<=0){
			enemies.change(enemy1.getX(), enemy1.getY(),-1);
			enemy1.setX(NULL);
			enemy1.setY(NULL);
			score = score + 20;
		}
		if (enemy2.getHealth() <= 0){
			enemies.change(enemy2.getX(), enemy2.getY(), -1);
			enemy2.setX(NULL);
			enemy2.setY(NULL);
			score = score + 20;
		}
		if (boss.getHealth() <= 0){
			enemies.change(boss.getX(), boss.getY(), -1);
			boss.setX(NULL);
			boss.setY(NULL);
			score = score + 100;
		}
		//Check if the hero dies
		if (hero.getHealth() <= 0){
			GameOver = true;
			ranking.declarescore(score, hero.getName());
		}
		//Draw the updated world
		DrawWorld();
	}
}


// ============================================================================
// Main program
// ============================================================================
int main(int argc, char* argv[]) {
	try {
		GameEngine game("Game Adventure v.1.0", 64 * 10, 64 * 8);	//A map of 10 by 8 cells, each cell are 64 pixels
		game.Run();
	}
	catch (exception & e) {
		std::cout << e.what() << endl;
	}
	return 0;
}
