#include "commanddata.h"

// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for CommandData class
CommandData::CommandData()
{
	action = ' ';
	custID = 0;
	dataType = ' ';
	movieType = ' ';
	year = 0;
	month = 0;
	director = "";
	title = "";
	actor = "";
	other = "";
}

// ---------------------------------------------------------------------------
// Copy Constructor 
// Copy constructor for CommandData class
CommandData::CommandData(const CommandData& src)
{
	action = src.action;
	custID = src.custID;
	dataType = src.dataType;
	movieType = src.movieType;
	year = src.year;
	month = src.month;
	director = src.director;
	title = src.title;
	actor = src.actor;
	other = src.other;
}
