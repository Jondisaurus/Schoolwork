#include "intset.h"

// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for IntSet
IntSet::IntSet(int a, int b, int c, int d, int e)
{
	IntPtr = new bool[0];
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
	
	size = toCopy.size;
	IntPtr = new bool[size + 1];

	for(int i = 0; i <= size; i++)
	{
		IntPtr[i] = toCopy.IntPtr[i];
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
// Outputs the data using the >> operator
istream& operator>>(istream& input, const IntSet& pass)
{
	

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
			IntPtr[i] = toCopy.IntPtr[i];
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
	int max = size;
	IntSet copy = *this;

	if(add.size > max) max = add.size;

    for(int i = 0; i <= max ; i++)
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
	int max = size;
	IntSet copy = *this;

	if(sub.size > max) max = sub.size;

    for(int i = 0; i <= max ; i++)
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
	int max = size;
	IntSet copy = *this;

	if(isc.size > max) max = isc.size;

    for(int i = 0; i <= max ; i++)
	{
		if(!(isc.IntPtr[i] == true && copy.IntPtr[i] == true)) 
			copy.remove(i);
	}

	return copy;
}


// ---------------------------------------------------------------------------
// '+=' Operator
// Returns the union of the two sets 
IntSet IntSet::operator+=(const IntSet& pass)
{
	IntSet::operator=(IntSet::operator+(pass)); 
	return *this;
}

// ---------------------------------------------------------------------------
// '-=' Operator
// Returns the union of the two sets 
IntSet IntSet::operator-=(const IntSet& pass)
{
	IntSet::operator=(IntSet::operator-(pass));
	return *this;
}

// ---------------------------------------------------------------------------
// '*=' Operator
// Returns the union of the two sets 
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
        
		for(int i = 0; i <= size; i++)
		{
			if(temp.IntPtr[i] = true) 
				IntPtr[i] = true;
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
	if(size <= 0) return true;
	else return false;
}

// ---------------------------------------------------------------------------
// isInSet
// Checks if the passed number is in the set
bool IntSet::isInSet(int num)
{
	if(num < size && num > 0 && IntPtr[num] == true) return true;
	else return false;
}