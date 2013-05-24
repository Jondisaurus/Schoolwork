#include "HashTable.h"
#include "customerdata.h"

HashTable::HashTable()
{
	HashTable::table = new Node*[MAX_BUCKETS]; 
	
	for(int i = 0; i <= MAX_BUCKETS ; i++)
	{  table[i] = NULL; }

}

HashTable::~HashTable()
{
	clear(); 

	delete [] table;
	table = NULL; 
}

void HashTable::clear()
{
	for(int i = 0; i <= MAX_BUCKETS ; i++)
	{
		if(table[i]->next != NULL)
		{
			clearHelper(table[i]->next);
		}
		
		if(table[i]->customerInfo != NULL)
		{ 
			delete table[i]->customerInfo; 
		} 

		delete table[i];
		table[i] = NULL; 
	}
}

void HashTable::clearHelper(Node* src)
{
	delete src->customerInfo;
	src->customerInfo = NULL; 

	if(src->next != NULL)
	{
	   clearHelper(src->next);
	}

	delete src;
	src = NULL; 
}

bool HashTable::insert(const cust* src)
{
	int hash = ((src->custID * HASH_FACTOR) % MAX_BUCKETS);

	if(table[hash] == NULL)
	{
		table[hash] = new Node;
		table[hash]->customerInfo = new cust;
		*table[hash]->customerInfo = *src; 
		table[hash]->next = NULL;
		return true;
	}

	else if(*table[hash]->customerInfo == *src)
	{
		return false;
	}

	else
	{
		if(table[hash]->next == NULL)
		{
			Node* ptr = new Node;

			ptr->next = NULL;
			ptr->customerInfo = new cust;
			*ptr->customerInfo = *src;
			
			table[hash]->next = ptr;
			return true;
		}

		else
		{
			Node* current = table[hash]->next;

			if(*current->customerInfo == *src)
				return false;
												
			while(current->next != NULL) // walk to end of collisions
			{
				current = current->next;

				if(*current->customerInfo == *src)
					{return false;}
			}

			Node* ptr = new Node;

			ptr->next = NULL;
			ptr->customerInfo = new cust;
			*ptr->customerInfo = *src;

			return true;
		}
	}
}
	
cust*& HashTable::getCust(const int id)
{   
	cust* notFound = NULL;
	int hash = ((id * HASH_FACTOR) % MAX_BUCKETS);

	if(table[hash]->customerInfo->custID == id)
	{  return table[hash]->customerInfo; } 
	
	else
	{
		if(table[hash]->next == NULL)
		{  return notFound; }

		Node* current = table[hash]->next;

		if(current->customerInfo->custID == id)
		{  return current->customerInfo; } 

		while(current->next != NULL)
		{
			current = current->next;

			if(current->customerInfo->custID == id)
			{  return current->customerInfo; }
		}
		return notFound;
	}
}

bool HashTable::isEmpty()
{
	if(table == NULL)
	{  return false; }

	for(int i = 0; i <= MAX_BUCKETS ; i++)
	{
		if(table[i] != NULL)
		{  return false; }
	}

	return true; 
}
