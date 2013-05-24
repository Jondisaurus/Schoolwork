

#pragma once
#ifndef BINTREE_H
#define BINTREE_H

#include "nodedata.h"
#include <iostream>

using namespace std; 


//----------------------------------------------------------------------------
// class BinTree
// By: Jonathan Difrancesco 2012
//
// ADT BinTree: Stores and outputs a binary search tree that can be accessed 
//              and modified via various overloaded operators. Data is stored
//              within using NodeData structures retrieved from the nodedata class.
//              By using the data memebers it is possible to reform a list into a 
//              balanced search tree by using a seperate array. 
//
// Assumptions: 
//               -Enough memory is available for all tasks
//               -Data passed will be valid string opjects
//               -Data passed will be able to be easily sorted and contain
//                 more than one set of data
//               -Data will only be stored once with additional data discarded
//
//
//----------------------------------------------------------------------------



class BinTree 
{

   friend ostream & operator<<(ostream &, BinTree &); //output operator

public:


	BinTree(); // constructor
	BinTree(const BinTree &); // copy constructor
	~BinTree(); // destructor, calls makeEmpty
	bool isEmpty() const; // true if tree is empty, otherwise false
	void makeEmpty(); // make the tree empty so isEmpty returns true
	BinTree& operator=(const BinTree &); //equivilence operator
	bool operator==(const BinTree &); //check to see if two trees are equal
	bool operator!=(const BinTree &); // checks to see if two trees are not equal
	bool insert(NodeData*);  //inserts data into the tree
	bool retrieve(const NodeData&, NodeData *&) const; //retrieves a pointer to data contained within the tree
	void displaySideways() const; // provided, displays the tree sideways
	int getDepth( NodeData &); //retrieves the depth of the pointed data
	void bstreeToArray(NodeData* []); //copies the data in the tree to an array
	void arrayToBSTree(NodeData* []); //copies data from an array into the tree


private:
	struct Node {
		NodeData* data; // pointer to data object
		Node* left; // left subtree pointer
		Node* right; // right subtree pointer
	};
	Node* root; // root of the tree
	// utility functions
	void inorderHelper(ostream &, Node*); //helper method for << operator
	void sideways(Node*, int) const; // provided, helper for displaySideways()
	void makeEmptyHelper(Node*); //helper method for makeempty
	void copy(const BinTree&); //copies the data from a sourch into the current tree
	void copyHelper(Node*&, Node*); //helper method for copy
	bool equalHelper(Node*, Node*); //helper method for the == operator
	void retrieveHelper(Node*, const NodeData& , NodeData *&)const; //helper class for the retrieve operator
	void getDepthHelper(Node*, NodeData, int, int&); //helper method for the getDepth method
	void bstreeArrayHelper(Node*, NodeData*[], int&); //helper method for the bstreeArray method
	struct Node* arrayToBSTreeHelper( int, int, NodeData*[]); //helper method for the arrayToBsTree method

};

#endif



