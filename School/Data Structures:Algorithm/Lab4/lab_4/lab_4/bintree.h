#pragma once
#ifndef BINTREE_H
#define BINTREE_H

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


template <typename T>
class BinTree 
{
public:
	
	friend ostream & operator<<(ostream & output, BinTree<T>& source) //output operator
    {
	  source.inorderHelper(output, source.root);
	  return output;
    }

	BinTree(); // constructor
	BinTree(const BinTree &); // copy constructor
	~BinTree(); // destructor, calls makeEmpty
	bool isEmpty() const; // true if tree is empty, otherwise false
	void makeEmpty(); // make the tree empty so isEmpty returns true
	BinTree& operator=(const BinTree &); //equivilence operator
	bool operator==(const BinTree &); //check to see if two trees are equal
	bool operator!=(const BinTree &); // checks to see if two trees are not equal
	bool insert(T*);  //inserts data into the tree
	bool retrieve(const T&, T *&) const; //retrieves a pointer to data contained within the tree


private:
	struct Node {
		T* data; // pointer to data object
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
	void retrieveHelper(Node*, const T& , T *&)const; //helper class for the retrieve operator	

};

// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for BinTree class
template <typename T>
BinTree<T>::BinTree()
{
	root = NULL; 
}

// ---------------------------------------------------------------------------
// Copy Constructor
// Copy constructor for BinTree Class
template <typename T>
BinTree<T>::BinTree(const BinTree<T>& source)
{
	root = NULL;
	copy(source);
}

// ---------------------------------------------------------------------------
// Destructor 
// Default destructor for BinTree class
template <typename T>
BinTree<T>::~BinTree()
{
	makeEmpty();
}

//----------------------------------------------------------------------------
// operator<<  
// outputs data from the BinTree with helper method
/*ostream& operator<<(ostream & output, BinTree<T> & source)
{
	source.inorderHelper(output, source.root);
	output << endl;
	return output;
}*/

template <typename T>
void BinTree<T>::inorderHelper(ostream & output, Node* source)
{
	if(source == NULL)
		return;
	if(source->left != NULL)
		inorderHelper(output, source->left);

	source->data->print(output); 

	//output << *source->data << ' ';

	if(source->right != NULL)
		inorderHelper(output, source->right);
}

//----------------------------------------------------------------------------
// Copy 
// Copies data from source tree into current tree with a helper method
template <typename T>
void BinTree<T>::copy(const BinTree<T>& source)
{
	if(source.root == root)
		return;
	makeEmpty();
	copyHelper(root, source.root);
}

template <typename T>
void BinTree<T>::copyHelper(Node*& copy, Node* source)
{
	if(source == NULL)
		return;

	copy = new Node;   //create new node to be inserted
	copy->data = new T; 
	copy->left = copy->right = NULL;

	*copy->data = *source->data;  //copy data into new node

	if(source->right != NULL)
		copyHelper(copy->right, source->right);
	if(source->left != NULL)
		copyHelper(copy->left, source->left);
}

//----------------------------------------------------------------------------
// == Operator
// check to see if two trees are equal in content and stucture by use of a helper method
template <typename T>
bool BinTree<T>::operator==(const BinTree<T>& source)
{
	return equalHelper(root, source.root);
}

template <typename T>
bool BinTree<T>::equalHelper(Node* check, Node* source)
{
	if(check == NULL && source == NULL)
		return true;
	else if(check == NULL && source != NULL)
		return false;
	else if(check != NULL && source == NULL)
		return false;
	else if(*check->data == *source->data &&
		    equalHelper(check->left, source->left) &&
		    equalHelper(check->right, source->right))
		return true;
	else return false;  
}

//----------------------------------------------------------------------------
// != Operator
// Returns the opposite of the == operator
template <typename T>
bool BinTree<T>::operator!=(const BinTree<T> & source)
{
	return !(operator==(source));
}

//----------------------------------------------------------------------------
// inserts
// inserts one NodeData member into the BS tree
// (Modified version of the lab5 insert from CSS342)
template <typename T>
bool BinTree<T>::insert(T* source)
{ 
	Node* ptr = new Node;
    if (ptr == NULL) return false;  //out of memory
	//ptr->data = new T; 
	ptr->data = source;
	ptr->left = ptr->right = NULL; 

	if(isEmpty())
	{
		root = ptr;
		return true;
	}
	else
	{ 
		Node* current = root;                           // walking pointer
        bool inserted = false;                          // whether inserted yet

        while (!inserted) 
	    {
           if (*ptr->data < *current->data) 
		   {
              if (current->left == NULL) 
		   	  {              // insert left
                 current->left = ptr;
                 inserted = true;
				 return true;
              }
              else
                 current = current->left;               // one step left
           }

		   else if(*ptr->data == *current->data)
		   {
				delete ptr;
				return false; 
		   }

           else
		   {
              if (current->right == NULL) 
			  {             // insert right
                 current->right = ptr;
                 inserted = true;
				 return true;
              } 
              else
                 current = current->right;              // one step right
           } 

	   }

		return false; 
	}
}

// ---------------------------------------------------------------------------
// retrieve 
// Searches for and retrieves a pointer to a desired account from the tree
template <typename T>
bool BinTree<T>::retrieve(const T& source, T *& found)const 
{
	found = NULL; 
	retrieveHelper(root, source, found);

	if(found == NULL)
		return false;
	else return true; 
	
};

// ---------------------------------------------------------------------------
// retrieveHelper
// Recursivly searches for an item and returns a pointer to it's location in the tree
template <typename T>
void BinTree<T>::retrieveHelper(Node* current, const T& source, T *& found)const
{
	if(found != NULL || current == NULL)
		return; 
	if(*current->data == source) 
	{
		found = current->data;
		return;
	}
	if((current->left != NULL) && source < *current->data)
		retrieveHelper(current->left, source, found);
	if((current->right != NULL) && source > *current->data)
		retrieveHelper(current->right, source, found);
};


// ---------------------------------------------------------------------------
// = operator
// copies the passed BinTree into the current BinTree
template <typename T>
BinTree<T>& BinTree<T>::operator=(const BinTree<T> & source)
{
	copy(source);
	return *this; 
}



//----------------------------------------------------------------------------
// makeEmpty
// Clears out the tree with help from a helper method
template <typename T>
void  BinTree<T>::makeEmpty()
{
	if(root != NULL)
	{
		makeEmptyHelper(root);
		root = NULL;
	}
}

template <typename T>
void BinTree<T>::makeEmptyHelper(Node* source)
{
	if(source->left != NULL)
		makeEmptyHelper(source->left);
	if(source->right != NULL)
		makeEmptyHelper(source->right);
	delete source->data; 
	delete source;
	source = NULL;
}

//----------------------------------------------------------------------------
// isEmpty
// Checks to see if the current tree is empty
template <typename T>
bool BinTree<T>::isEmpty() const
{
	return root == NULL;
};


#endif



