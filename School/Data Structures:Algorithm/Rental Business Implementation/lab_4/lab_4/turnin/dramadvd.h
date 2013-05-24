#pragma once
#ifndef DRAMADVD_H
#define DRAMADVD_H

#include "media_base.h"
#include "commanddata.h"
#include <iostream>
#include <iomanip>

using namespace std;

class DramaDVD : public MediaBase
{
	friend ostream& operator<<(ostream &, const DramaDVD &);

public:
	DramaDVD();
	~DramaDVD();

	void displayInv(const CommandData);
	void checkIn();
	bool checkOut();

    bool operator<(const DramaDVD& N) const;      
    bool operator>(const DramaDVD& N) const;
    bool operator==(const DramaDVD& N) const;
    bool operator!=(const DramaDVD& N) const;

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