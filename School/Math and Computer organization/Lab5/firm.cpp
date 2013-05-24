#include <iostream>
#include <fstream>
#include <iomanip>
#include "account.h"
#include "bstree.h"
#include "firm.h"

using namespace std;

// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for Firm
firm::firm()
{
	buildAccts();

	typeStr[0] = "Money Market";
	typeStr[1] = "Prime Money Market";
	typeStr[2] = "Long-Term Bond";
	typeStr[3] = "Short-Term Bond";
	typeStr[4] = "500 Index Fund";
	typeStr[5] = "Capital Value Fund";
	typeStr[6] = "Growth Equity Fund";
	typeStr[7] = "Growth Index Fund";
	typeStr[8] = "Value Fund";
	typeStr[9] = "Value Stock Index";
	
}

// ---------------------------------------------------------------------------
// Destructor 
// Destructor for IntSet
firm::~firm()
{
}

// ---------------------------------------------------------------------------
// processTrans 
// Processes transaction data and checks for errors, adds data to account history
bool firm::processTrans(const transData source)
{	
	switch(source.transType)
	{
		case 'D':  //Deposit
			 if(deposit(source.accountNum, source.acctTyp, source.bal1))
			 {
				 historyAdd(source.accountNum, source);
				 return 1;
			 }
			 else return 0; 
			 break;

		case 'M':  //Move
			if(move(source.accountNum, source.acctTyp,  source.bal1, source.toAcct, source.toAcctTyp))
			{
				 historyAdd(source.accountNum, source);
				 return 1;
			}
			else return 0; 
			break;

		case 'W':  //Withdraw
			if(withdraw(source.accountNum, source.acctTyp, source.bal1))
			{
				 historyAdd(source.accountNum, source);
				 return 1;
			 }
			 else return 0; 
			 break;

		case 'H':   //History
			historyAdd(source.accountNum, source);
			getHistory(source.accountNum);
			return 1; 
			break;

		default:   //Called if the type of transaction is not valid
			cout << "ERROR: Invalid Transaction ' " << source.transType << endl;
			return false;
			break;
	}
}

// ---------------------------------------------------------------------------
// Report
// displays data showing the before/after conditions of the data members
void firm::report()
{
	cout << "\n REPORT \n\n";
	acctObj.display();
}

// ---------------------------------------------------------------------------
// buildAccts 
// builds a binary search tree from account data pulled from an external file
bool firm::buildAccts()
{
	ifstream inFile("lab5data.txt");
	Account* toAdd; 
	
	if (!inFile)  {    // Check to make sure file opens 
      cout << "Account Data could not be opened.\nAccounts are NOT loaded." << endl; 
      return 0;  
    }

	for(;;)
	{
		toAdd = new Account; 

		if( inFile >> skipws >> toAdd->lastName >> toAdd->firstName >> toAdd->accountNum == false)
        { 
			delete toAdd; // Deletes pointer if cant retrieve data 
			break;
        }

		for(int i = 0; i < 10; i++)
			inFile >> skipws >> toAdd->accountSrtBal[i];

		for(int i = 0; i < 10; i++)  //copies accountBal data from the starting values
			toAdd->accountBal[i] = toAdd->accountSrtBal[i];

		acctObj.insert(toAdd); // Inserts the account into the BSTree
		 
		if(inFile.eof()) break;
	}
	return 1; 
}

// ---------------------------------------------------------------------------
// getHistory
// retrieves the history data for the transactions
bool firm::getHistory(const int acctnum)
{
	Account find;
	Account* found;

	find.accountNum = acctnum;

	if(acctObj.retrieve(find, found))
	{
		cout << "\nHistory of transactions for client " << found->firstName << " " 
			 << found->lastName << ", client ID = " << found->accountNum << endl
			 << setw(10) << left << "Type" << setw(8) << "Amount" << setw(12)
			 << "Detail" << endl << "--------- ------- ----------------------------------------\n"; 

		histDispHelper(found);
		
		cout << endl << endl;

		return 1;
	}
	else
	{
		cout << "Unknown client ID #" << acctnum << " requested\n";
		return 0;
	}
}

// ---------------------------------------------------------------------------
// deposit
// handles deposits to the accounts
bool firm::deposit(const int acctNum, const int type, const long bal)
{
	Account find;
	Account* found;

	find.accountNum = acctNum;

	if(acctObj.retrieve(find, found))
	{
		found->accountBal[type] += bal;
		return 1;
	}
	else
	{
		cout << "Unknown client ID #" << acctNum << " requested\n\n";
		return 0;
	}
}

// ---------------------------------------------------------------------------
// move
// handles move operations from account to account
bool firm::move(const int acctnum, const int type, const long bal, const int toAcct, const int toAcctTyp)
{
	Account find;	
	Account findTo;

	Account* found;
	Account* foundTo; 

	transData temp;

	find.accountNum = acctnum;
	findTo.accountNum = toAcct; 

	if(acctObj.retrieve(find, found) && acctObj.retrieve(findTo, foundTo))
	{
		if( found->accountBal[type] >= bal)
		{
			temp.transType = 'D';     //builds a transData struct to add to the history of the account being added to
			temp.accountNum = toAcct;
			temp.acctTyp = toAcctTyp;
			temp.bal1 = bal;

			found->accountBal[type] -= bal;
			deposit(toAcct, toAcctTyp, bal);
			historyAdd(toAcct, temp); 

			return 1; 
		}
		else{
			cout << "Move not performed on " << typeStr[type] << " for client #" << acctnum << ':'
				 << "\n		insufficient funds\n\n";
			return 0;
		}
	}
	else
	{
		cout << "Unknown client ID #" << acctnum << " or " << toAcct << " requested\n\n";
		return 0;
	}
}

// ---------------------------------------------------------------------------
// withdraw
// handles withdrawls from the accounts
bool firm::withdraw(const int acctnum, const int type, const long bal)
{
	Account find;
	Account* found;

	find.accountNum = acctnum;

	if(acctObj.retrieve(find, found))
	{
		if( found->accountBal[type] >= bal)
		{
			found->accountBal[type] -= bal;
			return 1;
		}
		else {
			cout << "Withdrawl not performed on " << typeStr[type] << " for client #" << acctnum
				 << ':' << "\n		insufficient funds\n\n";
			return 0;
		}
	}
	else
	{
		cout << "Unknown client ID #" << acctnum << " requested\n\n";
		return 0; 
	}
}

// ---------------------------------------------------------------------------
// historyAdd
// adds history data to account class
void firm::historyAdd(const int acctnum, const transData source)
{
	Account find;
	Account* found;

	find.accountNum = acctnum;

	if(acctObj.retrieve(find, found))
	{
		found->historyAdd(source);
	}
	else
	{
		cout << "Unknown client ID #" << acctnum  << " requested\n\n";
	}
}

// ---------------------------------------------------------------------------
// histDispHelper
// formats and displays history data from the Account class
void firm::histDispHelper(Account* source)
{
	transData output;

	source->it = source->history.begin();

	while(source->it != source->history.end())
	{
		output = *source->it; // pulls history data from current iterator location

		switch(output.transType)
		{
		case 'D':  // Deposit
			cout << setw(9) << left << "deposit" << setw(2) << right << "$"
				 << setw(6) << output.bal1 << " " << setw(5) << left
				 << "into " << setw(35) << typeStr[output.acctTyp] << endl;
			break;

		case 'M':   // Move
			cout << setw(9) << left << "move" << setw(2) << right << "$"
				 << setw(6) << output.bal1 << " " << setw(5) << left
				 << "from " << setw(35) << typeStr[output.acctTyp] << endl
				 << setw(18) << right << ' ' << setw(3) << left 
				 << "to " << typeStr[output.toAcctTyp] << " for client #" 
				 << output.toAcct << endl;
			break;

		case 'W':    // Withdraw
			cout << setw(9) << left << "withdraw" << setw(2) << right << "$"
				 << setw(6) << output.bal1 << " " << setw(5) << left 
				 << "from " << setw(35) << typeStr[output.acctTyp] << endl;
			break;

		case 'H':   // History
			cout << setw(9) << left << "history" << endl;
			break;
		}

		source->it++;  // Increment iterator
	}
}

