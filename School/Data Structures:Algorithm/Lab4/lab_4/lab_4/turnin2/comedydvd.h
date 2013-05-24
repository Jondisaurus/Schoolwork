#pragma once
#ifndef COMEDYDVD_H
#define COMEDYCDVD_H

#include "media_base.h"
#include "commanddata.h"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

//----------------------------------------------------------------------------
// class ClassicDVD
// By: Jonathan Difrancesco 2012
//
// ADT ClassicDVD: Inherits Media Base class and implements virtual members and 
//				allows serching, printing and data manipulation of class
//
// Assumptions: 
//               -Data will be correctly formatted for output and streamed properly
//
//
//----------------------------------------------------------------------------

class ComedyDVD : public MediaBase
{
public:
	ComedyDVD();//default constructor
	~ComedyDVD();//default destructor

	void checkIn(); //check in movie
	bool checkOut(); //check out movie if copies available
	void buildList(ifstream&); //build classic movie list from f stream object

    bool operator<(const MediaBase& N) const; // < operator
    bool operator>(const MediaBase& N) const; // > operator
    bool operator==(const MediaBase& N) const; // equivilence operator
    bool operator!=(const MediaBase& N) const; // inequivience operator
	void print(ostream&) const; //print contents of object
	void histPrint(ostream&) const; //prting contests of object formatted for history display
	void set(string, string, int, int); // sets the contents of object for use with retrieve

private:

};

#endif