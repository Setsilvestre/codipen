#include "MapEnemies.h"
MapEnemies::MapEnemies(){

}

MapEnemies::~MapEnemies(){
	if (data != 0) {
		for (int i = 0; i < cols; i++) {
			if (data[i] != 0)
				delete data[i];
		}
		delete[] data;
	}
}

//Create the map, the first parameter is the number of columns, and the second parameter is the number of rows
void MapEnemies::CreateMap(int x, int y){
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
	for (int i = 0; i < x; i++){
		for (int j = 0; j < y; j++){
			data[i][j] = 0;
		}
	}

}

//return the number of the surface stored on the position x,y
int MapEnemies::getSurface(int x, int y) {
	return data[x][y];
}

//Use the function create map and assign to each field a number for the surface
void MapEnemies::LoadMap() {
	CreateMap(16, 16);
	for (int i = 0; i < 16; i++){
		for (int j = 0; j < 16; j++){
			data[i][j] = -1;
		}
	}
	//21 is for an enemy
	data[13][5] = 21;
	data[5][4] = 21;
	data[13][13] = 26;
}
//change the value of a position
void MapEnemies::change(int x, int y, int value){
	data[x][y] = value;
}

//Save the map
void MapEnemies::SaveMap(int x, int y, int sword, int fireball, int xenemy, int yenemy, int map){
	if (map == 1){
		ofstream file("map.txt");
	}
	else if (map == 2){
		ofstream file("transition.txt");
	}
	else if (map == 3){
		ofstream file("enemy.txt");
		if (file.is_open()){
			if (map == 1){
				file << x << " " << y << " " << sword << " " << fireball << " " << xenemy << " " << yenemy;
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
	else ofstream file("objects.txt");
	

	cout << "Game Saved!" << endl;
}


////Load the map @param bool first is to know if is the first map to load the variables not related to the maps
void MapEnemies::LoadMapEnemies(){
	
		ifstream filein("enemy.txt", ios::in);
	
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

