#include <iostream>
#include "bstree.h"

// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for BSTree
BSTree::BSTree() 
{
	root = NULL;
};

// ---------------------------------------------------------------------------
// Destructor 
// Default destructor for account class 
BSTree::~BSTree() 
{
	makeEmpty();
}

// ---------------------------------------------------------------------------
// makeEmpty 
// removes all objects from tree
void BSTree::makeEmpty()
{
	if(root != NULL)
	{
		makeEmptyHelper(root);
		root = NULL;
	}
}

// ---------------------------------------------------------------------------
// isEmpty 
// Checks to see if tree is empty
bool BSTree::isEmpty()const
{
	 if(root == NULL) return true;
	 else return false; 
}

// ---------------------------------------------------------------------------
// makeEmptyHelper 
// Recursivly scans through file and deletes data to clear list
void BSTree::makeEmptyHelper(Node* current)
{
	if(current->left != NULL)
		makeEmptyHelper(current->left);
	if(current->right != NULL)
		makeEmptyHelper(current->right);
	delete current->data; 
	delete current;
	current = NULL;
}

// ---------------------------------------------------------------------------
// Insert
// Inserts an account into the tree if possible
bool BSTree::insert(Account* dataptr) 
{
   Node* ptr = new Node;
   if (ptr == NULL) return false; // out of memory
   ptr->data = dataptr;
   ptr->left = ptr->right = NULL;
   if (isEmpty()) {
      root = ptr;
   }
   else {
      Node* current = root;                           // walking pointer
      bool inserted = false;                          // whether inserted yet

      // if item is less than current item, insert in left subtree,
      // otherwise insert in right subtree
      while (!inserted) {
         if (*ptr->data < *current->data) {
            if (current->left == NULL) {              // insert left
               current->left = ptr;
               inserted = true;
            }
            else
               current = current->left;               // one step left
         }
         else {
            if (current->right == NULL) 
			{             // insert right
               current->right = ptr;
               inserted = true;
            } 
            else
               current = current->right;              // one step right
         }
      }
   }

};

// ---------------------------------------------------------------------------
// display
// Displays contents of the tree
bool BSTree::display()const
{
	if(root != NULL)
	{
		displayHelper(root);
		return true;
	}
	else{	
		cout << "\ntree is empty\n";
		return false;
	}
}

// ---------------------------------------------------------------------------
// displayHelper
// Recursivly scans and displays content stored in the tree
void BSTree::displayHelper(Node* source)const
{	
	if(source->left != NULL) 
		displayHelper(source->left); 

	cout << *source->data;

    if(source->right != NULL)
		displayHelper(source->right);
}

// ---------------------------------------------------------------------------
// retrieve 
// Searches for and retrieves a pointer to a desired account from the tree
bool BSTree::retrieve(const Account& source, Account *& found)const 
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
void BSTree::retrieveHelper(Node* current, const Account& source, Account *& found)const
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
