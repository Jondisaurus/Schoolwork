//----------------------------------------------------------------------------
// class Prefix
// By: Jonathan Difrancesco 2011
//
// Class Prefix: This class takes a prefix mathmatical operation and evaluates it
//               as well as converting it to a post fix expression. 
//             
//
// Assumptions: 
//               -Data will be a correctly formatted prefix expression
//               -Each expression will be valid (aka no divide by zero)
//               -Each expression is an integer between 0-9
//
//----------------------------------------------------------------------------


#ifndef PREFIX_H
#define PREFIX_H
#include <iostream>
#include <fstream>
using namespace std;

int const MAXSIZE = 100;

class Prefix {
    friend ostream& operator<<(ostream&, const Prefix&);

public:
    Prefix();
    void setPrefix(ifstream& infile);
    int evaluatePrefix() const;
    void outputAsPostfix(ostream&) const;

private:
    char expr[MAXSIZE];
    int evaluatePrefixHelper(int&) const;
    void toPostfix(int&, char [], int&) const;
};

#endif

