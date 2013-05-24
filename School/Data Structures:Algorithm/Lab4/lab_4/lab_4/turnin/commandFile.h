#pragma once
#ifndef COMMANDFILE_H
#define COMMANDFILE_H
#include "command_base.h"
#include "commanddata.h"
#include <string>
#include <queue>
#include <iostream>

using namespace std;
using std::string;

class commandFile : public command_base
{
public:
	commandFile();
	virtual ~commandFile();

	void initialize(const string);
    CommandData* next();

private:
	queue<CommandData> Q; 
};


#endif

// derived_constructor_name (parameters) : base_constructor_name (parameters) {...}