#pragma once
#include "Libraries.h"



class SuperLuigiBike{
	Matrix2D <int> Mapa;
	LinkedListPointer <Driver*> LinkedList;
	int players;
	int MAX_ROW, MAX_COLUMN;
	Driver *polymorphiscDrivers;
	bool win;
public:
	SuperLuigiBike(int MAX_ROW, int MAX_COLUMN);
	~SuperLuigiBike();
	void run();
	void initPlayers();
	void initMap();
	void startRace();
};