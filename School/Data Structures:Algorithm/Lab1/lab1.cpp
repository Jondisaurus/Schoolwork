#include <iostream>
#include "poly.h"


#define msg(x) std::cout << "\n" << x << "\n"
#define spc std::cout << "\n"
#define exe(expr)  expr;\
                    std::cout << "\nEXEC EXPRESSION:  " << #expr << "\n"
#define test(expr)  expr;\
                    std::cout << "\nTEST EXPRESSION:  " << #expr;\
                    if (expr) std::cout << " -> TRUE\n";\
                    else { std::cout << " **FALSE**\n"; return 1; }
#define show(x) std::cout << "\n" << #x << " == " << x


int main(int argc, char** argv)
{
    Poly a(1,2), b(4,2), c;
    a.setCoeff(2,1);
	a.setCoeff(1,0);
    b.setCoeff(4,1);
	b.setCoeff(1,0);

    c.setCoeff(1,3);
	c.setCoeff(2,2);
	c.setCoeff(1,1);
    msg("initial values:");    
    show(a);show(b);show(c);spc;
    
    exe( Poly d = a + b + c );
    show(d); spc;
    
    exe( Poly e = a * b );
    show(e); spc;
    
    exe( Poly g = a );
    test( a == g ); show(a); show(g);
    exe( Poly f = a += b += c );
    show(f); show(d); show(a);
    test( f == d );
    test( a == f );
    test( d == f );
    test( a != b );
    test( f != c );
    show(d); exe( d -= 4 ); show(d); show(f);
    test( f != d );
    test( d == (f - 4) );
    spc;

    exe( Poly h = a -= b -= c );
    show(h); show(a); show(b); show(c); spc;
    test( a != g );
    test( h == a );

    exe( Poly j = h );
    exe( Poly k = h * a * b );
    show(j); show(k);
    exe( j *= a * b );
    test (j == k );
    show(j); show(k);
    spc;
    test( j != (h -= k - f * b) );
    show(j); show(h); spc; spc;
	system("pause");
}




















/*
// DO NOT change anything in this file. Your code must compile with this main
// on the linux machines.

// Make sure the file containing the member function source is: poly.cpp
// Use all lowercase in the file names.
// This main does not do a thorough job of testing.  When testing arrays,
//   be sure to test the middle and also all the boundary conditions.  Test
//   values on the boundary and outside the boundaries, i.e., too big/small.

#include "poly.h"
#include <iostream>
using namespace std;

int main () {
   Poly A(5,7), B(3,4), C(2), D(A), X, Y, G(5,6), J(12,12);

   // set polynomials A and B to desired values
   // A = +5x^7 -4x^3 +10x -2
   // B = +3x^4 +1x^3 
   cout << "Enter terms for polynomial A.  Enter a coefficient " << endl
        << "then exponent for each term. Enter 0 0 to terminate." << endl;
   cin >> A;                                     // or use a bunch of setCoeff
   cout << "Enter terms for polynomial B.  Enter a coefficient " << endl
        << "then exponent for each term. Enter 0 0 to terminate." << endl;
   cin >> B; // or use a bunch of setCoeff

   J = G;
   cout << "J =" << J << endl;



   // outputs exactly what is in quotes: "A = +5x^7 -4x^3 +10x -2"
   cout << "A =" << A << endl;
   // outputs exactly what is in quotes: "B = +3x^4 +1x^3"
   cout << "B =" << B << endl;
   cout << "C =" << C << endl << endl;

   C = A + B;  
   cout << "Compute C = A + B" << C << endl << endl;

   
   cout <<  ( (A == B) ? "A == B" : "A is not == B" ) << endl;
   cout <<  ( (A != B) ? "A is not == B" : "A == B" ) << endl;

   cout << "Compute  D = A * B - 15" << endl;
   cout << "Before: D =" << D << endl;
   D = A * B - 15;
   cout << "After:  D =" << D << endl << endl;

   cout << "Test assignment operators" << endl;
   X = C = D = D;  
   Y += A -= B *= A;
   cout << "X =" << X << endl;
   cout << "Y =" << Y << endl << endl;

   cout << "Get and Set coefficient" << endl;
   int coeff = D.getCoeff(0); 
   cout << "coeff of subscript 0 of D is: " << coeff << endl;
   cout << "Doing getCoeff for term -20000" << endl;
   coeff = D.getCoeff(-20000);              // handle value out of range
   D.setCoeff(50,0);                        // set x^0 coeff to 50
   D.setCoeff(50,20000);                    // set x^20000 coeff to 50
   cout << "D =" << D << endl << endl;
   system("pause"); 

   return 0;
}

*/

