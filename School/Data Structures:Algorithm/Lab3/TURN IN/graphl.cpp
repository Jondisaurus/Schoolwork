#include "graphl.h"
#include <iomanip>

// =========================== graphl.cpp ===========================
//
// Contains contructor/destructor and method definitions for graphl.h
//
// ==================================================================

// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for GraphL. Initializes the array.
GraphL::GraphL()
{
	for(int i = 0; i < MAXNODES; i++)
	{
		G[i].edgeHead = NULL; 
		G[i].name = ""; 
	}
}

// ---------------------------------------------------------------------------
// Destructor 
// Default destructor for GraphL. Frees the memory from the linked lists.
GraphL::~GraphL()
{
	for(int i = 0; i < MAXNODES; i++)
	{
		if(G[i].edgeHead != NULL)
			removeHelper(G[i].edgeHead);
	}
}

// ==PRIVATE==-----------------------------------------------------------------
// removeHelper
// **Helper Method for the Destructor**
// Recursivly accesses all the nodes and frees their memory. 
void GraphL::removeHelper(EdgeNode*& source)
{
	if(source->nextEdge != NULL)
		removeHelper(source->nextEdge);
	delete source;
	source = NULL; 
}

// ---------------------------------------------------------------------------
// buildGraph
// Builds the graph from istream and builds lists of adjacent nodes
void GraphL::buildGraph(istream& input)
{
	int graphSize = 0;
	int node;
	int edge;
	
	input >> graphSize; //gets size of graph
	
	if(graphSize == 0 || graphSize > MAXNODES) // Bails if graph size if zero
		return;                                // or more than MAXNODES

	string temp;
	size = graphSize;
	getline(input,temp); //dump size EOL character

	for(int i = 1; i <= size; i++) //Adds node names to Array
	{
		getline(input, temp); 
		G[i].name = temp; 
	}

	while(!input.eof()) //inserts nodes into array 
	{
		input >> node >> edge;
		if(node == 0 || edge == 0)
			break; 
		insert(G[node], edge);
	}	
}

// ==PRIVATE==-----------------------------------------------------------------
// insert
// Inserts edge data into the graph starting at the front of the linked list. 
bool GraphL::insert(GraphNode& G, int edge)
{
	EdgeNode* ptr = new EdgeNode;

	if(ptr == NULL)
		return 0;      // Out of memory

	ptr->adjGraphNode = edge;
	ptr->nextEdge = NULL; 

	if(G.edgeHead == NULL)
	{
		G.edgeHead = ptr;
		return 1;
		
	}
	else if(G.edgeHead->adjGraphNode == edge) //returns 0 if  front of the list is edge
	{
		delete ptr;
		return 0;
	}

	EdgeNode* prevHead = G.edgeHead; 
	G.edgeHead = ptr; // Replace head with pointer
	ptr->nextEdge = prevHead;
	return 1;
}

// ---------------------------------------------------------------------------
// Display graph
// Displays the graph and outputs all of its edge data
void GraphL::displayGraph()
{
	cout << "\nGraph:\n";

	for(int i = 1; i <= size; i++)
	{
		cout << "Node " << i << "      " << G[i].name << endl;

		if(G[i].edgeHead != NULL)
		{
			EdgeNode* current = G[i].edgeHead;

			while( current != NULL) // walk through and pull data from the list
			{
				cout << "  edge " << i << " " << current->adjGraphNode << endl;
				current = current->nextEdge;
			}
		}

	}

	cout << endl;
}

// ---------------------------------------------------------------------------
// depthFirstSearch
// Performs a depth first search on all the nodes and outputs their associated
// edge data via the DFS method
void GraphL::depthFirstSearch()
{
	for(int i = 1; i <= size; i++) // mark all nodes as unvisited
	{
		G[i].visited = false;
	}

	cout << "Depth-First ordering:";

	for(int i = 1; i <= size; i++)
	{
		if(G[i].visited == false)
			dfs(G, i);
	}

	cout << endl;
}

// ==PRIVATE==-----------------------------------------------------------------
// dfs
// Recursivly accesses all nodes linked to i and marks/displays the node number 
void GraphL::dfs(GraphNode source[], int i)
{
	source[i].visited = true;
	
	cout << " " << i;

	EdgeNode* current = source[i].edgeHead;

	while(current != NULL)
	{
		if(G[current->adjGraphNode].visited == false) 
			dfs(G, current->adjGraphNode); //search for all unvisited nodes

		current = current->nextEdge;
	}
}
