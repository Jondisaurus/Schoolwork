#include "comedydvd.h"

// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for ComedyDVD class
ComedyDVD::ComedyDVD()
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
// Destructor 
// Default destructor for ComedyDVD class
ComedyDVD::~ComedyDVD()
{
}

// ---------------------------------------------------------------------------
// checkIn
// decreases number of movies out
void ComedyDVD::checkIn()
{
	numOut--;
}

// ---------------------------------------------------------------------------
// checkOut
// increases number of movies out if numOut < total movies
bool ComedyDVD::checkOut()
{
	if(numOut < total_copies)
	{
		numOut++;
		return true;
	}
	else 
	{
		cout << "\nNo more copies of " << title << " remain.";
		return false;
	}
}

// ---------------------------------------------------------------------------
// buildList
// builds object from file 
void ComedyDVD::buildList(ifstream& inFile)
{
	inFile.get();
	getline(inFile, director, ',');
	inFile.get();
	getline(inFile, title, ',');
	inFile.get();
	inFile  >> year;
}

//-------------------------------  >  ----------------------------------------
// > returns if object is less than Ned
bool ComedyDVD::operator<(const MediaBase& N) const 
{ 
	if(typeid(*this) != typeid(N))
		return false;


   if (title < static_cast<const ComedyDVD&>(N).title) 
	   return true;
   else if (title == static_cast<const ComedyDVD&>(N).title)
	   return  year < static_cast<const ComedyDVD&>(N).year;
   return false; 
};

//-------------------------------  <  ----------------------------------------
// < returns if object is greater than N
bool ComedyDVD::operator>(const MediaBase& N) const { 

	if(typeid(*this) != typeid(N))
		return false;

   if (title > static_cast<const ComedyDVD&>(N).title) 
	   return true;
   else if (title == static_cast<const ComedyDVD&>(N).title)
	   return  year > static_cast<const ComedyDVD&>(N).year;
   return false;
};

//-------------------------------  ==  ---------------------------------------
// == returns if the two objects are equivelent
bool ComedyDVD::operator==(const MediaBase& N) const { 

	if(typeid(*this) != typeid(N))
		return false;

	return title == static_cast<const ComedyDVD&>(N).title 
					&& year == static_cast<const ComedyDVD&>(N).year; 
}				

//-------------------------------  !=  ---------------------------------------
// != returns if two operations are inequivilent
bool ComedyDVD::operator!=(const MediaBase& N) const { 

	if(typeid(*this) != typeid(N))
		return false;

   return !(*this == static_cast<const ComedyDVD&>(N));
};

// ---------------------------------------------------------------------------
// print
// prints contents of object
void ComedyDVD::print(ostream& output) const
{
	string titleOut;
	titleOut.assign(title, 0, 18);

	output << left << setw(5) << (total_copies - numOut) << setw(5) << numOut << left
	      << setw(20) << titleOut << setw(18) << director << right 
		  << setw(6) << month << setw(6) << year  << "  " << actor
		  << "\n";
}

// ---------------------------------------------------------------------------
// histPrint
// prints history data formatted for output
void ComedyDVD::histPrint(ostream& output) const
{
	string titleOut;
	titleOut.assign(title, 0, 18);

	output << left << setw(20) << titleOut << setw(18) << director << right 
		   << setw(6) << month << setw(6) << year  << "  " << actor
		   << "\n";
}

// ---------------------------------------------------------------------------
// set
// sets data for retrieve operation
void ComedyDVD::set(string titleSrc, string str, int yearSrc, int monthSrc)
{
	title = titleSrc;
	year = yearSrc;
	month = monthSrc; 
}

