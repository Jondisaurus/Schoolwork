#pragma once
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include "customerdata.h"

using namespace std;

//----------------------------------------------------------------------------
// class HashTalbe
// By: Jonathan Difrancesco 2012
//
// ADT HashTable
//               Handles data storage for cust objects. Objects are stored
//               in chained hashed keys that handle collisions.
//
// Assumptions: 
//             -All data contained is properly formatted
//
//
//----------------------------------------------------------------------------

class HashTable
{
	static const int MAX_BUCKETS = 100;
	static const int HASH_FACTOR = 13;

public:
	HashTable(); //default constructor
	~HashTable(); //default destructor

	bool insert(const cust*); //insert object into hash table
	bool isEmpty(); //checks to see if talbe is empty
	cust*& getCust(const int); //gets customer object from table if found

private:
	struct Node //Node object for chaining members
	{
		cust* customerInfo;
		Node* next;
	};

	Node **table; //table that holds the hash objects for the table
	
	void clear(); //empty table
	void clearHelper(Node*); //assists in clearing out chained objects
};

#endif


