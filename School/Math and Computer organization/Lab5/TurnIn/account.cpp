#include "account.h"

// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for account class
Account::Account()
{
}

// ---------------------------------------------------------------------------
// Destructor 
// Default Destructor for account class
Account::~Account()
{
	history.clear(); 
}

// ---------------------------------------------------------------------------
// historyAdd 
// Adds objects to history list
void Account::historyAdd(const transData source)
{
	it = history.end(); 
	history.insert(it, source);

}

//-------------------------------  <  ----------------------------------------
// < defined by value of account number
bool Account::operator<(const Account& src) const { 
	return accountNum < src.accountNum;
}


//-------------------------------  <= ----------------------------------------
// < defined by value of account number
bool Account::operator<=(const Account& src) const { 
   return *this < src || *this == src;
}

//-------------------------------  >  ----------------------------------------
// > defined by value of account number
bool Account::operator>(const Account& src) const { 
   return accountNum > src.accountNum;
}

//-------------------------------  >= ----------------------------------------
// < defined by value of account number
bool Account::operator>=(const Account& src) const { 
   return *this > src || *this == src;
}

//----------------- operator == (equality) ----------------
// if name of calling and passed object are equal,
//   return true, otherwise false
//
bool Account::operator==(const Account& src) const {
   return accountNum == src.accountNum;
}

//----------------- operator != (inequality) ----------------
// return opposite value of operator==
bool Account::operator!=(const Account& src) const {
   return !(*this == src);
}
