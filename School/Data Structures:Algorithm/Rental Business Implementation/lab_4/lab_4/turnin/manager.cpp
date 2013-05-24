#include "manager.h"

Manager::Manager()
{
	commands = new commandFile;
	customers = new customer_list;
	media = new MediaStore;
}

Manager::~Manager()
{
	delete commands;
	delete customers;
	delete media;
}


bool Manager::initialize( const string custID, const string cmds, const string movies)
{
	commands->initialize(cmds);
	customers->initialize(custID);
	media->initialize(movies);
	
	customers->displayUser(3333);

	return true;
}

void Manager::run()
{
	CommandData *nextCmd = commands->next();

	while(nextCmd != NULL)
	{
		cout << *nextCmd;
		nextCmd = commands->next(); 
	}
	
}