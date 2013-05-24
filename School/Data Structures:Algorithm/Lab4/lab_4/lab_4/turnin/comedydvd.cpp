#include "comedydvd.h"

ComedyDVD::ComedyDVD()
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

ComedyDVD::~ComedyDVD()
{
}

void ComedyDVD::displayInv(const CommandData src)
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

void ComedyDVD::checkIn()
{
	numOut--;
}
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


//-------------------------------  <  ----------------------------------------
// < defined by value of num; if nums equal, ch is used
bool ComedyDVD::operator<(const ComedyDVD& N) const 
{ 
   if (title < N.title) return true;
   if (title == N.title && year < N.year) return true;
   if (title == N.title && year == N.year) return month < N.month;
   return false; 
};

//-------------------------------  >  ----------------------------------------
// > defined by value of num; if nums equal, ch is used
bool ComedyDVD::operator>(const ComedyDVD& N) const { 
   if (title > N.title) return true;
   if (title == N.title && year > N.year) return true;
   if (title == N.title && year == N.year) return month > N.month;
   return false;
};

//-------------------------------  ==  ---------------------------------------
// > defined by value of num; if nums equal, ch is used
bool ComedyDVD::operator==(const ComedyDVD& N) const { 
	return title == N.title && month == N.month && year == N.year;
};

//-------------------------------  !=  ---------------------------------------
// > defined by value of num; if nums equal, ch is used
bool ComedyDVD::operator!=(const ComedyDVD& N) const { 
   return !(*this == N);
};

//-------------------------------  <<  ---------------------------------------
// display NodeData object
ostream& operator<<(ostream& output, const ComedyDVD& N) { 
   output << setw(3) << (N.total_copies - N.numOut) << "   " << left << setw(5) << N.numOut
	      << setw(20) << N.title << setw(15) << N.director << right 
		  << setw(6) << N.year << setw(3) << N.month << "  " << N.actor
		  << "\n";

   return output;
};