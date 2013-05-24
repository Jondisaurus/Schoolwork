#pragma once
#ifndef CUSTOMER_BASE_H
#define CUSTOMER_BASE_H

#include "command_base.h"
#include "customerdata.h"
#include "commanddata.h"
#include <iostream>
#include <list>

using namespace std;

//----------------------------------------------------------------------------
// class customer_base
// By: Jonathan Difrancesco 2012
// ABSTRACT CLASS
//
// ADT customer_base
//                  Handles interface for customer objects. Allows virtual
//                  addition of more customer_base objects.
//
// Assumptions: 
//             -All data contained is properly formatted
//
//
//----------------------------------------------------------------------------

class customer_base
{
public:
	customer_base(); //default construcor
	virtual ~customer_base(){} //virtual destructor

	virtual void initialize(const string) = 0; //initialize customers
	virtual cust* getUser(const int) = 0; //get a specific user
	virtual void processUser(const CommandData) = 0; //process user data
	virtual void displayUser(const int) = 0; //display user information
};

#endif
