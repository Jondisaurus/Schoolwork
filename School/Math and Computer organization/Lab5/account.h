#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
#include <list>
#include <iomanip> 

using namespace std;

//--------------------------  class Account  ------------------------------------
// Class Account: This class holds data members and a history linked list that 
//				  can be accessed by outside data members. This class also holds
//				  the transData struct, which is the object used by transaction
//                processing members.
//
// Assumptions:  
//    -- As a container class, it is the functions that use the class's 
//       resposibility to protect the data contained
//    -- The class that uses the account will be compatible with the history
//       list object.
//----------------------------------------------------------------------------

struct transData  // Data member that holds all transaction data
{
	char transType;
	int accountNum;
	int acctTyp;
	long bal1;
	int toAcct;
	int toAcctTyp; 
};

class Account
{
public:
	Account();
	~Account();
	
	friend ostream& operator<< (ostream &output, const Account srcAcct) // Formats and outputs class balance data
	{
		output << srcAcct.accountNum << "   " << srcAcct.firstName 
			   << " " << srcAcct.lastName << endl
			   << setw(18) << left << "Initial Balances:";

        for(int i=0 ; i < 10 ; i++)
			output << setw(6) << srcAcct.accountSrtBal[i];

		output << endl << setw(18) << left << "Final Balances:";

		for(int i=0 ; i < 10 ; i++)
			output << setw(6) << srcAcct.accountBal[i];

		output << endl << endl; 
        
        return output;
    }

    int accountNum;
	long int accountBal[10];
	long int accountSrtBal[10];

	string lastName;
	string firstName; 
	
	list<transData>::iterator it;             // Iterator to be used for access to data members
	list<transData> history;				  // Linked list that holds the transaction data
	
	void historyAdd(const transData);

	bool operator<(const Account&) const;     // Operators check for simular account numbers, no other data is checked     
    bool operator<=(const Account&) const;      
    bool operator>(const Account&) const;
    bool operator>=(const Account&) const;
    bool operator==(const Account&) const;
    bool operator!=(const Account&) const;
	
	 
private: // Private data members are not used, it is the responsibility of the class to protect the data from mutations
	
};

#endif
