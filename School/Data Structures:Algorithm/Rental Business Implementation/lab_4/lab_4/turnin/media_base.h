#pragma once
#ifndef MEDIA_BASE_H
#define MEDIA_BASE_H

#include "commanddata.h"
#include <string>
#include <iostream>


using namespace std; 

class MediaBase
{
public:

	MediaBase();
	virtual ~MediaBase(){}

	virtual void displayInv(const CommandData) = 0;
	virtual void checkIn() = 0;
	virtual bool checkOut() = 0;

private:

};

#endif
