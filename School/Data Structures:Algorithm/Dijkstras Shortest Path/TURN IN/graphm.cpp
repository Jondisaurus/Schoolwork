#include "graphm.h"
#include <queue>
#include <iomanip>

// =========================== graphm.cpp ===========================
//
// Contains contructor and method definitions for graphm.h
//
// ==================================================================

// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for GraphM. Initializes the arrays.
GraphM::GraphM()
{
	for(int i = 0; i < MAXNODES; i++)
		for(int j = 0; j < MAXNODES; j++)
		{
			C[i][j] = INT_MAX;
			T[i][j].visited = false;
			T[i][j].dist = INT_MAX;
			T[i][j].path = 0;
		}
}

// ---------------------------------------------------------------------------
// buildGraph 
// Builds the graph from the passed istream object.
// NOTE: DATA MUST BE CORRECTLY FORMATTED FOR METHOD TO WORK CORRECTLY
void GraphM::buildGraph(istream & input)
{
	int graphSize = 0;
	int node;
	int edge;
	int cost;
	
	input >> graphSize; //gets size of graph
	
	if(graphSize == 0 || graphSize > MAXNODES) // Bails if graph size if zero
		return;                                // or more than MAXNODES

	string temp;
	size = graphSize;
	getline(input,temp); //dump size EOL character

	for(int i = 1; i <= size + 1; i++) //Builds data array
	{
		getline(input, temp); 
		data[i] = temp; 
	}

	while(!input.eof()) //adds edges and distances to array. 
	{
		input >> node >> edge >> cost;
		if(node == 0)
			break;
		C[node][edge] = cost;
	}	
}

// ---------------------------------------------------------------------------
// insertEdge 
// Inserts an edge into the Graph if the edge is not already defined.
// False is returned if the edge is already defined. 
bool GraphM::insertEdge(int node, int edge, int dist)
{
	if(C[node][edge] == INT_MAX)
	{
		C[node][edge] = dist;
		return 1;
	}
	else return 0; //returns false if there is already an edge defined
}

// ---------------------------------------------------------------------------
// removeEdge 
// Removes an edge from the Graph if it is found. 
// Returns false if the node is already absent from the graph. 
bool GraphM::removeEdge(int node, int edge)
{
	if(C[node][edge] != INT_MAX)
	{
		C[node][edge] = INT_MAX;
		return 1;
	}
	else return 0;
}

// ---------------------------------------------------------------------------
// findShortestPath
// Finds the shortest path between each node using Dijkstra's algorithm. Implemented
//   using private arrays: T for the shortest distance between nodes, pathing, and
//   marking for being visited; and C to record the nodes and the distances between
//   them. 
void GraphM::findShortestPath()
{
	int V;

	for(int source = 1; source <= size; source++) //loop for each node
	{
		T[source][source].dist = 0; 
		T[source][source].visited = true;
		T[source][source].path = source;
		V = source;

		for(int numRuns = 1; numRuns < size ; numRuns++) //Main loop for for 'V'
		{
			for(int W = 1; W <= size; W++) //Loop for the 'W' component
			{
				if(C[V][W] == INT_MAX || T[source][W].visited == true)
					continue; //Skips this 'W' if the node is visited or distance is infinite
				else if(T[source][W].dist > T[source][V].dist + C[V][W]) //Sets shortest distance
				{
					T[source][W].dist = T[source][V].dist + C[V][W]; 
					T[source][W].path = V; 
				}
			}
			
			T[source][V].visited = true; 
			V = getShortestDist(source); 
		}
		T[source][V].visited = true; //Set last node to visited

	}
}

// ==PRIVATE==-----------------------------------------------------------------
// getShortestDist
// **Helper Method for findShortestPath**
// Finds the unvisited node with the lowest distance for the V component of
// Dijkstra's algorithm. 
int GraphM::getShortestDist(int source)
{
	int min = 0;

	for(int i = 1; i <= size; i++)
	{
		if(T[source][i].dist < T[source][min].dist && T[source][i].visited == false)
			min = i;
	}

	return min;
}

// ---------------------------------------------------------------------------
// display
// Displays the passed node and destination using a recursive helper class and 
// a queue<int> object. 
//
// NOTE: THIS FUNCTION WILL NOT FUNCTION PROPERLY UNLESS "findShortestPath()" 
// IS RUN FIRST
void GraphM::display(int source, int dest)
{
	if(T[source][dest].visited == true)
	{
		int temp;
		queue<int> Q;

		cout << setw(5) << right << source << setw(5) << dest 
			 << setw(5) << T[source][dest].dist << "     ";
		pathDisplay(T,source,dest, Q);
		cout << endl;

		while(!Q.empty()) //Display path information from the queue
		{
			temp = Q.front();
			cout << data[temp] << endl;
			Q.pop(); 
		}
	}
	else
	{
		cout << "\nNO PATH FOUND FOR NODE " << source << " TO NODE " << dest <<"!\n";
	}


}

 
// ==PRIVATE==-----------------------------------------------------------------
// **Helper Method for display**
// Displays the path information for the passed node and saves the node values to
// the passed queue object. 
// NOTE: THIS METHOD IS ONLY COMPATIBLE WITH THE PRIVATE T ARRAY
void GraphM::pathDisplay(TableType T[][MAXNODES] , int source, int nextval, queue<int>& Q)
{
	if(T[source][nextval].visited == false)
	{
		cout << "\nPATH NOT FOUND!!\n";
		return;
	}

	if(T[source][nextval].path != nextval)
		pathDisplay(T, source, T[source][nextval].path, Q);

	cout << nextval << " ";
	Q.push(nextval); 
}

// ---------------------------------------------------------------------------
// displayAll
// Formats and displays all node information in the graph class. 
//
// NOTE: THIS FUNCTION WILL NOT FUNCTION PROPERLY UNLESS "findShortestPath()" 
// IS RUN FIRST!
void GraphM::displayAll()
{
	cout << left << setw(30) << "Description" << setw(12) << "From node" << setw(10) 
		 << "To Node" << setw(13) << "Dijkstra's" << setw(5) << "Path" << endl;

	for(int i = 1; i <= size; i++)
	{
		cout << left << data[i] << endl;

		for(int j = 1; j <= size; j++)
		{
			if(i == j)
				continue;

			cout << left << setw(35) << ' ' << setw(10) << i << setw(7) << j;

			if(T[i][j].visited == true)
			{
				cout << setw(13) << T[i][j].dist;
				pathDisplayAll(T,i,j);
				cout << endl;
			}
			else
			{
				cout << setw(20) << "----" << endl;
			}
		}
	}
}

// ==PRIVATE== -----------------------------------------------------------------
// pathDisplayAll
// **Helper Method for displayAll**
//Displays the path information for the passed nod
// NOTE: THIS METHOD IS ONLY COMPATIBLE WITH THE PRIVATE T ARRAY
void GraphM::pathDisplayAll(TableType T[][MAXNODES] , int source, int nextval)
{
	if(T[source][nextval].visited == false)
	{
		cout << "\nPATH NOT FOUND!!\n";
		return;
	}

	if(T[source][nextval].path != nextval)
		pathDisplayAll(T, source, T[source][nextval].path);

	cout << nextval << " ";
}
