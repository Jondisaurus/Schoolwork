#pragma once
#ifndef COMMANDDATA_H
#define COMMANDDATA_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

//----------------------------------------------------------------------------
// class CommandData
// By: Jonathan Difrancesco 2012
// ABSTRACT CLASS
//
// ADT CommandData
//                  container class that holds command data that manipulates
//                  other functions found within the program. 
//
// Assumptions: 
//             -All data contained is properly formatted
//
//
//----------------------------------------------------------------------------

class CommandData
{
	friend ostream& operator<< (ostream &output, const CommandData src) //Output stored data (mostly debugging code)
	{
		/*
		output << src.custID;

		if(src.action == 'B' || src.action == 'R')
		{
			if(src.action == 'B')
			{
				output << " Borrowed ";
			}
			else
			{
				output << " Returned ";
			}

			if(src.movieType == 'F')
				output  << src.title << " " << src.year << "\n";
			else if(src.movieType == 'C')
				output << src.month << " " << src.year << " " << src.actor << "\n";
			else if(src.movieType == 'D')
				output << src.director << " " << src.title << "\n";
		}
		else if(src.action == 'H')
		{
			output << " Display History\n";
		}
		else
		{
			output << " Unknown Command\n";
		}*/

        return output;
    }

public:
	CommandData(); //defailt constructor
	CommandData(const CommandData&); //copy constuctor
	virtual ~CommandData() {} //virtual destructor

	char action; // operation to be performed
	int custID; //customer ID
	char dataType; //Type of data to be read
	char movieType; //type of movie contained
	int year; //year movie was made
	int month; //Month movie was made
	string director; //Director of move
	string title; //title of movie
	string actor; //main actor of movie
	string other; // other data that can be reprocess at a later time
};

#endif
