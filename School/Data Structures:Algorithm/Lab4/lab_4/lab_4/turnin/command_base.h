#pragma once
#ifndef COMMANDBASE_H
#define COMMANDBASE_H

#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include "commanddata.h"

using namespace std;

class command_base
{
public:
	command_base(); 
	virtual ~command_base(){}

	virtual void  initialize(const string) = 0;
	virtual CommandData* next(); 
	

private:
};

#endif

