#pragma once
#ifndef GRAPH_L
#define GRAPH_L
#ifndef MAXNODES
#define MAXNODES 100 // Maximum # of nodes that can be in the graph. 
#endif

#include <iostream>
#include <string>

using namespace std;

//----------------------------------------------------------------------------
// class GraphL
// By: Jonathan Difrancesco 2012
//
// ADT GraphL: Generates a graph from an input stream and stores data in an
//             array of structs that hold the node name, a bool indicating 
//             whether the node had been visited and a linked list with edge data.
//             
//             The ADT can output the graph and all of its data members, as well
//             as perform a depth first search to retrieve ordered data.
//
// Assumptions: 
//               -Data is correctly formated, with a number indicating the number of
//                   nodes in the graph, names for each node in the graph, then the 
//                   associated edge costs. 
//               -The number of nodes is less than the graph's maximum of 100 
//
//----------------------------------------------------------------------------

class GraphL
{
public:
	GraphL(); // Default Constructor
	~GraphL(); // Default Destructor
	void buildGraph(istream&); // Build the graph from an input stream
	void displayGraph(); // Displays the contents of the graph
	void depthFirstSearch(); // Output the node data in depth first order

private:
	int size;  // The number of nodes in the graph
	struct EdgeNode; // forward reference for the compiler
	struct GraphNode // The nodes that make up the array
	{ 
		EdgeNode* edgeHead; // head of the list of edges
		string name; // The location name
		bool visited; //Whether the node has been visited yet
	};
	struct EdgeNode  // Nodes that make up the GraphNode linked list
	{
		int adjGraphNode; // subscript of the adjacent graph node
		EdgeNode* nextEdge; // Pointer to the next node in the list
	};
	GraphNode G[MAXNODES]; // Array of GraphNodes that hold node/edge data

	bool insert(GraphNode&, int); // Inserts an edge into the graph
	void removeHelper(EdgeNode*&); // Works with deconstructor to free memory
	void dfs(GraphNode [] , int); // Helper class that outputs the ordered node number
};

#endif
