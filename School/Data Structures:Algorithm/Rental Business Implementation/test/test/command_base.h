#pragma once
#ifndef COMMANDBASE_H
#define COMMANDBASE_H

#include <iostream>
#include <queue>
#include <string>

using namespace std;
using std::string;

class CommandData
{
public:
	char action;
	int custID;
	char dataType;
	char movieType;
	int year;
	int month;
	string director;
	string title;
	string actor;
	string other;
};

class command_base
{
public:
	command_base();
	~command_base();
	virtual void  initialize(void) = 0;
	CommandData next();  
	

private:
};



#endif
