#pragma once
#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include "account.h"

using namespace std; 

//--------------------------  class List  ------------------------------------
// Template BSTree: This container stores objects in a binary search tree
//                  that allows data to be added and displayed 
//           
//          
// Assumptions:  
//    -- Control of <, printing, etc. of NodeData information is in the 
//       NodeData class.  

//    -- The insert allocates memory for a Node, ptr to the data is passed in.
//       is the responsibility of the client. 
//    -- Data passed to the template is properly formatted and can be stored
//       by the data members
//
//----------------------------------------------------------------------------


class BSTree {
	
public:
	BSTree();
	~BSTree();

	// insert object into the tree, parameter holds pointer to object to insert
	bool insert(Account*);

	// retrieve object, first parameter is object to retrieve
	// second parameter holds pointer to found object, NULL if not found
	bool retrieve(const Account& , Account*&)const;
	bool display()const; //displays the contents of a tree
	void makeEmpty(); //empties the current tree
	bool isEmpty()const; //returns true if tree is empty

private:
	struct Node{ //glue that holds data properly
		Account* data;
		Node* right;
		Node* left;
	};

	Node* root; // root of the tree

	void makeEmptyHelper(Node*);
	void displayHelper(Node*)const;
	void retrieveHelper(Node*, const Account&, Account *&)const;
};

#endif

