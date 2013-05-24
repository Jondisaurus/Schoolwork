#pragma once
#ifndef MEDIA_BASE_H
#define MEDIA_BASE_H

#include "commanddata.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std; 

//----------------------------------------------------------------------------
// class MediaBase
// By: Jonathan Difrancesco 2012
//
// ADT MediaBase
//               Interface for DVD type objects. Pure virtual
//
// Assumptions: 
//             -All data contained is properly formatted
//
//
//----------------------------------------------------------------------------

class MediaBase
{
public:
   
	MediaBase(); //default constructor
	virtual ~MediaBase(){} //default destructor

	virtual void checkIn() = 0; // check in object
	virtual bool checkOut() = 0; // check out object
	virtual void buildList(ifstream&) = 0; //build list of objects
	virtual void addDupe(); //add duplicate member to total stock
	
	virtual bool operator<(const MediaBase& source) const; // < operator
	virtual bool operator>(const MediaBase& source) const; // > operator
	virtual bool operator==(const MediaBase& source) const; // equivilence operator
	virtual bool operator!=(const MediaBase& source) const; // inequality operator
	virtual void print(ostream&) const; //print all data
	virtual void histPrint(ostream&) const = 0; //print history formatted data
	virtual void set(string, string, int, int) = 0; //sets data for retrieve operation

protected:
	
	char type; //type of action to happen
	string actor; //actor of movie
	string title; //title of movie
	string director; //director of movie
	int month; //month movie was made
	int year; //year movie was made
	int total_copies; //total number of copies
	int numOut; //number of copies checked out

private:

};

#endif
