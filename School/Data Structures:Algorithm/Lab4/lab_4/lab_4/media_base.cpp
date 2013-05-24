#include "media_base.h"

// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for MediaBase class
MediaBase::MediaBase()
{
	type = ' ';
	actor = " ";
	title = ' ';
	director = ' ';
	month = 0;
	year = 0;
	total_copies = 10;
	numOut = 0;
}

// ---------------------------------------------------------------------------
// addDupe
// if a duplicate object is found, it is added to the total copies available
void MediaBase::addDupe()
{
	total_copies++;
}

//-------------------------------  >  ----------------------------------------
// > returns if object is less than N
bool MediaBase::operator<(const MediaBase& N) const
{ 
	if(typeid(*this) != typeid(N))
		return false;

	return type == N.type; 
}

//-------------------------------  <  ----------------------------------------
// < returns if object is greater than N
bool MediaBase::operator>(const MediaBase& N) const
{
	if(typeid(*this) != typeid(N))
		return false;

	return type == N.type;
}

//-------------------------------  ==  ---------------------------------------
// == returns if the two objects are equivelent
 bool MediaBase::operator==(const MediaBase& N) const
{
	if(typeid(*this) != typeid(N))
		return false;

	return type == N.type;
}

//-------------------------------  !=  ---------------------------------------
// != returns if two operations are inequivilent
bool MediaBase::operator!=(const MediaBase& N) const
{
	if(typeid(*this) != typeid(N))
		return false;

	return type == N.type;
}

// ---------------------------------------------------------------------------
// print
// prints contents of object
void MediaBase::print(ostream& output) const
{
	output << setw(3) << (total_copies - numOut) << "   " << left << setw(5) << numOut
	      << setw(20) << title << setw(15) << director << right 
		  << setw(6) << year << setw(3) << month << "  " << actor
		  << "\n";
}


