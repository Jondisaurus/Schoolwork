#pragma once
#ifndef COMEDYDVD_H
#define COMEDYCDVD_H

#include "media_base.h"
#include "commanddata.h"
#include <iostream>
#include <iomanip>

using namespace std;

class ComedyDVD : public MediaBase
{
	friend ostream& operator<<(ostream &, const ComedyDVD &);

public:
	ComedyDVD();
	~ComedyDVD();

	void displayInv(const CommandData);
	void checkIn();
	bool checkOut();

    bool operator<(const ComedyDVD& N) const;      
    bool operator>(const ComedyDVD& N) const;
    bool operator==(const ComedyDVD& N) const;
    bool operator!=(const ComedyDVD& N) const;

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