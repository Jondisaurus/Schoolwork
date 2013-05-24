#include "commandFile.h"

// ---------------------------------------------------------------------------
// Constructor 
// Default constructor for commandFile class
commandFile::commandFile()
{
}



// ---------------------------------------------------------------------------
// Initialize
// Initializes data from input file string
void commandFile::initialize(const string fileName)
{
	ifstream inFile(fileName.c_str( ));
	 
	if (!inFile)  //check to make sure file opens 
	{     
      cout << "Command Data could not be opened.\nCommands are NOT loaded." << endl; 
      return;  
    }

	string temp;
	string token;
	string dump;
	char strTemp[50];
	bool addToQueue = true; 
	
	

	for(;;)
	{
		CommandData toAdd;

		if(inFile >> skipws >> toAdd.action == false)
			break;
		
		if(toAdd.action != 'B' && toAdd.action != 'H' && toAdd.action != 'R')
		{
			getline(inFile, toAdd.other);
		}
		else if(toAdd.action != 'H')
		{
			getline(inFile, temp);
			strcpy(strTemp, temp.c_str());
			toAdd.custID = atoi(strtok(strTemp, " "));
			toAdd.dataType = strtok(NULL, " ")[0];
			toAdd.movieType = strtok(NULL, " ")[0];

			if(toAdd.movieType == 'F')
			{
				toAdd.title = strtok(NULL, ",");
				toAdd.year = atoi(strtok(NULL, " "));
			}
			else if(toAdd.movieType == 'C')
			{
				toAdd.month = atoi(strtok(NULL, " "));
				toAdd.year = atoi(strtok(NULL, " "));
				toAdd.actor = strtok(NULL, "\n");
			}
			else if(toAdd.movieType == 'D')
			{
				toAdd.director = strtok(NULL, ",");
				toAdd.title = strtok(NULL, ",");
				toAdd.title.erase(0,1);
			}	
		}	
		else 
		{
			getline(inFile, temp);
			strcpy(strTemp, temp.c_str());
			toAdd.custID = atoi(strtok(strTemp, " "));
		}

		Q.push(toAdd);
	}
}

// ---------------------------------------------------------------------------
// next
// retrieves next item from queue and returns commandData object
CommandData* commandFile::next()
{
	CommandData* temp = NULL;

	if(Q.empty() == false)
	{
		temp = new CommandData;

		*temp = Q.front();
		Q.pop(); 
	}

	return temp; 
}
