#include "customerdata.h"

cust::cust()
{
	custID = 0;
	firstName = "";
	lastName = "";
}

void cust::histAdd(const CommandData& src)
{
	 history.push_front(src);
}

void cust::dispHistory()
{
	if(!history.empty())
	{
		cout << "\n\n=========   Outputting History for " << firstName << " " << lastName << " ||| UserID = " << custID << "   =======\n";

		list<CommandData>::const_iterator it;
		for(it = history.begin(); it != history.end(); it++)
		{
			cout << *it;
		}

		cout << endl << endl;
	}
	else
	{
		cout << "\n\n ----- NO HISTORY AVAILABLE FOR " << firstName << " " << lastName << " |||  UserID = " << custID << " ----- \n\n";
	}
}

//-------------------------------  <  ----------------------------------------
// < defined by value of num; if nums equal, ch is used
bool cust::operator<(const cust& src) const 
{ 
	return custID < src.custID;
}

//-------------------------------  >  ----------------------------------------
// > defined by value of num; if nums equal, ch is used
bool cust::operator>(const cust& src) const 
{ 
	return custID > src.custID;
}

//-------------------------------  ==  ---------------------------------------
// > defined by value of num; if nums equal, ch is used
bool cust::operator==(const cust& src) const 
{ 
	return custID == src.custID;
}

//-------------------------------  !=  ---------------------------------------
// > defined by value of num; if nums equal, 
bool cust::operator!=(const cust& src) const 
{ 
	return custID != src.custID; 
}