#pragma once
#ifndef BSTREE_H
#define BSTREE_H

#include <iostream>
#include "account.h"

using namespace std; 

//--------------------------  class BSTree  ------------------------------------
// class BSTree: This container stores objects in a binary search tree.
//               Can be used to display and retrieve data.
//           
//          
// Assumptions:  
//    -- Control of <, printing, etc. of Account information is in the 
//       Account class.  
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

