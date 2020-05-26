#include "jsonHelp.h"


void jsonHelp::writeJson(json& jsonToWrite, string nameOfFile)
{
	ofstream jsonToSave(nameOfFile);
	jsonToSave << jsonToWrite;
}


json jsonHelp::readJson(string nameOfFile)
{
	ifstream inFile(nameOfFile);
	try
	{
		json j;
		inFile >> j;
		return j;
	}
	catch (...)
	{
		cout << "Couldn't find the file." << endl;
		cout << "Returning empty JSON." << endl;
		json empJson;
		return empJson;
	}
	
}
