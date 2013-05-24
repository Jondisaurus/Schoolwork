#pragma once
#ifndef POLY_H
#define POLY_H

#include <iostream>
using namespace std;

//----------------------------------------------------------------------------
// class Poly
// By: Jonathan Difrancesco 2012
//
// ADT Poly: Stores and displays a polynumeral that is modified and output
//           through various operators. 
//
// Assumptions: 
//               -Exponents must all be zero or positive
//               -Data passed will all be valid integers
//               -Coefficents of zero will not be displayed, but negative values
//                   are valid and will be stored
//
//----------------------------------------------------------------------------

class Poly
{
	friend ostream& operator<<(ostream&, const Poly&);
	friend istream& operator>>(istream &,  Poly&);

public:
	Poly(int = 0, int = -1);
	Poly(const Poly&);
	~Poly();

    bool operator==(const Poly&) const;
    bool operator!=(const Poly&) const;
	
	Poly operator=(const Poly&);
	Poly operator+=(const Poly&);
	Poly operator-=(const Poly&);
	Poly operator*=(const Poly&);

	Poly operator*(const Poly&) const;
	Poly operator-(const Poly&) const;
	Poly operator+(const Poly&) const;

	bool setCoeff(const int = -1, const int = -1);   // returns false if invalid input present
	int getCoeff(const int) const; // returns 0 if invalid character
	
private:
	void resize(const int);   //Resizes the array
	int* pArray;
	int size;
};

#endif
