#include "askUser.h"
#include <string>
#include <iostream>
using namespace std;

// Asks the users any kind of input through the screen
//TODO: put in place checks to see if user input is good
string askUser::askInput(string appQuery)
{
	string responseUser;

	cout << appQuery << endl; 
	getline(cin, responseUser);

	return responseUser;
}

string askUser::chooseList(json& chooseJson, string typeJson)
{
	string userAns;
	int openListNr;
	int listNr = 0;
	bool userAnsCorr = false;
	
	while (!userAnsCorr)
	{
		cout << "Here is an overview of your current " << typeJson << "s:" << endl << endl;
		
		for (auto it = chooseJson.begin(); it != chooseJson.end(); ++it)
		{
			listNr++;
			cout << listNr << " - " << it.key() << endl;
		}
		listNr = 0;

		userAns = askInput("Choose a " + typeJson + " to open by returning the number of the " + typeJson + ":");
		istringstream(userAns) >> openListNr;
		if (0 < openListNr && openListNr <= chooseJson.size())
		{
			userAnsCorr = true;
		}
		else
		{
			cout << "The number you entered doesn't exist, please try again." << endl;
		}
	}
	

	for (auto it = chooseJson.begin(); it != chooseJson.end(); ++it)
	{
		listNr++;
		if (listNr == openListNr)
		{
			return it.key();
		}
	}
}
