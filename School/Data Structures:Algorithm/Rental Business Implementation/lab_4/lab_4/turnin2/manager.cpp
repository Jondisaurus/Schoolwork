#include "manager.h"

// ---------------------------------------------------------------------------
// Constructor
// Default constructor for Manager class
Manager::Manager()
{
	commands = new commandFile;
	customers = new customer_list;
	media = new MediaStore;
}

// ---------------------------------------------------------------------------
// Destructor 
// Default destructor for Manager class
Manager::~Manager()
{
	delete commands;
	delete customers;
	delete media;
}

// ---------------------------------------------------------------------------
// Initialize 
// Initializes control objects from file name data
bool Manager::initialize( const string custID, const string cmds, const string movies)
{
	commands->initialize(cmds);
	customers->initialize(custID);
	media->initialize(movies);

	return true;
}

// ---------------------------------------------------------------------------
// Run
// Pulls commands from command queue and delegates them to correct places
void Manager::run()
{
	CommandData *nextCmd = commands->next();

	while(nextCmd != NULL)
	{
		cout << *nextCmd;
		
		cust* temp = NULL;

		switch(nextCmd->action)
		{
		case 'S':
			media->dispStock();
			break;
		case 'H':{
			temp = customers->getUser(nextCmd->custID);

			if(temp == NULL)
				break;

			CommandData* histCMD = temp->nextCmdHist();

			if(temp != NULL)
			{
				cout << "\n\n Outputting Data for " << temp->firstName << " " << temp->lastName << " -==- User# " << temp->custID << "\n";
				while(histCMD != NULL)
				{
					media->getHistory(*histCMD);
					histCMD = temp->nextCmdHist();
				}
				cout << "\n\n";
			}
		         
			break;
				 }
		case 'B':
			temp = customers->getUser(nextCmd->custID);

			if(temp == NULL)
			{
				cout << "USER# " << nextCmd->custID << " NOT FOUND!!";
				break;
			}

			if(!media->checkOut(*nextCmd))
				break;

			temp->histAdd(*nextCmd); 
			break;

		case 'R':
			temp = customers->getUser(nextCmd->custID);

			if(temp == NULL)
			{
				cout << "USER# " << nextCmd->custID << " NOT FOUND!!";
				break;
			}

			if(!media->checkIn(*nextCmd))
				break;

			temp->histAdd(*nextCmd); 
			break;
		}

		//delete nextCmd;
		nextCmd = commands->next();
	}
	
}