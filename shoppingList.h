#pragma once

#include "externalCode/json.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;


#include "askUser.h"
#include "jsonHelp.h"
#include "helperFunc.h"

class shoppingList
{
private:
	vector<string> itemList;
	
	

public:
	void orderList();
	void createList();
	// Adds an item to a shopping list
	void addItem(json& currList, json& allDeps, string listName);
	void checkAllDepsForItem(json& allDeps, string currItem);
	void addItemToDep(json& allDeps, string currItem);
	void dumpDeps(json& allDeps, string whatDump);
	// Opens an existing shopping list and gives you the option to either add an item or sort the list to then use it while shopping
	void openList();
	void delList();
};

