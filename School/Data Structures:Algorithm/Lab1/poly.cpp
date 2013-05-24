#include "poly.h"
#include <iostream>

// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for Poly
Poly::Poly(int a, int b)
{
	if(a == 0 && b < 0)  // no parameters
	{
		pArray = new int[1];
		pArray[0] = 0;
		size = 0;
	}
	else if( a != 0 && b < 0) // one parameter
	{
		pArray = new int[1];
		size = 0;
		pArray[0] = a; 
	}
	else // both parameters
	{
		pArray = new int[b + 1];
		size = b;
		
		for(int i = 0; i <= b; i++)
			pArray[i] = 0;
		
		pArray[b] = a; 
	}
};

// ---------------------------------------------------------------------------
// Copy Constructor 
// Copy constructor for Poly
Poly::Poly(const Poly& source)
{ 
	pArray = new int[source.size + 1];
	size = source.size;

	for(int i = 0; i <= size ; i++)
	{
		if(source.pArray[i] != 0)
			pArray[i] = source.pArray[i];
		else
			pArray[i] = 0;
	}
};

// ---------------------------------------------------------------------------
// Destructor 
// Destructor for Poly
Poly::~Poly()
{
	delete [] pArray;
	pArray = NULL; 
};

// ---------------------------------------------------------------------------
// '>>' Operator
// Inputs the data using the >> operator until two concecutive '0's are entered
istream& operator>>(istream& input, Poly& source)
{
	int coeff = 0;
	int temp = 0;
	
	do
	{
		input >> temp;
		input >> coeff;
		if(coeff > source.size)
			source.resize(coeff);
		if(coeff >= 0 && temp != 0) 
			source.pArray[coeff] = temp;
	}while(temp != 0 || coeff != 0);  //pull input till sentinel values reached

	return input;
};

// ---------------------------------------------------------------------------
// '<<' Operator
// Outputs the stored polynumeral using the << operator
ostream& operator<<(ostream& output, const Poly& source)
{
	for(int i = source.size; i >= 0; i--)
	{
		if(source.pArray[i] != 0)
			output << ' ' <<  ((source.pArray[i] > 0)? "+" : "" ) //Formats to fit exponent values
				   << source.pArray[i] << ((i > 0)? "X" : "" ) << ((i > 1)? "^" : "" );
		if(source.pArray[i] != 0 && i > 1)
			output << i; 
	}
	return output;
};

// ---------------------------------------------------------------------------
// '==' Operator
// Checks to see if the two polynumerals are equivilent to each other
bool Poly::operator==(const Poly& source) const
{
	bool larger = false;
	int minSize = size;

	if(source.size < size)
	{
		minSize = source.size;
		larger = true;
	}

	for(int i = 0; i <= minSize; i++)
	{
		if(pArray[i] != source.pArray[i])
			return false; 
	}

	if(source.size == size)
		return true;

	// If there is a difference in sizes makes sure the larger portion is clear
	else if(larger == true)
	{
		for(int i = minSize + 1; i <= size; i++)
		{
			if(pArray[i] != 0)
				return false;
		}
		return true;  
	}
	else
	{
		for(int i = minSize + 1; i <= source.size; i++)
		{
			if(source.pArray[i] != 0)
				return false;
		}
		return true;
	}
};

// ---------------------------------------------------------------------------
// '!=' Operator
// Checks to see if the two polynumerals are not equivilent to each other
bool Poly::operator!=(const Poly& source) const
{
	return !(Poly::operator==(source));
};

// ---------------------------------------------------------------------------
// '=' Operator
// Sets the polynumeral on the left of the operator to be equivilent to the polynumeral on the right
Poly Poly::operator=(const Poly& source)
 {
	if(source.size > size)
		resize(source.size);
	for(int i = 0; i <= source.size; i ++)
		pArray[i] = source.pArray[i];
	if(size > source.size)
	{
		for(int i = source.size + 1; i <= size; i++)
			pArray[i] = 0;
	}

	return *this; 
};

// ---------------------------------------------------------------------------
// '+=' Operator
// Assigns the sum of the two polynumerals
Poly Poly::operator+=(const Poly& source)
{
	return Poly::operator=(Poly::operator+(source));
};

// ---------------------------------------------------------------------------
// '-=' Operator
// Assigns the difference of the two polynumerals
Poly Poly::operator-=(const Poly& source)
{
	return Poly::operator=(Poly::operator-(source));
};

// ---------------------------------------------------------------------------
// '*=' Operator
// Assigns the product of the two polynumerals
Poly Poly::operator*=(const Poly& source)
{
	return Poly::operator=(Poly::operator*(source));
};

// ---------------------------------------------------------------------------
// '*' Operator
// Returns the product of the two polynumerals
Poly Poly::operator*(const Poly& source) const
{
	Poly temp;

	temp.resize(size + source.size); 

	for(int i = 0; i <= source.size; i++)
	{
		if(source.pArray[i] != 0)
		{
			for(int j = 0; j <= size; j++)
			{
				if(pArray[j] != 0)
				{								
					temp.pArray[j+i] += (pArray[j] * source.pArray[i]);
				}
			}
		}
	}

	return temp; 
};

// ---------------------------------------------------------------------------
// '-' Operator
// Returns the difference of the two polynumerals 
Poly Poly::operator-(const Poly& source) const
{
	Poly temp(*this);

	if(source.size > temp.size)
		temp.resize(source.size);

	for(int i = 0; i <= temp.size; i++)
	{
		if(i > source.size)
			break;
		else
			temp.pArray[i] -= source.pArray[i];			
	}
	return temp;
};

// ---------------------------------------------------------------------------
// '+' Operator
// Returns the difference of the two polynumerals
Poly Poly::operator+(const Poly& source) const
{
	Poly temp(*this);

	if(source.size > temp.size)
		temp.resize(source.size);

	for(int i = 0; i <= temp.size; i++)
	{
		if(i > source.size)
			break;
		else
			temp.pArray[i] += source.pArray[i];			
	}
	return temp;
};

// ---------------------------------------------------------------------------
// setCoeff
// Sets the coefficient passed by parameter 'a' to the variable with exponent 'b'
bool Poly::setCoeff(const int a, const int b)
{
	if(b < 0)
	{
		return false;
	}

	if( b > size)
		resize(b); 

	pArray[b] = a;

	return true; 	
};

// ---------------------------------------------------------------------------
// getCoeff
// gets the coefficient of exponent 'a'
// returns 0 if invalid value is passed
int Poly::getCoeff(const int a) const
{
	if(a > size || a < 0) 
		return 0; 
	else
	{
		return pArray[a]; 
	}
};

// -----------------===PRIVATE===---------------------------------------------
// resize
// resizes the array to the size passed by newSize
void Poly::resize(const int newSize)
{
	if(size >= newSize)
		return;

	int* temp;

	if(size >= 0)
	{
		temp = new int[size + 1];

		for(int i = 0; i <= size; i++)
		{
			temp[i] = pArray[i];
		}
	}

	if(size < 0) //If size is negative, creates a new array to point to. 
	{
		temp = new int[1];
		temp[0] = 0;
	}

	delete [] pArray;
    pArray = new int[newSize + 1];
	
	for(int i = 0; i <= size; i++)
	{
		pArray[i] = temp[i];
	}

	for(int i = size + 1; i <= newSize; i++)
	{
		pArray[i] = 0;
	}

	size = newSize; 

	delete [] temp; //Clears temp from memory
	temp = NULL; 
};
