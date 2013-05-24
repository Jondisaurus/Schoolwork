#pragma once
#ifndef CUSTOMER_BASE_H
#define CUSTOMER_BASE_H

#include "command_base.h"
#include "customerdata.h"
#include "commanddata.h"
#include <iostream>
#include <list>

using namespace std;

class customer_base
{
public:
	customer_base();
	virtual ~customer_base(){}

	virtual void initialize(const string) = 0; 
	virtual cust* getUser(const int) = 0;
	virtual void processUser(const CommandData) = 0; 
	virtual void displayUser(const int) = 0;
};

#endif
