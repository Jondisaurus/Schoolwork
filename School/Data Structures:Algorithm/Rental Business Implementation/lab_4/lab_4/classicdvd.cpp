#include "classicdvd.h"

// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for ClassicDVD class
ClassicDVD::ClassicDVD()
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
// Default destructor for classicDVD class
ClassicDVD::~ClassicDVD()
{
}

// ---------------------------------------------------------------------------
// buildList
// builds object from file 
void ClassicDVD::buildList(ifstream& inFile)
{
	string help; 

	inFile.get();
	getline(inFile, director, ',');
	inFile.get();
	getline(inFile, title, ',');
	inFile.get();
	getline(inFile, actor, ' ');
	actor.append(" ");
	getline(inFile, help, ' ');
	actor.append(help); 
	inFile >> month >> year;
}

// ---------------------------------------------------------------------------
// checkIn
// decreases number of movies out
void ClassicDVD::checkIn()
{
	numOut--;
}

// ---------------------------------------------------------------------------
// checkOut
// increases number of movies out if numOut < total movies
bool ClassicDVD::checkOut()
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

//-------------------------------  <  ----------------------------------------
// < defined by value of num; if nums equal, ch is used
bool ClassicDVD::operator<(const MediaBase& N) const 
{ 
	if(typeid(*this) != typeid(N))
		return false;


   if (year < static_cast<const ClassicDVD&>(N).year) 
	   return true;
   else if (year == static_cast<const ClassicDVD&>(N).year && month < static_cast<const ClassicDVD&>(N).month)
	   return true;
   else if (year == static_cast<const ClassicDVD&>(N).year && month == static_cast<const ClassicDVD&>(N).month) 
	   return actor < static_cast<const ClassicDVD&>(N).actor;
   else return false; 
};

//-------------------------------  >  ----------------------------------------
// > defined by value of num; if nums equal, ch is used
bool ClassicDVD::operator>(const MediaBase& N) const { 

	if(typeid(*this) != typeid(N))
		return false;

   if (year > static_cast<const ClassicDVD&>(N).year) 
	   return true;
   if (year == static_cast<const ClassicDVD&>(N).year && month > static_cast<const ClassicDVD&>(N).month)
	   return true;
   if (year == static_cast<const ClassicDVD&>(N).year && month == static_cast<const ClassicDVD&>(N).month)
	   return actor > static_cast<const ClassicDVD&>(N).actor;
   else return false;
};

//-------------------------------  ==  ---------------------------------------
// > defined by value of num; if nums equal, ch is used
bool ClassicDVD::operator==(const MediaBase& N) const { 

	if(typeid(*this) != typeid(N))
		return false;

	if(static_cast<const ClassicDVD&>(N).title == " " ||
	   static_cast<const ClassicDVD&>(N).title == title)
	{
		return year == static_cast<const ClassicDVD&>(N).year
			   && month == static_cast<const ClassicDVD&>(N).month;
	}


	return year == static_cast<const ClassicDVD&>(N).year
					&& month == static_cast<const ClassicDVD&>(N).month 
					&& actor == static_cast<const ClassicDVD&>(N).actor;
};

//-------------------------------  !=  ---------------------------------------
// > defined by value of num; if nums equal, ch is used
bool ClassicDVD::operator!=(const MediaBase& N) const { 

	if(typeid(*this) != typeid(N))
		return false;

   return !(*this == static_cast<const ClassicDVD&>(N));
};

// ---------------------------------------------------------------------------
// print
// prints contents of object
void ClassicDVD::print(ostream& output) const
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
void ClassicDVD::histPrint(ostream& output) const
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
void ClassicDVD::set(string titleSrc = " ", string actorSrc = " ", int yearSrc = 0, int monthSrc = 0)
{
	title = titleSrc;
	actor = actorSrc; 
	year = yearSrc;
	month = monthSrc; 
}



