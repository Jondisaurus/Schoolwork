#IFNDEF INTSET_H
#DEFINE INTSET_H

#include<iostream>
using namespace std;

class IntSet
{
public:
   IntSet();
   IntSet(int&);
   IntSet(int&, int&);
   IntSet(int&, int&, int&);
   IntSet(int&, int&, int&, int&);
   IntSet(int&, int&, int&, int&, int&);
   ~IntSet();    
       
   IntSet operator+() const;
   IntSet operator*() const;
   IntSet operator-() const;
   IntSet operator=() const;
   IntSet operator+=() const;
   IntSet operator*=() const;
   IntSet operator-=() const;
   bool operator==() const;
   bool operator!=() const;
   bool insert();
   bool remove();
   bool isEmpty();
   bool isInSet();
               
             
private:
}
