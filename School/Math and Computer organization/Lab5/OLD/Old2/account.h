#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <iostream>
#include <string>
#include <list>
#include <iomanip> 

using namespace std;

struct transData
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
	
	friend ostream& operator<< (ostream &output, const Account srcAcct)
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
	
	list<transData>::iterator it;
	list<transData> history;
	
	void historyAdd(const transData);

	bool operator<(const Account&) const;      
    bool operator<=(const Account&) const;      
    bool operator>(const Account&) const;
    bool operator>=(const Account&) const;
    bool operator==(const Account&) const;
    bool operator!=(const Account&) const;
	
	 
private:
	
};

#endif
