#include <iostream>
#include <string>
#include "manager.h"

using namespace std;

int main()
{
	string custID = "data4customers.txt";
	string cmds = "data4commands.txt";
	string movies = "data4movies.txt";

	Manager mgr;

	mgr.initialize(custID, cmds, movies); 
	mgr.run(); 

	system("pause"); 
	return 0; 


};