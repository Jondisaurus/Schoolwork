#ifndef INTSET_H
#define INTSET_H

#include <iostream>
using namespace std;

//----------------------------------------------------------------------------
// class IntSet
// By: Jonathan Difrancesco 2011
//
// ADT IntSet: Stores an set of non-negative int values in a dynamic bool array
//             that can be modified and outputted through various operators
//
// Assumptions: 
//               -Data passed will be non-negative
//               -Data passed will consist only of char values
//               -Set is assumed to have contain numbers higher than 0
//                  but can perform most functionality with a set containing just 0 
//
//----------------------------------------------------------------------------

class IntSet
{
	friend ostream& operator<<(ostream &, const IntSet &);
	friend istream& operator>>(istream &, IntSet &);

public:
	IntSet(int = -1, int = -1, int = -1, int = -1, int = -1);		// Constructor
	IntSet(const IntSet &);											// Copy Constructor
	~IntSet();														// Destructor

	IntSet operator=(const IntSet&);								// Assign IntSet
	bool operator==(const IntSet&) const;							// Returns whether two intsets are equal
	bool operator!=(const IntSet&) const;							// Returns whether two intsets are not equal
	IntSet operator+(const IntSet&) const;							// Returns the union of two sets
	IntSet operator-(const IntSet&) const;							// Returns the difference of two sets
	IntSet operator*(const IntSet&) const;							// Returns the intersection of two sets
	IntSet operator+=(const IntSet&);                               // Returns the union of two sets, assigned to the left
	IntSet operator-=(const IntSet&);                               // Returns the difference of two sets, assigned to the left
	IntSet operator*=(const IntSet&);								// Returns the intersection of two sets, assigned to the left

	int getSize() const;											// Returns size of the IntSet
	bool insert(int);                                               // Inserts a new item into the IntSet
	bool remove(int);												// Removes an item from the IntSet if found
	bool isEmpty();													// Checks to see if the IntSet is empty
	bool isInSet(int);												// Checks to see if an int is in the set

private:
	bool* IntPtr;													// Pointer to first element in the int Array
	int size;														// Size of the set
};


#endif