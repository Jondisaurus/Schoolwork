#include <iostream>
#include "account.h"
#include "firm.h"
#include "getqueue.h"

using namespace std; 

// ----------------------------------------------------------------------------
//    CSS342 Lab 5  - Fall 2011 - Dr. Carol Zander
//
// AUTHOR: Jonathan Difrancesco
// PURPOSE: To process and display transaction data from the bank 
//          "Lots Of Savings Earned" (Lose). Displays all transactions
//          processed through the day and starting/ending balances. 
//
// ASSUMPTIONS : 
//               --All data is formatted in the text files correctly
//               --Data is all positive and able to be properly displayed
//
//------------------------------------------------------------------------------

int main()
{
	getQueue trans;
	firm bank; 

	while(!trans.isEmpty())  //Processeses transactions from the queue while not empty
	{
		bank.processTrans(trans.getNext());  
	}

	bank.report();

	system("pause"); 
}

