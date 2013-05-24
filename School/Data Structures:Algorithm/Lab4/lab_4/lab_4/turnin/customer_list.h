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

class customer_list : public customer_base
{
public:
	customer_list();
	virtual ~customer_list();

	void initialize(const string); 
	cust* getUser(const int);
	void processUser(const CommandData); 
	void displayUser(const int);

private:
	HashTable T;
};

#endif
