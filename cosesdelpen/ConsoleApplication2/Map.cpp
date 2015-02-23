#include "Map.h"

/**
* Constructor
*/
Map::Map(){

}

//Destructor
Map::~Map(){
	if (data != 0) {
		for (int i = 0; i < cols; i++) {
			if (data[i] != 0)
				delete data[i];
		}
		delete[] data;
	}
}

/**
* Overload constructor. Creates the x*y matrix
* @param x is the rows value
* @param y is the cols value
*/
Map::Map(int x, int y){
	//throw exception
	if ((x <= 0) || (y <= 0)) {
		throw exception("Matrix with negative or null dimensions doesn't exist");
	}
	//Actualize the rows and cols value
	this->rows = x;
	this->cols = y;
	data = 0;
	//Allocate memory
	data = new int*[x];
	if (data == 0) {
		throw exception("System was not able to create the matrix");
	}
	for (int i = 0; i < x; i++) {
		data[i] = new int[y];
		if (data[i] == 0) {
			throw exception("System was not able to create the matrix");
		}
	}
	//Initizalize to 0
	for (int i = 0; i < x; i++){
		for (int j = 0; j < y; j++){
			data[i][j] = 0;
		}
	}
}
/**
* Set the data in a cell
* @param x is the row cell number
* @param y is the column cell number
* @param _data is the value to assign to that position
*/
void Map::Set(int x, int y, int _data){
	data[x][y] = _data;
}

/**
* Create the map
* @param x is the row cell number
* @param y is the column cell number
*/
void Map::CreateMap(int x, int y){
	this->cols = y;
	this->rows = x;
		if ((x <= 0) || (y <= 0)) {
			throw exception("Matrix with negative or null dimensions doesn't exist");
		}

		data = 0;
		//Allocate memory
		data = new int*[x];
		if (data == 0) {
			throw exception("System was not able to create the matrix");
		}

		for (int i = 0; i < x; i++) {
			data[i] = 0;
		}

		for (int i = 0; i < x; i++) {
			data[i] = new int[y];
			if (data[i] == 0) {
				throw exception("System was not able to create the matrix");
			}
		}
		//Initialize the data to 0
		for (int i = 0; i < x; i++){
			for (int j = 0; j < y; j++){
				data[i][j] = 0;
			}
		}
		
}

/**
* Create the map and set the info for that map, in this case the surface map
*/
void Map::LoadMap() {

	CreateMap(16, 16);
	for (int i = 0; i < 7; i++){
		for (int j = 0; j < 16; j++){
			data[i][j] = 2;
		}
	}
	for (int i = 9; i < 16; i++){
		for (int j = 0; j < 16; j++){
			data[i][j] = 10;
		}
	}
	for (int i = 7; i < 9; i++){
		for (int j = 0; j < 16; j++){
			data[i][j] = 5;
		}
	}
}
/**
* Create the map and set the info for that map, in this case the transition map
*/
void Map::LoadSecondLayer(){
	CreateMap(16, 16);
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 16; j++){
			data[i][j] = 15;
		}
	}
	for (int i = 9; i < 16; i++){
		for (int j = 0; j < 16; j++){
			data[i][j] = 15;
		}
	}
	for (int i = 8; i < 9; i++){
		for (int j = 0; j < 16; j++){
			data[i][j] = 17;
		}
	}
}

/**
* Return the number of the surface stored on the position x,y
*/
int Map::getSurface(int x, int y) {
	return data[x][y];
}

/**
* Save the map in a .txt file and store the variables of the characters
* @param _x is the X position of the hero
* @param _y is the Y position of the hero
* @param sword for know if the hero has or not the sword
* @param fireball for know if the hero has or not the fireball
* @param xenemy is the X position of the enemy1
* @param yenemy is the Y position of the enemy1
* @param xenemy2 is the X position of the enemy2
* @param yenemy2 is the Y position of the enemy2
* @param xboss is the X position of the boss
* @param yboss is the Y position of the boss
* @param health is the health of the hero
* @param map is the number of the map that will be stored
*/
void Map::SaveMap( int x, int y, int sword, int fireball, int xenemy, int yenemy,int xenemy2, int yenemy2,int xboss, int yboss, int health, int map){
	//Depending of the map it will store the values of the characters
	if (map == 1){
		ofstream file("map.txt");
		if (file.is_open()){
			if (map == 1){
				file << x << " " << y << " " << sword << " " << fireball << " " << xenemy << " " << yenemy << " " << xenemy2 << " " << yenemy2 <<" " <<xboss<< " "<< yboss<< " "<< health<< " ";
			}
			for (int i = 0; i < rows; i++){
				for (int j = 0; j < cols; j++){
					file << data[i][j] << " ";
				}
			}
			file << endl;
			file.close();
		}
		else cout << " Unable to save Map";
	}
	else if (map == 2){
		ofstream file("transition.txt", ios::out);
		if (file.is_open()){
			for (int i = 0; i < rows; i++){
				for (int j = 0; j < cols; j++){
					file << data[i][j] << " ";
				}
			}
			file << endl;
			file.close();
		}
		else cout << " Unable to save Map";
	}
	else if (map == 3){
		ofstream file("enemy.txt", ios::out);
		if (file.is_open()){
			for (int i = 0; i < rows; i++){
				for (int j = 0; j < cols; j++){
					file << data[i][j] << " ";
				}
			}
			file << endl;
			file.close();
		}
		else cout << " Unable to save Map";
	}
	else {
		ofstream file("objects.txt", ios::out);
		if (file.is_open()){
			for (int i = 0; i < rows; i++){
				for (int j = 0; j < cols; j++){
					file << data[i][j] << " ";
				}
			}
			file << endl;
			file.close();
		}
		else cout << " Unable to save Map";
	}
	cout << "Game Saved!" << endl;
}


/**
* Load the game from a .txt
* @param map is the map it will load
*/
void Map::LoadMap( int map){
	if (map == 1){
		ifstream filein("map.txt");
		if (filein.is_open()){
			if (map == 1){
				//read the characters variables in this variables
				filein >> temp1;
				filein >> temp2;
				filein >> temp3;
				filein >> temp4;
				filein >> temp5;
				filein >> temp6;
				filein >> temp7;
				filein >> temp8;
				filein >> temp10;
				filein >> temp11;
				filein >> temp9;
			}
			for (int i = 0; i < rows; i++){
				for (int j = 0; j < cols; j++){
					filein >> data[i][j];
				}
			}
			filein.close();
			cout << "Game Loaded";
		}
	}
	else if (map == 2){
		ifstream filein("transition.txt");
		if (filein.is_open()){
			for (int i = 0; i < rows; i++){
				for (int j = 0; j < cols; j++){
					filein >> data[i][j];
				}
			}
			filein.close();
			cout << "Game Loaded";
		}
	}
	else if (map == 3){
		ifstream filein("enemy.txt");
		if (filein.is_open()){
			for (int i = 0; i < rows; i++){
				for (int j = 0; j < cols; j++){
					filein >> data[i][j];
				}
			}
			filein.close();
			cout << "Game Loaded";
		}
	}
	else {
		ifstream filein("objects.txt");
		if (filein.is_open()){
			for (int i = 0; i < rows; i++){
				for (int j = 0; j < cols; j++){
					filein >> data[i][j];
				}
			}
			filein.close();
			cout << "Game Loaded";
		}
	}
	
}

/**
* Return the loaded X Position  of the hero
*/
int Map::HeroPosX(){
	return temp1;
}

/**
* Return the loaded Y Position  of the hero
*/
int Map::HeroPosY(){
	return temp2;
}

/**
* Return the loaded sword value of the hero
*/
int Map::Sword(){
	return temp3;
}

/**
* Return the loaded fireball value of the hero
*/
int Map::Fireball(){
	return temp4;
}

/**
* Return the loaded X Position  of the enemy1
*/
int Map::EnemyX(){
	return temp5;
}

/**
* Return the loaded Y Position of the enemy1
*/
int Map::EnemyY(){
	return temp6;
}

/**
* Return the loaded X Position of the enemy2
*/
int Map::EnemyX2(){
	return temp7;
}

/**
* Return the loaded Y Position of the enemy2
*/
int Map::EnemyY2(){
	return temp8;
}

/**
* Return the loaded health value of the hero
*/
int Map::HeroHealth(){
	return temp9;
}

/**
* Return the columns of the map
*/
int Map::getColumns(){
	return cols;
}

/**
* Return therows of the map
*/
int Map::getRows(){
	return rows;
}

/**
* Return the loaded X Position of the boss
*/
int Map::getXBoss(){
	return temp10;
}

/**
* Return the loaded Y Position of the boss
*/
int Map::getYBoss(){
	return temp11;
}
