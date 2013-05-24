#include "classicdvd.h"

ClassicDVD::ClassicDVD()
{
	 type = ' ';
	 actor = " ";
	 title = ' ';
	 director = ' ';
	 month = 0;
	 year = 0;
	 total_copies = 0;
	 numOut = 0;

}

ClassicDVD::~ClassicDVD()
{
}

void ClassicDVD::displayInv(const CommandData src)
{
	if(src.dataType == 'D')
		cout << "DVD ";

	if(src.action == 'B')
		cout << "Borrow   ";
	else if(src.action == 'R')
		cout << "Return   ";

	cout << left << setw(30) << title << setw(20) << director 
		 << setw(6) << year << setw(3) << month << actor;
}

void ClassicDVD::checkIn()
{
	numOut--;
}
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
bool ClassicDVD::operator<(const ClassicDVD& N) const 
{ 
   if (year < N.year) return true;
   if (year == N.year && month < N.month) return true;
   if (year == N.year && month == N.month) return actor < N.actor;
   return false; 
};

//-------------------------------  >  ----------------------------------------
// > defined by value of num; if nums equal, ch is used
bool ClassicDVD::operator>(const ClassicDVD& N) const { 
   if (year > N.year) return true;
   if (year == N.year && month > N.month) return true;
   if (year == N.year && month == N.month) return actor > N.actor;
   return false;
};

//-------------------------------  ==  ---------------------------------------
// > defined by value of num; if nums equal, ch is used
bool ClassicDVD::operator==(const ClassicDVD& N) const { 
	return actor == N.actor && month == N.month && year == N.year;
};

//-------------------------------  !=  ---------------------------------------
// > defined by value of num; if nums equal, ch is used
bool ClassicDVD::operator!=(const ClassicDVD& N) const { 
   return !(*this == N);
};

//-------------------------------  <<  ---------------------------------------
// display NodeData object
ostream& operator<<(ostream& output, const ClassicDVD& N) { 
	output << setw(3) << (N.total_copies - N.numOut) << "   " << left << setw(5) << N.numOut
	      << setw(20) << N.title << setw(15) << N.director << right 
		  << setw(6) << N.year << setw(3) << N.month << "  " << N.actor
		  << "\n";

   return output;
};
