#pragma once
#ifndef CUSTOMERDATA_H
#define CUSTOMERDATA_H

#include <iostream>
#include <list>
#include "commanddata.h"

using namespace std;

class cust
{
public:

	cust();
	~cust(){}

	int custID;
	string firstName;
	string lastName;

	void histAdd(const CommandData&);
	void dispHistory();

	bool operator<(const cust&) const;      
    bool operator>(const cust&) const;
    bool operator==(const cust&) const;
    bool operator!=(const cust&) const;


private:

	list<CommandData> history;

};

#endif
