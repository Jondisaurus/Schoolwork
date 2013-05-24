////////////////////////////////  list.h file  ///////////////////////////////
// Linked list template

#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <fstream>
using namespace std;

//--------------------------  class List  ------------------------------------
// Template list: This container is passed dataNodes by filestream and stores
//                them in a linked list where they can be removed, retrieved,
//                and combined together. 
//           
//          
// Assumptions:  
//    -- Control of <, printing, etc. of NodeData information is in the 
//       NodeData class.  
//    -- There is no dummy head node, head points to first node.  
//       If the list is empty, head is NULL.
//    -- The insert allocates memory for a Node, ptr to the data is passed in.
//       is the responsibility of the client. 
//    -- Data passed to the template is properly formatted and can be stored
//       by the data members
//
//----------------------------------------------------------------------------

template <typename NodeData> 
class List {

	//----------------------------------------------------------------------------
	// operator<<	 
	// output operator for class List, print data, 
	// responsibility for output is left to object stored in the list
	// (this function was given by the sample linkedlist  file)
	friend ostream& operator<< (ostream &output, const List<NodeData>& theList) {
        Node* current;
        current = theList.head;
        while (current != NULL) {
            output << *current->data;
            current=current->next;
        }
        return output;
    }

public:
   List();                                     // default constructor
   ~List();                                 // destructor
   List(const List&);                       // copy constructor
   bool insert(NodeData*);                     // insert one Node into list
   bool isEmpty() const;                       // is list empty?
   void buildList(ifstream&);                 // build a list from datafile
   List operator=(const List&);
   
   void makeEmpty(); 
   bool remove(const NodeData&, NodeData*&);
   bool retrieve(const NodeData&, NodeData*&);
   void merge(List&, List&);
   void intersect(List&, List&);
   bool operator==(const List&);
   bool operator!=(const List&);


private:
   bool copy(const List&);

   struct Node {              // the node in a linked list
      NodeData* data;         // pointer to actual data, operations in NodeData
      Node* next;
   };

   Node* head;                                 // pointer to first node in list
};

//----------------------------------------------------------------------------
// Constructor 
template <typename NodeData> 
List<NodeData>::List() 
{
   head = NULL;
}

//----------------------------------------------------------------------------
// Destructor
template <typename NodeData> 
List<NodeData>::~List()
{
	makeEmpty(); 
}


//----------------------------------------------------------------------------
// Copy Constructor 
template <typename NodeData> 
List<NodeData>::List(const List<NodeData>& source)
{
	head = NULL;
	copy(source);
}

//----------------------------------------------------------------------------
// insert 
// insert an item into list; operator< of the NodeData class
// has the responsibility for the sorting criteria
// (this was included in the original sample list) 
template <typename NodeData> 
bool List<NodeData>::insert(NodeData* dataptr) {                    

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
// isEmpty 
// check to see if List is empty
template <typename NodeData> 
bool List<NodeData>::isEmpty() const {
   return head == NULL;
}

//----------------------------------------------------------------------------
// buildList 
// continually insert new items into the list
template <typename NodeData> 
void List<NodeData>::buildList(ifstream& infile) {
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
// = Operator
// This copies the contents into this instance if not sent this instance. Returns
// a pointer to this instance. 
template <typename NodeData> 
List<NodeData> List<NodeData>::operator=(const List<NodeData>& source)
{
	if(source.head != head)
		copy(source);
	return *this;
}

//----------------------------------------------------------------------------
// Make Empty
// This removes everything from the list and sets the head to NULL. 
template <typename NodeData> 
void List<NodeData>::makeEmpty()
{
	Node* current = head;

	while(current != NULL)
	{
		Node* next = current->next;
		if(current->data != NULL)
			delete current->data; 
		delete current;
		current = next;
	}

	head = NULL;
}

//----------------------------------------------------------------------------
// Remove
// This is sent a target data node which if found is sent back to the function.
// If it is not found: a null value is passed and false is returned. 
template <typename NodeData> 
bool List<NodeData>::remove(const NodeData& target, NodeData*& found)
{
	Node* current = head->next;
	Node* previous = head;

	if(previous == NULL)
	{
		found = NULL;
		return false;
	}

	if(*previous->data == target)
	{
		found = previous->data;

		head = current;
		delete previous;

		return true;
	}

	while(current != NULL)
	{
		if(*current->data == target)
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
// This serches the list for the target data node and if found returns a pointer
// to that data. If it is not found it passes a null value and returns false. 
template <typename NodeData> 
bool List<NodeData>::retrieve(const NodeData& target, NodeData*& found)
{
	Node* current = head->next;
	Node* previous = head;

	if(previous == NULL)
	{
		found = NULL;
		return false;
	}

	if(*previous->data == target)
	{
		found = previous->data;
	    return true;
	}

	while(current != NULL)
	{
		if(*current->data == target)
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
// Merge 
// This combines and copies the passed data into the current instance. If the
// instance is not empty or one of the data nodes it is emptied. 
template <typename NodeData> 
void List<NodeData>::merge(List<NodeData>& src1, List<NodeData>& src2)
{
	if(src1.head != head && src2.head != head && head != NULL)  
		makeEmpty();

	Node* source1 = src1.head;
	Node* source2 = src2.head; 
	
	if(source2 == NULL || ((source1 != NULL) && *source1->data < *source2->data))
	{
		head = new Node;
		*head = *source1;
		source1 = source1->next;
	}
	else
	{
		head = new Node;
		*head = *source2;
		source2 = source2->next;
	}

	Node* ptr = head;

	//this builds and sorts the list while the source1 and source2 files aren't empty 
	while(source1 != NULL && source2 != NULL)
	{
		if(*source1->data < *source2->data)
		{
			ptr->next = source1;
			source1 = source1->next;
		}
		else 
		{
			ptr->next = source2; 
			source2 = source2->next;
		}
		ptr = ptr->next; 
	}

	//appends the end of the array if more data is in source1
	while(source1 != NULL)
	{
		ptr->next = source1;
		source1 = source1->next;
		ptr = ptr->next;
	}

	//appends the end of the array if more data is in source2
	while(source2 != NULL)
	{
		ptr->next = source2;
		source2 = source2->next;
		ptr = ptr->next;
	}

	if(src1.head != head)
		src1.head = NULL;
	if(src2.head != head)
		src2.head = NULL; 


}

//----------------------------------------------------------------------------
// intersect
// this serches the two passed arrays for similar data and inserts them into the 
// instance as they are found. 
template <typename NodeData> 
void List<NodeData>::intersect( List<NodeData>& src1, List<NodeData>& src2)
{
	Node* source1 = src1.head;
	Node* source2 = src2.head; 
	Node* src2HeadPtr = src2.head;

	List temp;
	
	if(source2 == NULL || source1 == NULL) 
		return;

    if(src1 == *this)
	{
		List temp1 = *this;
		makeEmpty();
		source1 = temp1.head;

	}
	if(src2 == *this)
	{
		List temp2 = *this;
		makeEmpty();
		source2 = temp2.head;
	}
	

	while(source1 != NULL)
	{
		while(source2 != NULL)
		{
			if(*source2->data == *source1->data)
			{
				temp.insert(source2->data);
			}
			source2 = source2->next; 
		}
		source2 = src2HeadPtr;
		source1 = source1->next; 
	}

	copy(temp);
}

//----------------------------------------------------------------------------
// operator==
// this compares the two arrays and returns whether they contain identical data 
template <typename NodeData> 
bool List<NodeData>::operator==(const List<NodeData>& source)
{
	if(head == source.head) 
		return true; 

	Node* ptr1 = head;
	Node* ptr2 = source.head;

	while(ptr1 != NULL && ptr2 != NULL) 
	{
		if(*ptr1->data != *ptr2->data)
			return false; 

		ptr1 = ptr1->next;
		ptr2 = ptr2->next; 
	}

	if((ptr1 == NULL) != (ptr2 == NULL)) return false;
    return true; 
}


//----------------------------------------------------------------------------
// operator!=
// this compares the two arrays and returns if they do not contain indentical data
template <typename NodeData> 
bool List<NodeData>::operator!=(const List<NodeData>& source)
{
	return !(List<NodeData>::operator==(source));
}

//----------------------------------------------------------------------------
// Copy 
// PRIVATE
// This function is sent a list object and copies the data into the current instance
template <typename NodeData> 
bool List<NodeData>::copy(const List<NodeData>& source)
{
	if(head != NULL)
	{
		makeEmpty(); 
	}
	
    head = new Node;
	if(head == NULL) 
		return false;  //out of memory 

	Node* read = source.head;
	if(read == NULL)
		return true; 

	Node* current = head;

	//Scans through the data and copies into the instance
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
	return true;
}

#endif

