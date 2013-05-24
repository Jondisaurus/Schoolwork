#ifndef FIRM_H
#define FIRM_H

#include <iostream>
#include "account.h"
#include "bstree.h"

using namespace std; 

//--------------------------  class firm  ------------------------------------
// Class firm: This class holds and processes transaction data passed to it
//             by transData members, stores it in Account objects, and displays
//             the data for the user
//          
// Assumptions:  
//    -- Data built is correctly formatted for use in the class
//
//----------------------------------------------------------------------------

class firm
{
public:
	firm();
	~firm();

	bool processTrans(const transData); 
	bool buildAccts();
	void report(); 

private:
	string typeStr[10]; // Holds strings with the different types of accounts used by the class

	bool getHistory(const int);
	bool deposit(const int, const int, const long);
	bool move(const int, const int, const long, const int, const int);
	bool withdraw(const int, const int, const long); 

	void historyAdd(const int, const transData); 
	void histDispHelper(Account*);
	BSTree acctObj; 
};

#endif
