
#include "mediastore.h"

MediaStore::MediaStore()
{
}

MediaStore::~MediaStore()
{
}

void MediaStore::initialize(const string fileName)
{
	ifstream inFile(fileName);
	string help;

	if (!inFile)  //check to make sure file opens 
	{     
      cout << "Command Data could not be opened.\nCommands are NOT loaded." << endl; 
      return;  
    }

	char movieType = ' ';

	for(;;)
	{
		if(inFile >> skipws >> movieType == false)
			break;

		if(movieType == 'C')
		{
			ClassicDVD* toAdd = new ClassicDVD;
			ClassicDVD* dupe;

			inFile.get();
			getline(inFile, toAdd->director, ',');
			inFile.get();
			getline(inFile, toAdd->title, ',');
			inFile.get();
			getline(inFile, toAdd->actor, ' ');
			toAdd->actor.append(" ");
			getline(inFile, help, ' ');
			toAdd->actor.append(help); 
			inFile >> toAdd->month >> toAdd->year;

			classics.retrieve(*toAdd, dupe);

			if(dupe == NULL)
			{	
				if(classics.insert(toAdd))
					cout << "\nCLASSIC ADDED\n";
			}

			else{ dupe->total_copies++; }

			delete toAdd;
			
		}
		else if(movieType == 'F')
		{
			ComedyDVD* toAdd = new ComedyDVD;
			ComedyDVD* dupe;

			inFile.get();
			getline(inFile, toAdd->director, ',');
			inFile.get();
			getline(inFile, toAdd->title, ',');
			inFile.get();
			inFile  >> toAdd->year;

			comedies.retrieve(*toAdd, dupe);

			if(dupe == NULL)
			{	
				if(comedies.insert(toAdd))
					cout << "\nFUNNIES ADDED\n";
			
			}

			else{ dupe->total_copies++; }

		//	delete toAdd;
			
		}
		else if(movieType == 'D')
		{
			DramaDVD* toAdd = new DramaDVD;
			DramaDVD* dupe;

			inFile.get();
			getline(inFile, toAdd->director, ',');
			inFile.get();
			getline(inFile, toAdd->title, ',');
			inFile.get(); 
			inFile >> toAdd->year;

			dramas.retrieve(*toAdd, dupe);

			if(dupe == NULL)
			{	
				if(dramas.insert(toAdd))
					cout << "\nDRAMA ADDED\n";

			}

			else{ dupe->total_copies++; }

			delete toAdd;

		}
		else
		{
			getline(inFile, help);
		}

	}
}

bool MediaStore::getHistory(const CommandData)
{
	return true;
}

void MediaStore::checkIn(const CommandData)
{
}

bool MediaStore::checkOut(const CommandData)
{
	return true;
}

void MediaStore::getMovie(const CommandData)
{
};
