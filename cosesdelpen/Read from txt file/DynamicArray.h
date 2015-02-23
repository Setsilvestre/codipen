#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
using namespace std;
class DynamicArray{
	int lenght;
	float *data;
	int vertices;
public:
	DynamicArray();
	~DynamicArray();
	void CreateArray();
	float returnData(int position);
	int getVertices();
};