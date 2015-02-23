#pragma once

#include "Map.h"
#include <vector>
#include <deque>

using namespace std;

class FSM {
	//Data structure for representing the node-edge relationship
	Map directionTable;
	//Value for specifying that there is NO any relationship
	int emptyRelationship;
	//Data structure for representing if nodes are marked
	Map markedNodes;

	//Mark all nodes as not visited
	void initMarkInformation();
	//Set the visited state of a node
	void setMarkedState(int node, bool value);
	//Set the visited of a node
	bool getMarkedState(int node);

public:
	//Constructor
	FSM(int nodes, int edges, int _emptyRelationship);
	//Destructor
	~FSM();
	FSM();
	void SetInfo(int states, int edges, int _emptyRelationship);
	//Add an edge between two nodes
	void addEdge(int sourceNode, int targetNode, int edge);
	//Get the target node when you go through the edge. Returns the emptyRelationship if the edge relationship doesn't exist
	int getNode(int sourceNode, int edge);
};