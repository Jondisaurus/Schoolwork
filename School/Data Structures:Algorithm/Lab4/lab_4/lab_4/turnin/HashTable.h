#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include "customerdata.h"

using namespace std;

class HashTable
{
	static const int MAX_BUCKETS = 100;
	static const int HASH_FACTOR = 13;

public:
	HashTable();
	~HashTable();

	bool insert(const cust*);
	bool isEmpty();
	cust*& getCust(const int);

private:
	struct Node
	{
		cust* customerInfo;
		Node* next;
	};

	Node **table;
	
	void clear();
	void clearHelper(Node*);
};

#endif


