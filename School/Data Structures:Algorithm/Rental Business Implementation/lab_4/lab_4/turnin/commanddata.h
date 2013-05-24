#pragma once
#ifndef COMMANDDATA_H
#define COMMANDDATA_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

class CommandData
{
	friend ostream& operator<< (ostream &output, const CommandData src) 
	{
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
		}

        return output;
    }

public:
	CommandData();
	CommandData(const CommandData&);
	virtual ~CommandData() {}

	char action;
	int custID;
	char dataType;
	char movieType;
	int year;
	int month;
	string director;
	string title;
	string actor;
	string other;
};

#endif
