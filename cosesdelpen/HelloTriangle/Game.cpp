#include "Game.h"



/**
* Constructor
* Note: It uses an initialization list to set the parameters
* @param windowTitle is the window title
* @param screenWidth is the window width
* @param screenHeight is the window height
*/
Game::Game(std::string windowTitle, int screenWidth, int screenHeight, int maxFPS) :
	_windowTitle(windowTitle), _screenWidth(screenWidth), _screenHeight(screenHeight),_gameState(GameState::INIT), _maxFPS(maxFPS) {
}

/**
* Destructor
*/
Game::~Game()
{
}

/*
* Game execution
*/
void Game::run() {
		//System initializations
	initSystems();
		//Start the game if all the elements are ready
	gameLoop();
}

/*
* Initializes all the game engine components
*/
void Game::initSystems() {
		//Create an Opengl window using SDL
	_window.create(_windowTitle, _screenWidth, _screenHeight, 0);		
		//Compile and Link shader
	loadShaders();
		//Load sprites
	loadTriangle();		
}

/*
* Compiles, sets the variables between C++ and the Shader program and links the shader program
*/
void Game::loadShaders() {
		//Compile the shaders
	_colorProgram.addShader(GL_VERTEX_SHADER, "./resources/shaders/vertex-shader.txt");
	_colorProgram.addShader(GL_FRAGMENT_SHADER, "./resources/shaders/fragment-shader.txt");
	_colorProgram.compileShaders();
		//Attributes must be added before linking the code
	_colorProgram.addAttribute("vert");
		//Link the compiled shaders
	_colorProgram.linkShaders();
}

/*
* Loads all the element that has to be displayed on the screen
*/
void Game::loadTriangle() {
	// make and bind the VAO
	glGenVertexArrays(1, &gVAO);
	glBindVertexArray(gVAO);

	// make and bind the VBO
	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);

	// Put the three triangle vertices into the VBO
	GLfloat vertexData[] = {
		//  X     Y     Z
		0.0f, 0.4f, 0.0f,
		-0.4f, -0.4f, 0.0f,
		0.4f, -0.4f, 0.0f,
		0.5f, 0.8f, 0.3f,
		-0.2f, -0.9f, 0.1f,
		0.7f, -0.4f, 0.2f,
		-0.9f, 0.4f, 0.4f,
		-0.8f, -0.1f, -0.5f,
		-0.3f, -0.9f, 0.4f,
	};
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	
	// connect the xyz to the "vert" attribute of the vertex shader
	glEnableVertexAttribArray(_colorProgram.getAttribLocation("vert"));
	/*
	The first argument is the shader variable that the data should be sent to
	The second argument, 3, says that each vertex has three numbers
	The third argument, GL_FLOAT, says that the three numbers are GLfloats
	The fourth argument, GL_FALSE, says that we do not want the floats to be "normalized." If they were normalized, they would be restricted to having a minimum of zero, and a maximum of one. We don't want that restriction on our points, which is why this argument is false.
	The fifth argument, 0, would be used if there was a gap in between each point. Setting this argument to zero means that there are no gaps in our data.
	The sixth argument, NULL, would be used if our data was not at the start of the buffer. Setting this argument to NULL means that our data starts right at the first byte of the VBO.	
	*/
	glVertexAttribPointer(_colorProgram.getAttribLocation("vert"), 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// unbind the VBO and VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


/*
* Game execution: Gets input events, processes game logic and draws sprites on the screen
*/
void Game::gameLoop() {	
	double initTime, finalTime = 0.0, average =0.0;
	double averageFPS[10] = { 0 };
	int i=0;
	fstream myfile;
	_gameState = GameState::PLAY;
	while (_gameState != GameState::EXIT) {
		//Process the input information (keyboard and mouse)
		processInput();
		initTime = clock();
		//Draw the objects on the screen
		drawGame();
		//Compute the last frame and the average of the last 10 frames and store it in a .txt file
		myfile.open("ComputeFrames.txt", ios::app);
		if (myfile.is_open()){
			myfile << "Time needed to compute a frame: ";
			myfile << (initTime - finalTime) / (double)CLOCKS_PER_SEC;
			myfile << "\n";
			averageFPS[i] = (initTime - finalTime) / (double)CLOCKS_PER_SEC;
			i++;
			finalTime = initTime;
			if (i == 10){
				i = 0;
				for (int j = 0; j < 10; j++){
					average = averageFPS[j] + average;
				}
				myfile << "The averrage time of the last 10 frames is: ";
				myfile << average / 10;
				average = 0;
				myfile << "\n";	
			}
			myfile.close();
		}
	}
}

/*
* Processes input with SDL
*/
void Game::processInput() {
	//Review https://wiki.libsdl.org/SDL_Event to see the different kind of events
	//Moreover, table show the property affected for each event type
	SDL_Event evnt;
	//Will keep looping until there are no more events to process
	while (SDL_PollEvent(&evnt)) {
		switch (evnt.type) {
		case SDL_QUIT:
			_gameState = GameState::EXIT;
			break;
		default:
			break;
		}
	}
}

/**
* Draw the sprites on the screen
*/
void Game::drawGame() {
		//Set the base depth to 1.0
	glClearDepth(1.0);

		//Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Bind the GLSL program. Only one code GLSL can be used at the same time
	_colorProgram.use();

		// bind the VAO (the triangle)
	glBindVertexArray(gVAO);

		// draw the VAO
	glDrawArrays(GL_TRIANGLES, 0, 9);

		// unbind the VAO
	glBindVertexArray(0);

		//Unbind the program
	_colorProgram.unuse();

		//Swap the display buffers (displays what was just drawn)
	_window.swapBuffer();
	
}

