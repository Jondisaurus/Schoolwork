#pragma once
#ifndef CUSTOMERDATA_H
#define CUSTOMERDATA_H

#include <iostream>
#include <list>
#include "commanddata.h"

using namespace std;


//----------------------------------------------------------------------------
// class cust
// By: Jonathan Difrancesco 2012
//
// ADT cust
//                 Container class that holds customer information as well as 
//                 the command history for a specific user
//
// Assumptions: 
//             -All data contained is properly formatted
//
//
//----------------------------------------------------------------------------

class cust
{
public:

	cust(); //default constructor
	~cust(){} //default destructor

	int custID; //customer id
	string firstName;//customer first name
	string lastName; //customer last name

	void histAdd(const CommandData&); //add to user history
	void dispHistory(); //display user history
	CommandData* nextCmdHist(); //get next history object
	void resetIt(); //reset iterator for history list

	bool operator<(const cust&) const; // < operator
    bool operator>(const cust&) const; // > operator
    bool operator==(const cust&) const;// equivilence operator
    bool operator!=(const cust&) const;// inequality operator

private:

	list<CommandData>::const_iterator histIt; //iterator that outputs history data
	list<CommandData> history; //list that contains history data

};

#endif
