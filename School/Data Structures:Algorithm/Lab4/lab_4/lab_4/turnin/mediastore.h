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

class MediaStore
{
public:
	MediaStore();
	~MediaStore();

	void initialize(const string);
	bool getHistory(const CommandData);
	void checkIn(const CommandData);
	bool checkOut(const CommandData);
	void getMovie(const CommandData);

private:
	BinTree<ClassicDVD> classics;
	BinTree<ComedyDVD> comedies;
	BinTree<DramaDVD> dramas;
};

#endif
