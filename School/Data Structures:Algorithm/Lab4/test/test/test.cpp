#include <iostream>
#include <string>
#include <fstream>
#include "command_base.h"

using namespace std;

int main()
{
	string fileName = "data4commands.txt";
	ifstream inFile(fileName);
	CommandData toAdd; 
	string temp;
	string token;
	string dump;
	char strTemp[50];
	bool addToQueue = true; 
	
	if (!inFile)  //check to make sure file opens 
	{     
      cout << "Command Data could not be opened.\nCommands are NOT loaded." << endl; 
	  system("pause");
      return 0;  
    }

	for(;;)
	{
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
				toAdd.director.pop_back();
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
	}

	system("pause");
	return 0;
}
