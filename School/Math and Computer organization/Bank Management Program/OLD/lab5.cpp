#include <iostream>
#include <fstream>
#include <queue>
#include "bstree.h" 
#include "account.h"
#include "firm.h"

using namespace std; 


// ----------------------------------------------------------------------------
//    CSS342 Lab 5  - Fall 2011 - Dr. Carol Zander
//
// AUTHOR: Jonathan Difrancesco
// PURPOSE: To process and display transaction data to a bank object.
//
// ASSUMPTIONS : 
//               --All data is formatted in the text files correctly
//               --Data is all positive and able to be properly displayed
//
//------------------------------------------------------------------------------

//PROTOTYPES
bool getQueue(queue<transData>&);

//MAIN FUNCTION
int main()
{
	queue<transData> transQ;
	firm bank; 
	
	getQueue(transQ);

	while(!transQ.empty())
	{
		bank.processTrans(transQ.front()); 
		transQ.pop(); 
	}

	bank.report();

	system("pause"); 
}


// ---------------------------------------------------------------------------
// getQueue
// Builds the Queue object 
bool getQueue(queue<transData>& transQ)
{
	ifstream inFile("lab5command.txt");
	transData toAdd; 
	char getVal[10];
	char dumpLine[30];
	bool addToQueue = true; 
	
	if (!inFile)  //check to make sure file opens 
	{     
      cout << "Transaction Data could not be opened.\nTransactions are NOT loaded." << endl; 
      return 0;  
    }

	for(;;)
	{
		if(inFile >> skipws >> toAdd.transType == false)
			break;

		switch(toAdd.transType)
		{
			case 'W':
			case 'D': 
				inFile.read(getVal, 5);
				toAdd.accountNum = atoi(getVal);

				inFile.read(getVal, 2);
				toAdd.acctTyp = atoi(getVal);

				inFile >> skipws >> toAdd.bal1;

				break;

			case 'M':
				inFile.read(getVal, 5);
				toAdd.accountNum = atoi(getVal);
				inFile.read(getVal, 2);
				toAdd.acctTyp = atoi(getVal);

				inFile >> skipws >> toAdd.bal1;

				inFile.read(getVal, 5);
				toAdd.toAcct = atoi(getVal);
				inFile.read(getVal, 2);
				toAdd.toAcctTyp = atoi(getVal);

				break;

			case 'H':
				inFile >> skipws >> toAdd.accountNum;
				break;

			case ' ':
			case '\n':
				addToQueue = false; 
				break;

			default:
				cout << "Unknown transaction type '" << toAdd.transType << "' entered\n";
				inFile.getline(dumpLine,30);
				addToQueue = false;
				break;
		}

		if(addToQueue == true)
		{
			transQ.push(toAdd); 
		}

		addToQueue = true;
		if(inFile.eof()) break;
	}
	return 1; 
}
