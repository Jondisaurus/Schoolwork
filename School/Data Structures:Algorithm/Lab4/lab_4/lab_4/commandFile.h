#pragma once
#ifndef COMMANDFILE_H
#define COMMANDFILE_H
#include "command_base.h"
#include "commanddata.h"
#include <string>
#include <queue>
#include <iostream>
#include <fstream>

using namespace std;

//----------------------------------------------------------------------------
// class commandFile
// By: Jonathan Difrancesco 2012
// ABSTRACT CLASS
//
// ADT CommandFile
//                  Inherits the command_base class and handles function definitions
//                  and building of output queing
//
// Assumptions: 
//             -All data contained is properly formatted
//
//
//----------------------------------------------------------------------------

class commandFile : public command_base
{
public:
	commandFile(); //constructor
	virtual ~commandFile(){} //virtual destructor

	void initialize(const string); //initialize array
    CommandData* next(); //get next object in queue

private:
	queue<CommandData> Q; //queue that holds the commanddata objects
};


#endif
