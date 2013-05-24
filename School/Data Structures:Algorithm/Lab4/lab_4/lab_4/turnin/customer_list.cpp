#include "customer_list.h"

customer_list::customer_list()
{
}

customer_list::~customer_list()
{
}

void customer_list::initialize(const string fileName)
{
	ifstream inFile(fileName);

	cust* toAdd = NULL;
	 
	if (!inFile)  //check to make sure file opens 
	{     
      cout << "Customer Data could not be opened.\nCustomers are NOT loaded." << endl; 
      return;  
    }
	
	for(;;)
	{
		toAdd = new cust;

		if(inFile >> toAdd->custID == false)
			break;

		inFile >> toAdd->lastName >> toAdd->firstName;

		T.insert(toAdd); 
	}

	if(toAdd != NULL)
	{  delete toAdd; }
}

void customer_list::displayUser(const int id)
{
	cust* temp = NULL;

	temp = T.getCust(id);

	if(temp != NULL)
	{  temp->dispHistory(); }

	else cout << "\n\n == ERROR! User not found! == \n\n";
}

void customer_list::processUser(const CommandData src)
{
	cust* proc = T.getCust(src.custID); 

	if(proc == NULL)
	{
		cout << "\n\n == ERROR! User not found! == \n\n";
		return;
	}

	if(src.action == 'H')
	{
		customer_list::displayUser(src.custID);
		T.getCust(src.custID)->histAdd(src);
	}

	else
	{   T.getCust(src.custID)->histAdd(src);} 
}

cust* customer_list::getUser(const int id)
{
	cust* temp = NULL;
	temp = T.getCust(id);
	return temp;
}