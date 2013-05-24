#include "intset.h"

// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for IntSet
IntSet::IntSet(int a, int b, int c, int d, int e)
{
	//initalizes one block to enable accepting sets containing just 0
	IntPtr = new bool[1];
	size = 0;

	if(a >= 0) insert(a);
	if(b >= 0) insert(b);
	if(c >= 0) insert(c);
	if(d >= 0) insert(d);
	if(e >= 0) insert(e);
}

// ---------------------------------------------------------------------------
// Copy Constructor 
// Copy constructor for IntSet
IntSet::IntSet(const IntSet& toCopy)
{
	if(toCopy.size > 0)
	{
		size = toCopy.size;
		IntPtr = new bool[size + 1];

		for(int i = 0; i <= size; i++)
		{
			if(toCopy.IntPtr[i] == true)
				IntPtr[i] = true;
			else IntPtr[i] = false;
		}	
	}
	else  //Initializes one block in case of array with 0 == true
	{
		size = 0;
		IntPtr = new bool[1];
	}
}

// ---------------------------------------------------------------------------
// Destructor 
// Destructor for IntSet
IntSet::~IntSet()
{
	delete  [] IntPtr;
	IntPtr = NULL;
}

// ---------------------------------------------------------------------------
// '<<' Operator
// Outputs the data using the << operator
ostream& operator<<(ostream& output, const IntSet& pass)
{
	output << '{';

	for(int i = 0; i <= pass.size; i++)
	{
		if(pass.IntPtr[i] == true) 
			output << ' ' << i;
	}

	output << '}';

	return output;
}

// ---------------------------------------------------------------------------
// '>>' Operator
// Inputs the data using the >> operator until a value <1 is entered
istream& operator>>(istream& input, IntSet& pass)
{
	int temp = 0;

	while(temp >=0)
	{
		input >> temp;
		if(temp >= 0) pass.insert(temp);
	}

	return input; 
}

// ---------------------------------------------------------------------------
// '=' Operator
// Sets the IntSet on the left of the operator to be equivilent to the IntSet on the right
IntSet IntSet::operator=(const IntSet& toCopy)
{   
	if(toCopy != *this)
	{
		delete [] IntPtr;
		size = toCopy.size;
		IntPtr = new bool[size + 1];

		for(int i = 0; i <= size; i++)
		{
			if(toCopy.IntPtr[i] == true)
				IntPtr[i] = true;
			else IntPtr[i] = false;
		}
	}
	return *this;
}

// ---------------------------------------------------------------------------
// '==' Operator
// Checks to see if the two intsets are equivilent to each other
bool IntSet::operator==(const IntSet& Right) const
{
	if(size == Right.size)
	{
		for(int i = 0; i <= size; i++)
		{
			if(IntPtr[i] != Right.IntPtr[i]) return false;
		}    
	    return true; 
	}
	else return false;
}

// ---------------------------------------------------------------------------
// '!=' Operator
// Checks to see if the two intsets are not equivilent to each other
bool IntSet::operator!=(const IntSet& Right) const
{
	if(size == Right.size)
	{
		for(int i = 0; i <= size; i++)
		{
			if(IntPtr[i] != Right.IntPtr[i]) return true;
		}
	    
	    return false; 
	}
	else return true;
}

// ---------------------------------------------------------------------------
// '+' Operator
// Returns the union of the two sets 
IntSet IntSet::operator+(const IntSet& add) const
{
	IntSet copy = *this;

    for(int i = 0; i <= add.size ; i++)
	{
		if(add.IntPtr[i] == true) 
			copy.insert(i);
	}

	return copy;
}

// ---------------------------------------------------------------------------
// '-' Operator
// Returns the difference of the two sets 
IntSet IntSet::operator-(const IntSet& sub) const
{
	IntSet copy = *this;

    for(int i = 0; i <= sub.size ; i++)
	{
		if(sub.IntPtr[i] == true) 
			copy.remove(i);
	}

	return copy;
}

// ---------------------------------------------------------------------------
// '*' Operator
// Returns the intersection of the two sets 
IntSet IntSet::operator*(const IntSet& isc) const
{
	IntSet copy = *this;

    for(int i = 0; i <= size ; i++)
	{
		if(!(isc.IntPtr[i] == true && copy.IntPtr[i] == true)) 
			copy.remove(i);
	}

	return copy;
}


// ---------------------------------------------------------------------------
// '+=' Operator
// Assigns the union of the two sets 
IntSet IntSet::operator+=(const IntSet& pass)
{
	IntSet::operator=(IntSet::operator+(pass)); 
	return *this;
}

// ---------------------------------------------------------------------------
// '-=' Operator
// Assigns the difference of the two sets 
IntSet IntSet::operator-=(const IntSet& pass)
{
	IntSet::operator=(IntSet::operator-(pass));
	return *this;
}

// ---------------------------------------------------------------------------
// '*=' Operator
// Assigns the union of the two sets 
IntSet IntSet::operator*=(const IntSet& pass)
{
	IntSet::operator=(IntSet::operator*(pass));
	return *this;
}

// ---------------------------------------------------------------------------
// Insert
// Inserts an int into the array if valid
bool IntSet::insert(int num)
{
	// Resizes the set if needed
	if(num > size)
	{
		IntSet temp = *this;
		delete [] IntPtr;
		IntPtr = new bool[num + 1];

		for(int i = 0; i <= num; i++)
		{
			// This reinitializes the array without potentielly stepping out of bounds
			if(i <= size && size > 0)
			{ 
				if(temp.IntPtr[i] == true)
					IntPtr[i] = true;
				else IntPtr[i] = false;
			}
			else IntPtr[i] = false;
		}
		size = num;	
	}
	
	// Adds number to set
	if(num >= 0)
	{
		IntPtr[num] = true;
		return true;
	}
	else return false;
}

// ---------------------------------------------------------------------------
// Remove
// Attempts to remove an int from the array
// Returns true if the num is not in the array, false if the input is invalid
bool IntSet::remove(int num)
{		
	// Removes number from the set
	if(num > 0)
	{
		if(isInSet(num))
		{	
		   IntPtr[num] = false;		   
		}

		return true;
	}
	else return false;
}

// ---------------------------------------------------------------------------
// isEmpty
// Checks if the IntSet is empty
bool IntSet::isEmpty()
{
	if(size == 0 && !isInSet(0)) return true;
	else return false;
}

// ---------------------------------------------------------------------------
// isInSet
// Checks if the passed number is in the set
bool IntSet::isInSet(int num)
{
	if(num <= size && num >= 0 && IntPtr[num] == true) return true;
	else return false;
}

