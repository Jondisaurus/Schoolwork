//#pragma once
#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include "command_base.h"
#include "commandFile.h"
#include "commanddata.h"
#include "customer_list.h"
#include "customer_base.h"
#include "customerdata.h"
#include "mediastore.h"
#include <string>

using namespace std;

//----------------------------------------------------------------------------
// class Manager
// By: Jonathan Difrancesco 2012
//
// ADT Manager
//               Initializes commands, customers, and media objects and deligates
//               commands between classes
//
// Assumptions: 
//             -All data contained is properly formatted
//
//
//----------------------------------------------------------------------------

class Manager
{
public:
	Manager(); //default constructor
	~Manager(); //default destructor

	bool initialize(const string, const string, const string); //initialize data members
	void run(); //run operations till no more object remain in queue

private:
	command_base* commands; //command object
	customer_base* customers; //customer storage object
	MediaStore* media; //media storage object
};

#endif

