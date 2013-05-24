
////////////////////////////////  list.cpp file  /////////////////////////////

#include "list.h"

//----------------------------------------------------------------------------
// Constructor 
List::List() 
{
   head = NULL;
}

//----------------------------------------------------------------------------
// Destructor
List::~List()
{
	Node* current = head;

	while( current != NULL)
	{
		Node* next = current->next;
		delete current;
		current = next;
	}

	head = NULL;
}


//----------------------------------------------------------------------------
// Copy Constructor 
List::List(const List& source)
{
	copy(source);
}


//----------------------------------------------------------------------------
// Copy 
void List::copy(const List& source)
{
	if(head != NULL)
	{
		makeEmpty(); 
	}
	
	head = new Node;

	Node* read = source.head;

	if(read == NULL) return; 

	Node* current = head;

	while(read != NULL)
	{
		current->data = new NodeData;
		*current->data = *read->data;
        
		read = read->next;

		if(read == NULL) 
		{		
			current->next = NULL;
			break;
		}

		Node* ptr = new Node;
		
		current->next = ptr; 
		current = current->next; 	
	}
}

//----------------------------------------------------------------------------
// Remove
bool List::remove(NodeData* target, NodeData* found)
{
	Node* current = head->next;
	Node* previous = head;

	if(previous = NULL)
	{
		found = NULL;
		return false;
	}

	if(previous->data == target)
	{
		found = previous->data;

		head = current;
		delete previous;

		return true;
        
	}

	while(current != NULL)
	{
		if(current->data == target)
		{
			found = current->data;
			
			previous->next = current->next;
			delete current;

			return true;
		}

		previous = current;
		current = current->next;
	}

	found = NULL;
	return false; 
}

//----------------------------------------------------------------------------
// Retreive
bool List::retreive(NodeData* target, NodeData* found)
{

	Node* current = head->next;
	Node* previous = head;

	if(previous = NULL)
	{
		found = NULL;
		return false;
	}

	if(previous->data == target)
	{
		found = previous->data;
	    return true;
	}

	while(current != NULL)
	{
		if(current->data == target)
		{
			found = current->data;
			return true;
		}
		previous = current;
		current = current->next;
	}
	found = NULL;
	return false; 
}



//----------------------------------------------------------------------------
// = Operator
bool List::operator=(const List& source)
{
	copy(source); 
	return true;
}

//----------------------------------------------------------------------------
// Make Empty
void List::makeEmpty()
{
	Node* current = head;

	while(current->next != NULL)
	{
		Node* next = current->next;
		delete current;
		current = next;
	}

	head = NULL;
}



//----------------------------------------------------------------------------
// isEmpty 
// check to see if List is empty
bool List::isEmpty() const {
   return head == NULL;
}

//----------------------------------------------------------------------------
// insert 
// insert an item into list; operator< of the NodeData class
// has the responsibility for the sorting criteria
bool List::insert(NodeData* dataptr) {                    

   Node* ptr= new Node;
   if (ptr == NULL) return false;                 // out of memory, bail
   ptr->data = dataptr;                           // link the node to data

   // if the list is empty or if the node should be inserted before 
   // the first node of the list
   if (isEmpty() || *ptr->data < *head->data) {
      ptr->next = head;                           
      head = ptr;
   }
     
   // then check the rest of the list until we find where it belongs 
   else {
      Node* current = head->next;          // to walk list
      Node* previous = head;               // to walk list, lags behind

      // walk until end of the list or found position to insert
      while (current != NULL && *current->data < *ptr->data) {
            previous = current;                  // walk to next node
            current = current->next;
      }

      // insert new node, link it in
      ptr->next = current; 
      previous->next = ptr; 
   }
   return true;
}

//----------------------------------------------------------------------------
// buildList 
// continually insert new items into the list
void List::buildList(ifstream& infile) {
   NodeData* ptr;
   bool successfulRead;                            // read good data
   bool success;                                   // successfully insert
   for (;;) {
      ptr = new NodeData;
      successfulRead = ptr->setData(infile);       // fill the NodeData object
      if (infile.eof()) {
         delete ptr;
         break;
      }

      // insert good data into the list, otherwise ignore it
      if (successfulRead) {
         success = insert(ptr);
      }
      else {
         delete ptr;
      }
      if (!success) break;
   }
}

//----------------------------------------------------------------------------
// operator<<  
// output operator for class List, print data, 
// responsibility for output is left to object stored in the list
ostream& operator<<(ostream& output, const List& thelist) {

   List::Node* current = thelist.head;
   while (current != NULL) { 
      output << *current->data;
      current = current->next;
   }
   return output;                      // enables output << x << y;
}

