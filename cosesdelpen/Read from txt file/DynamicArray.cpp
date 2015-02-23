#include "DynamicArray.h"

DynamicArray::DynamicArray(){
	data = 0;
}

DynamicArray::~DynamicArray(){
	if (data!= 0){
		delete[]data;
	}
}


void DynamicArray::CreateArray(){
	string line;
	ifstream myfile;
	myfile.open("Vertex.txt", ios::in);
	myfile >> line;
	/*while (!myfile.eof()){
		getline(myfile, line);
	}*/
	lenght = stof(line);
	vertices = lenght;
	lenght = lenght * 7;
	myfile.close();
	data = new float [lenght+1];
	int i = 0;
	myfile.open("Vertex.txt", ios::in);
	while (!myfile.eof()){
		if (i == 0){
			myfile >> line;
		}
		myfile >> line;
		data[i] = stof(line);
		i++;
	}
	myfile.close();
}

float DynamicArray::returnData(int position){
	return data[position];
}

int DynamicArray::getVertices(){
	return vertices;
}