#pragma once
#ifndef CUSTOMER_LIST_H
#define CUSTOMER_List_H

#include "command_base.h"
#include "customerdata.h"
#include "customer_base.h"
#include "HashTable.h"
#include <iostream>
#include <list>
#include <fstream>

using namespace std;

//----------------------------------------------------------------------------
// class customer_list
// By: Jonathan Difrancesco 2012
// ABSTRACT CLASS
//
// ADT CommandData
//                  Inherits interface from customer_base and provides implementation
//
// Assumptions: 
//             -All data contained is properly formatted
//
//
//----------------------------------------------------------------------------

class customer_list : public customer_base
{
public:
	customer_list(); //defualt constructor
	virtual ~customer_list(){} //virtual destructor

	void initialize(const string); //initialize cutomers
	cust* getUser(const int); //get a user from hash table
	void processUser(const CommandData); //process command on user data
	void displayUser(const int); //display user information

private:
	HashTable T; //hash table for class that handles storage
};

#endif
