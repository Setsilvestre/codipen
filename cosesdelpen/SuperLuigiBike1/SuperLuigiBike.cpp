#include "SuperLuigiBike.h"	

SuperLuigiBike::SuperLuigiBike(int MAX_ROW, int MAX_COLUMN) : Mapa(MAX_ROW, MAX_COLUMN), LinkedList(){
	this->MAX_ROW = MAX_ROW;
	this->MAX_COLUMN = MAX_COLUMN;
	win = false;
}

SuperLuigiBike::~SuperLuigiBike(){

}

void SuperLuigiBike::run(){
	srand(NULL);
	initPlayers();
	initMap();
	startRace();
}

void SuperLuigiBike::initPlayers(){
	try{
		cout << "How many players will be?" << endl;
		cin >> players;
		if (cin.fail() || players>MAX_ROW){
			throw 1;
		}
	}
	catch (int e){
		cout << "Unable to create the game do to number of players, please check that is lower than the rows and that is it a NUMBER" << endl;
	}
	int temporal;
	
	for (int i = 0; i < players; i++){
		temporal=abs(rand() % 3);
		if (temporal == 0){
			polymorphiscDrivers = new Bike(temporal,players-1-i);
		}
		else if (temporal == 1){
			polymorphiscDrivers = new Car(temporal, players-1-i);
		}
		else if (temporal == 2){
			polymorphiscDrivers = new Tank(temporal,players-1-i);
		}
		LinkedList.addCharacter(polymorphiscDrivers);
	}
	cout << "0 is a Bike player" << endl;
	cout << "1 is a Car player" << endl;
	cout << "2 is a Tank player" << endl;
}

void SuperLuigiBike::initMap(){
	for (int i = 0; i < MAX_ROW; i++){
		for (int j = 0; j < MAX_COLUMN; j++){
			Mapa.Set(i, j, -1);
		}
	}
	int random;
	for (int i = 0; i < MAX_ROW; i++){
		for (int j = 0; j < MAX_COLUMN; j++){
			random = rand() % (MAX_ROW * MAX_COLUMN);
			if (random >=0 && random<(MAX_ROW * MAX_COLUMN/10)){
				Mapa.Set(i, j, -2);
			}
		}
	}
	for (int i = 0; i < players; i++){
		Mapa.Set(i, 0, (LinkedList.getCharacter(i))->getDriver());
	}
}

void SuperLuigiBike::startRace(){
	cout << Mapa << endl;
	system("pause");
	while (!win){
		for (int j = 0; j < LinkedList.getSize(); j++){
			LinkedList.getCharacter(j)->move(Mapa.Get(LinkedList.getCharacter(j)->getPosX(), LinkedList.getCharacter(j)->getPosY() + 1));
		}
		for (int j = 0; j < LinkedList.getSize(); j++){
			if (Mapa.Get(LinkedList.getCharacter(j)->getPosX(), LinkedList.getCharacter(j)->getPosY()) == -2){
				if (LinkedList.getCharacter(j)->getDriver() != 2){
					cout << "Player ";
					cout << LinkedList.getCharacter(j)->getName();
					cout << " died" << endl;
					LinkedList.removeCharacterfromPosition(j);
					cout << LinkedList.getSize() << endl;
				}
				else Mapa.Set(LinkedList.getCharacter(j)->getPosX(), LinkedList.getCharacter(j)->getPosY(), LinkedList.getCharacter(j)->getDriver());
			}
			else Mapa.Set(LinkedList.getCharacter(j)->getPosX(), LinkedList.getCharacter(j)->getPosY(), LinkedList.getCharacter(j)->getDriver());
		}
		cout << Mapa << endl;
		for (int j = 0; j < LinkedList.getSize(); j++){
			if (LinkedList.getCharacter(j)->getPosY() == MAX_COLUMN - 1 || LinkedList.getCharacter(j)->getPosY() == MAX_COLUMN){
				win = true;
				cout << "The player  ";
				cout << LinkedList.getCharacter(j)->getName();
				cout << " win the game" << endl;
				break;
			}
		}
		system("pause");
	}
}

int main(){
	int rows, columns;
	try{
		cout << "How many rows do you want to have the game?" << endl;
		cin >> rows;
		if (cin.fail()){
			throw 1;
		}
		cout << "How many columns do you want to have the game?" << endl;
		cin >> columns;
		if (cin.fail()){
			throw 1;
		}
		SuperLuigiBike game(rows, columns);
		game.run();
	}
	catch (int e){
		cout << "Unable to create the game, please check that you put a number" << endl;
	}
	
}

