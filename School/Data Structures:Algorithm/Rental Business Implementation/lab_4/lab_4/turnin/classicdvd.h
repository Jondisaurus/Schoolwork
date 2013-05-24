#pragma once
#ifndef CLASSICDVD_H
#define CLASSICDVD_H

#include "media_base.h"
#include "commanddata.h"
#include <iostream>
#include <iomanip>

using namespace std;

class ClassicDVD : public MediaBase
{
	friend ostream& operator<<(ostream &, const ClassicDVD &);

public:
	ClassicDVD();
	~ClassicDVD();

	void displayInv(const CommandData);
	void checkIn();
	bool checkOut();

    bool operator<(const ClassicDVD& N) const;      
    bool operator>(const ClassicDVD& N) const;
    bool operator==(const ClassicDVD& N) const;
    bool operator!=(const ClassicDVD& N) const;

	char type;
	string actor;
	string title;
	string director;
	int month;
	int year;
	int total_copies;
	int numOut;
private:

};

#endif