#pragma once


//Third-party libraries
#include <GL/glew.h>			//The OpenGL Extension Wrangler
#include <glm/glm.hpp>			//OpenGL Mathematics 
#include <iostream>
#include "Window.h"
#include "GLSLProgram.h"
#include "FPSLimiter.h"


//Game has three possible states: INIT (Preparing environment), PLAY (Playing) or EXIT (Exit from the game)
enum class GameState{INIT, PLAY, EXIT};

//This class manages the game execution
class Game {
	public:						
		Game(std::string windowTitle, int screenWidth, int screenHeight, bool enableLimiterFPS, int maxFPS, bool printFPS);	//Constructor
		~Game();					//Destructor
		void run();					//Game execution

	private:
			//Attributes	
		std::string _windowTitle;	//Window Title
		int _screenWidth;			//Screen width in pixels				
		int _screenHeight;			//Screen height in pixels				
		GameState _gameState;		//It describes the game state		
		GLuint gVAO = 0;			//Vertex Array Object
		GLuint gVBO = 0;			//Vertex Buffer Object
		Window _window;				//Manage the OpenGL context
		GLSLProgram _colorProgram;	//Manage the shaders
		FPSLimiter _fpsLimiter;		//Manage the synchronization between frame rate and refresh rate
	
			//Internal methods
		void initSystems();
		void loadShaders();
		void loadTriangle();
		void gameLoop();
		void processInput();
		void drawGame();	
		
};

