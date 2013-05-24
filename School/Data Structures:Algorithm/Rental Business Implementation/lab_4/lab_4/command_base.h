#pragma once
#ifndef COMMANDBASE_H
#define COMMANDBASE_H

#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include "commanddata.h"

using namespace std;

//----------------------------------------------------------------------------
// class command_base
// By: Jonathan Difrancesco 2012
// ABSTRACT CLASS
//
// ADT command_base: Provides an interface for command_base object. 

//
// Assumptions: 
//             -class functions as an interface, inherited member responsible for all output
//
//
//----------------------------------------------------------------------------

class command_base
{
public:
	command_base(); // constructor 
	virtual ~command_base(){} // virtual destructor

	virtual void  initialize(const string) = 0; // initialize array
	virtual CommandData* next(); // get next command
	
private:
};

#endif

