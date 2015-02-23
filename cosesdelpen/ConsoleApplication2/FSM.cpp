#include "FSM.h"

/**
* Overload constructor. It pass the parameters to the internal data structures
* @param states represents how many nodes has the graph (rows in the direction table)
* @param edges represents the maximal number of edges (columns in the direction table)
* @param _emptyRelationship is the initial value set in the direction table
*/
FSM::FSM(int states, int edges, int _emptyRelationship) :directionTable(states, edges), markedNodes(states, 1){
	emptyRelationship = _emptyRelationship;
	for (int i = 0; i < directionTable.getRows(); i++){
		for (int j = 0; j < directionTable.getColumns(); j++) {
			directionTable.Set(i, j, emptyRelationship);
		}
	}
}

/*
* Destructor
*/
FSM::~FSM() {

}

/*
* Initialize all the nodes as NOT visited
*/
void FSM::initMarkInformation() {
	for (int i = 0; i < markedNodes.getColumns(); i++) {
		markedNodes.Set(i, 0, false);
	}
}

/*
* Change the visited state of a node
* @param node is the node to update
* @param value is the new value
*/
void FSM::setMarkedState(int node, bool value) {
	markedNodes.Set(node, 0, value);
}

/*
* Return the current state of a given node
* @param node is the node to check
* @return bool that represents the state of the speficied node. True if it has been visited. Otherwise, false
*/
bool FSM::getMarkedState(int node) {
	return markedNodes.getSurface(node, 0);
}

/*
* Add an edge between two nodes
* @param sourceNode is the source node
* @param targetNode is the target node
* @param edge is the edgeId that links nodes
*/
void FSM::addEdge(int sourceNode, int targetNode, int edge) {
	//Before adding a new edge you need to remove a previous
	if (directionTable.getSurface(sourceNode, edge) == -1) {
		directionTable.Set(sourceNode, edge, targetNode);
	}
	else {
		throw exception("Before adding a new edge you need to remove a previous");
	}
}

/*
* Get the new node that is got when the edge is followed from the sourceNode
*@param sourceNode is the source node
* @param targetNode is the target node
*/
int FSM::getNode(int sourceNode, int edge) {
	return directionTable.getSurface(sourceNode, edge);
}

