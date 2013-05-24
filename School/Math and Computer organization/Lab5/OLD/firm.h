#ifndef FIRM_H
#define FIRM_H

#include <iostream>
#include "account.h"
#include "bstree.h"

using namespace std; 

//--------------------------  class List  ------------------------------------
// Class firm: This class holds and processes transaction data passed to it
//             by transData members and outputs data
      
//          
// Assumptions:  
//    -- Data that will be built is correctly formatted
//    
//
//----------------------------------------------------------------------------

class firm
{
public:
	firm();
	~firm();

	bool processTrans(const transData); 
	bool getAcctData();
	bool buildAccts();
	void report(); 

private:
	
	bool getHistory(const int);
	bool deposit(const int, const int, const long);
	bool move(const int, const int, const long, const int, const int);
	bool withdraw(const int, const int, const long); 

	string typeStr[10]; 

	void historyAdd(const int, const transData); 
	void histDispHelper(Account*);
	BSTree acctObj; 
};

#endif