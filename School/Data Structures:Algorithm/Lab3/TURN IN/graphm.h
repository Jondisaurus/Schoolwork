#pragma once
#ifndef GRAPH_M
#define GRAPH_M
#ifndef MAXNODES
#define MAXNODES 100 // Maximum # of nodes that can be in the graph. 
#endif

#include "nodedata.h"
#include <iostream>
#include <queue>

using namespace std; 

//----------------------------------------------------------------------------
// class GraphM
// By: Jonathan Difrancesco 2012
//
// ADT GraphM: Generates a graph from an input stream and finds the shortest
//             distance between nodes in the graph using Dijkstra's shortest
//             path algorithm. Output will show a text description of the graph
//             along with the nodes traveled to. Output options include showing
//             all nodes, or displaying one node and associated path if found.
//
//             Nodes in the graph are assigned an int, and it's associated edge
//             costs are inputted along with a name for each node, stored as a 
//             NodeData object. 
//
// Assumptions: 
//               -Data is correctly formated, with a number indicating the number of
//                   nodes in the graph, names for each node in the graph, then the 
//                   associated edge costs. 
//               -The number of nodes is less than the graph's maximum of 100
//               -Distances between nodes that cannot be reached will be set to
//                    infinite(see below).
//               -"Infinite" for the purpose of this ADT is set to INT_MAX
//                    which is defined as 2147483647, which means that the max
//                    distance between nodess is 2,147,483,646
//               -In order for the "displayALL" and "display" methods to function
//                    correctly, the method "findShortestPath" must first be run. 
//
//----------------------------------------------------------------------------

class GraphM 
{
public:
	GraphM();
	void buildGraph(istream &);  //Builds the graph from the passed istream object
	bool insertEdge(int, int, int); //Inserts an edge into the graph, if the edge is not already present
	bool removeEdge(int, int); //Removes an edge from the graph if found 
	void findShortestPath(); //Find the shortest path between nodes
	void displayAll(); //Displays all nodes and associated pathing and shortest distance
	void display(int,int);  //Displays node distance and pathing for passed node

private:
	struct TableType 
	{
		bool visited; // whether node has been visited
		int dist; // shortest distance from source known so far
		int path; // previous node in path of min dist
	};

	NodeData data[MAXNODES]; // data for graph nodes information
	int C[MAXNODES][MAXNODES]; // Cost array, the adjacency matrix
	int size; // number of nodes in the graph
	TableType T[MAXNODES][MAXNODES]; // stores visited, distance, path
	int getShortestDist(int); //Helper method for "FindShortestPath". Find shortest unvisited distance
	void pathDisplay(TableType [][MAXNODES], int, int, queue<int>& Q); // Displays the shortest path and stores visited nodes in a queue
	void pathDisplayAll(TableType [][MAXNODES], int, int); //Same as PathDisplay without a queue

};

#endif


