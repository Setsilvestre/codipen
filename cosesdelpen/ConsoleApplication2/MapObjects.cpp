#include "MapObjects.h"

void MapObjects::CreateObjects(){
	CreateMap(16,16);
	for (int i = 0; i < 16; i++){
		for (int j = 0; j < 16; j++){
			data[i][j] = 15;
		}
	}
	data[6][9] = 14;
	data[9][13] = 16;
	objects = 2;
}

void MapObjects::EliminateSword(){
	data[6][9] = 15;
}
void MapObjects::EliminateFireball(){
	data[9][13] = 15;
}
