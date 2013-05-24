#include <iostream>
#include <fstream>
#include <queue>
#include "account.h"
#include "getqueue.h"

// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for getQueue
getQueue::getQueue() 
{
	buildQueue(transQ);
};

// ---------------------------------------------------------------------------
// Destructor 
// Default destructor for getQueue
getQueue::~getQueue() 
{
};

// ---------------------------------------------------------------------------
// isEmpty 
// Checks to see if the queue is empty
bool getQueue::isEmpty()
{
	return transQ.empty();
};

// ---------------------------------------------------------------------------
// getNext 
// returns the next queue object if available
transData getQueue::getNext()
{
	if(!transQ.empty())
	{
		transData temp = transQ.front();
		transQ.pop();
		return temp; 
	}
	else 
		cout << "\n\n THE QUEUE IS EMPTY \n\n";

};

// ---------------------------------------------------------------------------
// buildQueue
// builds the queue from the command text file loaded into transData structs
void getQueue::buildQueue(queue<transData>& transQ)
{
	ifstream inFile("lab5command.txt");
	transData toAdd; 
	char getVal[10] = {0};
	char dumpLine[30] = {0};
	bool addToQueue = true; 
	
	if (!inFile)  //check to make sure file opens 
	{     
      cout << "Transaction Data could not be opened.\nTransactions are NOT loaded." << endl; 
      return;  
    }

	for(;;)
	{
		if(inFile >> skipws >> toAdd.transType == false)
			break;

		switch(toAdd.transType)
		{
			case 'W':
			case 'D': //Withdraw and Deposit transactions
				inFile.read(getVal, 5);
				toAdd.accountNum = atoi(getVal);

				inFile.read(getVal, 2);
				toAdd.acctTyp = atoi(getVal);

				inFile >> skipws >> toAdd.bal1;

				break;

			case 'M': //Move transactions
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

			case 'H':  //History transactions
				inFile >> skipws >> toAdd.accountNum;
				break;

			case ' ':
			case '\n': // If spaces or newline is encountered, flags data as invalid
				addToQueue = false; 
				break;

			default:   // For any other data an error message is given and also flagged invalid
				cout << "Unknown transaction type '" << toAdd.transType << "' entered\n";
				inFile.getline(dumpLine,30);
				addToQueue = false;
				break;
		}

		if(addToQueue == true) // Adds data to the queue if valid
		{
			transQ.push(toAdd); 
		}

		addToQueue = true;
		if(inFile.eof()) break;
	}
	return; 
};
