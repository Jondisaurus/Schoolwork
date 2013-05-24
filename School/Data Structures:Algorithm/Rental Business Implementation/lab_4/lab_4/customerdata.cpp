#include "customerdata.h"

// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for customerData class
cust::cust()
{
	custID = 0;
	firstName = "";
	lastName = "";
	list<CommandData>::const_iterator histIt = history.begin();
}

// ---------------------------------------------------------------------------
// histAdd
// Adds command object to customer history
void cust::histAdd(const CommandData& src)
{
	 history.push_front(src);
	 histIt = history.begin();
}

// ---------------------------------------------------------------------------
// disphistory
// distplays customer history
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

// ---------------------------------------------------------------------------
// resetIt 
// Resets itorator to begging posistion
void cust::resetIt()
{
	histIt = history.begin(); 
}

// ---------------------------------------------------------------------------
// nextCmdHist
// retrieves next command from customer history data
CommandData* cust::nextCmdHist()
{
	if(history.empty())
		return NULL;
	
	if(histIt != history.end())
	{   
		CommandData* temp = new CommandData; 
		*temp = *histIt;
		histIt++;
		return temp;
	}
	else return NULL; 
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