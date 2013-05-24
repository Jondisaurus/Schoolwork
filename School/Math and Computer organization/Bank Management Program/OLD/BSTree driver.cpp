#include <iostream>
#include "BStree.h" 
#include "account.h"
#include "firm.h"

using namespace std; 

int main()
{

	firm bobertson;

	BSTree<int> bob;

	int* joe = new int(6);
	int* jean = NULL;
	int billy = 74;

	bob.insert(joe);
	joe = new int(22);
	bob.insert(joe); 
	joe = new int(44);
	bob.insert(joe); 
	joe = new int(11);
	bob.insert(joe); 
	joe = new int(12);
	bob.insert(joe); 
	joe = new int(15);
	bob.insert(joe); 
	joe = new int(16);
	bob.insert(joe); 
	joe = new int(33);
	bob.insert(joe); 
	joe = new int(66);
	bob.insert(joe); 
	joe = new int(56);
	bob.insert(joe); 

	transData testo;
	transData toCopy; 

	testo.accountNum = 1234;
	testo.acctTyp = 4;
	testo.transType = 'd';
	testo.bal1 = 333333; 
	testo.toAcct = 2222;
	testo.toAcctTyp = 4; 
		

	Account jones;
	jones.historyAdd(testo);
	testo.accountNum = 3453;
	jones.historyAdd(testo);
	testo.accountNum = 2462;
	jones.historyAdd(testo);

	jones.it = jones.history.begin();

	for(int j = 0; j < 3 ; j++)
	{
		
		toCopy = *jones.it; 

		cout  << "outputting account num " << toCopy.accountNum << " " << toCopy.bal1 << endl;
		jones.it++; 
	}

	jones.firstName = "bob";
	jones.lastName = "bobbertson";
	jones.accountNum = 1234; 
	jones.accountBal[1] = 33333;
	jones.accountBal[0] = 22222; 

	//cout << endl << jones << endl; 

	bob.display();
	if(bob.retrieve(billy, jean))
		cout << endl << *jean << " was found in the tree\n"; 
	else cout << endl << billy << " could not be found\n";
	//cout << bob.retrieve(billy, jean) << "   " << *jean;
	bob.makeEmpty();

	cout << "\n empty done here \n"; 

	
	bob.display(); 

	system("pause"); 


}