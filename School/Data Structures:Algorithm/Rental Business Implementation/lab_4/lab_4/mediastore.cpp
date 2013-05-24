
#include "mediastore.h"

// ==== CODE BEHIND FOR MediaStore ====

// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for MediaStore class
MediaStore::MediaStore()
{
}


// ---------------------------------------------------------------------------
// Initialize
// Initializes data from input file string
void MediaStore::initialize(const string fileName)
{
	ifstream inFile(fileName.c_str( ));
	string help;
	MediaBase* dupe = NULL; 

	if (!inFile)  //check to make sure file opens 
	{     
      cout << "Command Data could not be opened.\nCommands are NOT loaded." << endl; 
      return;  
    }

	char movieType = ' ';

	for(;;) //builds objects from the ifstream object
	{
		if(inFile >> skipws >> movieType == false)
			break;

		if(movieType == 'C') // if classic movie
		{

			MediaBase* aClassic = new ClassicDVD;
			aClassic->buildList(inFile); 

			classics.retrieve(*aClassic, dupe); // get movie from tree

			if(dupe == NULL)// if movie not found
				classics.insert(aClassic); //insert into array
			else
			{
				dupe->addDupe();
				delete aClassic;
				aClassic = NULL;
			}

			dupe = NULL;

			//delete aClassic; 			
		}
		else if(movieType == 'D') //drama movie
		{
			MediaBase* aDrama = new DramaDVD;
			aDrama->buildList(inFile);

			dramas.retrieve(*aDrama, dupe); 

			if(dupe == NULL)
				dramas.insert(aDrama);
			else 
			{
				dupe->addDupe();
				delete aDrama;
				aDrama = NULL;
			}


			dupe = NULL; 
		}
		else if(movieType == 'F') //comedy movie
		{

			MediaBase* aComedy = new ComedyDVD;
			aComedy->buildList(inFile); 

			comedies.retrieve(*aComedy, dupe); 

			if(dupe == NULL)
				comedies.insert(aComedy);
			else
			{
				dupe->addDupe();
				delete aComedy;
				aComedy = NULL;
			}
			dupe = NULL; 
		}
		else 
		{ getline(inFile, help); } 
	}

}

// ---------------------------------------------------------------------------
// getHistory
// gets history data from the correct tree
bool MediaStore::getHistory(const CommandData& source)
{
	MediaBase* find = processCmd(source);
	MediaBase* found = NULL;

	if(source.action == 'B')
		cout << "Borrow == ";
	else if(source.action == 'R')
		cout  << "Return == ";

	switch(source.movieType)
	{
	case'C':
		classics.retrieve(*find, found);

		if(found != NULL)
		{
			found->histPrint(cout);
		}
		else cout << "/n/nMovie not found!\n\n";

		break;
	case'F':
		comedies.retrieve(*find, found);

		if(found != NULL)
		{
			found->histPrint(cout);
		}
		else cout << "/n/nMovie not found!\n\n";

		break;
	case'D':
		dramas.retrieve(*find, found);

		if(found != NULL)
		{
			found->histPrint(cout);
		}
		else cout << "/n/nMovie not found!\n\n";

		break;
	default:
		cout << "\n\nUnknows movie format!\n\n";
	}

	return true;
}

// ---------------------------------------------------------------------------
// dispStock
// outputs total contents of the trees
void MediaStore::dispStock()
{
	cout << "\n----==== OUTPUT ENTIRE STOCK ====----\n"
	     << "Outputting Classics Database: \n" << classics 
		 << "\nOutputting Comedies Database: \n" << comedies
		 << "\nOutputting Dramas Database: \n" << dramas;
}

// ---------------------------------------------------------------------------
// checkIn
// checks in movies from the command object
bool MediaStore::checkIn(const CommandData& source)
{
	MediaBase* found = processCmd(source);


	if(found != NULL)
	{
		found->checkIn();
		return true;
	}
	else
	{
		cout << " Movie not found!";
		return false;

	}
}

// ---------------------------------------------------------------------------
// checkOut
// checks out movies if there is enough stock, returns false if there isnt enough space
bool MediaStore::checkOut(const CommandData& source)
{
	MediaBase* found = processCmd(source);
	
	if(found != NULL)
	{
		if(!found->checkOut())
		{
			//cout << "\n\n No more copies remain!\n";
			return false; 
		}
		else return true;
	}
	else cout << " Movie not found!";
	return false; 
}

// ---------------------------------------------------------------------------
// processCmd
// processes command ojects and converts it to movie type object
MediaBase* MediaStore::processCmd(const CommandData& source)
{
	MediaBase* ptr = NULL;
	MediaBase* found = NULL;

	switch(source.movieType)
	{
	case'C':
		ptr = new ClassicDVD;
		ptr->set(source.title, source.actor, source.year, source.month);
		classics.retrieve(*ptr, found);
		break;

	case'F':
		ptr = new ComedyDVD;
		ptr->set(source.title, " ", source.year, source.month);
		comedies.retrieve(*ptr,found);
		break;
	case'D':
		ptr = new DramaDVD;
		ptr->set(source.title, source.director, 0, 0);
		dramas.retrieve(*ptr,found);
		break;
	default: return NULL;
	}

	delete ptr; 

	if(found != NULL)
		return found;
	else return NULL;
}
