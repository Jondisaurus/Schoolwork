#ifndef GETQUEUE_H
#define GETQUEUE_H

#include <iostream>
#include <fstream>
#include <queue>
#include "account.h"

using namespace std; 

//--------------------------  class GetQueue  ------------------------------------
// Class getQueue: This builds a queue object from transaction data that is used
//                 to control a seperate banking class
//          
// Assumptions:  
//    -- Data in the file built is correctly formatted
//    -- the object utilizing the queue accepts transData structs
//    
//----------------------------------------------------------------------------

class getQueue
{
public:
	getQueue();
	~getQueue();

	transData getNext();
	bool isEmpty();

private:
	void buildQueue(queue<transData>&);
	queue<transData> transQ;
};

#endif