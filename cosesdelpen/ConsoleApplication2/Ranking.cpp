#include "Ranking.h"
//Ghost constructor
Ranking::Ranking(){
	for (int i = 0; i < 10; i++){
		players[i] = "Player " + to_string(i);
		score[i] = rand() %140;
	}
}
//Destructor
Ranking::~Ranking(){

}
//Print the ranking
void Ranking::DrawRanking(){
	for (int i = 0; i < 10; i++){
		cout << players[i] << ": ";
		cout << score[i] << endl;
	}
}
//Update the ranking
void Ranking::declareName(string name){
	for (int i = 0; i < 10; i++){
		if (players[i] =="ghost"){
			players[i] = name;
		}
	}
}
//Update the score
void Ranking::declarescore(int x, string name){
	for (int i = 0; i < 10; i++){
		if (players[i] == name){
			score[i] = x;
		}
	}
}
//Create the file for the ranking
void Ranking::CreateRanking(char filename[100]){
	fstream myOutputFile;
	char Score[10];
	//Create the file with a random population
	myOutputFile.open(filename, ios::out | ios::trunc | ios::binary);

	if (myOutputFile.is_open()) {
		for (int i = 0; i < 10; i++) {
			int sizePerson = sizeof(players[i]);
			int sizeScore = sizeof(score[i]);
			const char* player = players[i].c_str();
			myOutputFile.write(player, sizePerson);
			myOutputFile.write(": ", 2);
			sprintf(Score,"%d", score[i]);
			char*SCORE = Score;
			myOutputFile.write( SCORE, sizeScore);
		}
		myOutputFile.close();
	}
	else {
		throw exception("System was not able to open the file");
	}
}
	