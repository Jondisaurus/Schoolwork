#include "dramadvd.h"

// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for DramaDVD class
DramaDVD::DramaDVD()
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
// Default destructor for DramaDVD class
DramaDVD::~DramaDVD()
{
}

// ---------------------------------------------------------------------------
// buildList
// builds object from file
void DramaDVD::buildList(ifstream& inFile)
{
	inFile.get();
	getline(inFile, director, ',');
	inFile.get();
	getline(inFile, title, ',');
	inFile.get(); 
	inFile >> year;
}

// ---------------------------------------------------------------------------
// checkIn
// decreases number of movies out
void DramaDVD::checkIn()
{
	numOut--;
}

// ---------------------------------------------------------------------------
// checkOut
// increases number of movies out if numOut < total movies
bool DramaDVD::checkOut()
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
bool DramaDVD::operator<(const MediaBase& N) const 
{ 
	if(typeid(*this) != typeid(N))
		return false;


   if (director < static_cast<const DramaDVD&>(N).director) 
	   return true;
   else if (director == static_cast<const DramaDVD&>(N).director) 
	   return title < static_cast<const DramaDVD&>(N).title;
   return false; 
};

//-------------------------------  >  ----------------------------------------
// > defined by value of num; if nums equal, ch is used
bool DramaDVD::operator>(const MediaBase& N) const { 

	if(typeid(*this) != typeid(N))
		return false;

   if (director > static_cast<const DramaDVD&>(N).director) 
	   return true;
   else if (director == static_cast<const DramaDVD&>(N).director) 
	   return title > static_cast<const DramaDVD&>(N).title;
   return false;
};

//-------------------------------  ==  ---------------------------------------
// > defined by value of num; if nums equal, ch is used
bool DramaDVD::operator==(const MediaBase& N) const { 

	if(typeid(*this) != typeid(N))
		return false;

	return director == static_cast<const DramaDVD&>(N).director && title == static_cast<const DramaDVD&>(N).title;
};

//-------------------------------  !=  ---------------------------------------
// > defined by value of num; if nums equal, ch is used
bool DramaDVD::operator!=(const MediaBase& N) const { 

	if(typeid(*this) != typeid(N))
		return false;

   return !(*this == static_cast<const DramaDVD&>(N));
};

// ---------------------------------------------------------------------------
// print
// prints contents of object
void DramaDVD::print(ostream& output) const
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
// prints history data formatted for outpu
void DramaDVD::histPrint(ostream& output) const
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
void DramaDVD::set(string titleSrc = " ", string directorSrc = " ", int yearSrc = 0, int monthSrc = 0)
{
	title = titleSrc;
	director = directorSrc;  
}

