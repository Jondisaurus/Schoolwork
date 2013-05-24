#include "bintree.h"

//++===== CPP Cope Behind for the BinTree class contained in bintree.h =======++

// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for BinTree class
BinTree::BinTree()
{
	root = NULL; 
}

// ---------------------------------------------------------------------------
// Copy Constructor
// Copy constructor for BinTree Class 
BinTree::BinTree(const BinTree& source)
{
	root = NULL;
	copy(source);
}

// ---------------------------------------------------------------------------
// Destructor 
// Default destructor for BinTre class 
BinTree::~BinTree()
{
	makeEmpty();
}

//----------------------------------------------------------------------------
// operator<<  
// outputs data from the BinTree with helper method
ostream& operator<<(ostream & output,BinTree & source)
{
	source.inorderHelper(output, source.root);
	output << endl;
	return output;
}

void BinTree::inorderHelper(ostream & output, Node* source)
{
	if(source == NULL)
		return;
	if(source->left != NULL)
		inorderHelper(output, source->left);

	output << *source->data << ' ';

	if(source->right != NULL)
		inorderHelper(output, source->right);
}

//----------------------------------------------------------------------------
// Copy 
// Copies data from source tree into current tree with a helper method
void BinTree::copy(const BinTree& source)
{
	if(source.root == root)
		return;
	makeEmpty();
	copyHelper(root, source.root);
}

void BinTree::copyHelper(Node*& copy, Node* source)
{
	if(source == NULL)
		return;

	copy = new Node;   //create new node to be inserted
	copy->data = new NodeData; 
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
bool BinTree::operator==(const BinTree& source)
{
	return equalHelper(root, source.root);
}

bool BinTree::equalHelper(Node* check, Node* source)
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
bool BinTree::operator!=(const BinTree & source)
{
	return !(operator==(source));
}

//----------------------------------------------------------------------------
// inserts
// inserts one NodeData member into the BS tree
// (Modified version of the lab5 insert from CSS342)
bool BinTree::insert(NodeData* source)
{ 
	Node* ptr = new Node;
    if (ptr == NULL) return false;  //out of memory
	ptr->data = source;
	ptr->left = ptr->right = NULL; 

	if(isEmpty())
	{
		root = ptr;
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
	}
}

// ---------------------------------------------------------------------------
// retrieve 
// Searches for and retrieves a pointer to a desired account from the tree
bool BinTree::retrieve(const NodeData& source, NodeData *& found)const 
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
void BinTree::retrieveHelper(Node* current, const NodeData& source, NodeData *& found)const
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
BinTree& BinTree::operator=(const BinTree & source)
{
	copy(source);
	return *this; 
}



//----------------------------------------------------------------------------
// makeEmpty
// Clears out the tree with help from a helper method
void  BinTree::makeEmpty()
{
	if(root != NULL)
	{
		makeEmptyHelper(root);
		root = NULL;
	}
}

void BinTree::makeEmptyHelper(Node* source)
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
bool BinTree::isEmpty() const
{
	return root == NULL;
}

//----------------------------------------------------------------------------
// getDepth
// Returns the depth of the passed data member through a helper method
int BinTree::getDepth(NodeData& source)
{
	int depth = 0;
	int found = 0;
	getDepthHelper(root, source, depth, found);
	return found;

}

void BinTree::getDepthHelper(Node* ptr, NodeData source, int depth, int& found)
{
	if(*ptr->data == source)
	{ //checks to see if is the data member to be searched for
		found = depth + 1;
		return;
	}
	else
	{
		if(ptr->left != NULL && found == 0)
			getDepthHelper(ptr->left,source,depth + 1, found);
		if(ptr->right != NULL && found == 0)
			getDepthHelper(ptr->right,source,depth + 1, found);
	} 
}

//---------------------------------------------------------------------------
// displaySideways 
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.

void BinTree::displaySideways() const {
   sideways(root, 0);
}

void BinTree::sideways(Node* current, int level) const {
   if (current != NULL) {
      level++;
      sideways(current->right, level);

      // indent for readability, 4 spaces per depth level 
      for(int i = level; i >= 0; i--) {
          cout << "    ";
      }

      cout << *current->data << endl;        // display information of object
      sideways(current->left, level);
   }
}

//---------------------------------------------------------------------------
// bstreeToArray 
// Copies contents of the binary search tree to a sorted array via a helper method
void BinTree::bstreeToArray(NodeData* source[])
{
	int subs = 0;
	bstreeArrayHelper(root, source, subs);
	makeEmpty();
}

void BinTree::bstreeArrayHelper(Node* ptr, NodeData* source[], int& subs)
{
	if(ptr->left != NULL)
		bstreeArrayHelper(ptr->left, source, subs);

	NodeData* arryPtr = new NodeData;

	*arryPtr = *ptr->data;
	source[subs] = arryPtr;
	subs++;

	if(ptr->right != NULL)
		bstreeArrayHelper(ptr->right, source, subs);

}

//---------------------------------------------------------------------------
// arrayToBSTree 
// Copies contents of a sorted array to a balanced binary search tree via
// a helper method
void BinTree::arrayToBSTree(NodeData* source[])
{
	int max = 0;

	while(source[max + 1] != NULL)
		max++;
	if(!isEmpty())
		makeEmpty();

	root = arrayToBSTreeHelper( max, 0, source);

	for(int i = 0; i <= max; i++)
	{
		if(source[i] != NULL)
		{
			source[i] = NULL;
		}
	}
}

BinTree::Node* BinTree::arrayToBSTreeHelper(int max, int min, NodeData* source[])
{
	//if(max == min)
	//{
		//insert(source[max]);
		//return;
	//}
	if(min > max)
		return NULL;

	int mid = (max+min)/2;

	struct Node* ptr = new Node;
	ptr->data = source[mid];

	ptr->left = arrayToBSTreeHelper(mid - 1, min, source);
	
	ptr->right = arrayToBSTreeHelper(max, mid + 1, source);

	return ptr;

}
