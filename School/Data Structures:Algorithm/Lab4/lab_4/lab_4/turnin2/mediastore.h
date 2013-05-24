#pragma once
#ifndef MEDIASTORE_H
#define MEDIASTORE_H

#include "commanddata.h"
#include "classicdvd.h"
#include "comedydvd.h"
#include "bintree.h"
#include "dramadvd.h"
#include <string>
#include <fstream>
#include <iostream>

//----------------------------------------------------------------------------
// class MediaStore
// By: Jonathan Difrancesco 2012
//
// ADT MediaStore
//               Processes commands and handles movie data storange and manipulaton
//
// Assumptions: 
//             -All data contained is properly formatted
//
//
//----------------------------------------------------------------------------

class MediaStore
{
public:
	MediaStore(); //default constructor
	virtual ~MediaStore(){} //default destructor

	void initialize(const string); //initialize 
	bool getHistory(const CommandData&); //get history for all member
	bool checkIn(const CommandData&); //check in movie
	bool checkOut(const CommandData&); //check out movie
	void dispStock(); //display stock levels of movies

private:
	MediaBase* processCmd(const CommandData&); //coverts command object to mediabase object

	BinTree<MediaBase> classics; //classic movie storage
	BinTree<MediaBase> comedies; //comedy movie storage
	BinTree<MediaBase> dramas; //drama movie storage
};

#endif
