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

class Manager
{
public:
	Manager();
	~Manager();

	bool initialize(const string, const string, const string);
	void run();

private:
	command_base* commands;
	customer_base* customers;
	MediaStore* media;
};


#endif
