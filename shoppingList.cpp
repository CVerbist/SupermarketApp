#include "shoppingList.h"

// TODO: Refactor 
void shoppingList::orderList()
{
	jsonHelp jFunc;
	askUser queryPrompt;
	helperFunc getDir;

	string workingDir;
	string shopData;
	string depData;
	string listData;
	string listName;
	json shops;
	json* ptrToShops = &shops;
	json deps;
	json* ptrToDep = &deps;
	json lists;
	json* ptrToLists = &lists;
	string userList;
	string userShop;
	vector<string> currItems;
	vector<string> shopsDepOrder;
	bool checkOn = true;
	
	// Get working directory and read shops file
	workingDir = getDir.getDir();
	shopData = workingDir + "\\userData\\shops.json";
	shops = jFunc.readJson(shopData);
	// Read the departments file
	depData = workingDir + "\\userData\\deps.json";
	deps = jFunc.readJson(depData);
	// Read the currently existing shoppinglists
	listData = workingDir + "\\userData\\lists.json";
	lists = jFunc.readJson(listData);

	userList = queryPrompt.chooseList(*ptrToLists, "list");
	userShop = queryPrompt.chooseList(*ptrToShops, "shop");

	currItems = lists[userList].get<vector<string>>();
	vector<int> orderItems(currItems.size(), -1); // Items not in departments will have a -1 as identifier
	for (size_t i = 0; i < currItems.size(); i++) 
	{
		vector<string> shopsDepOrder = shops[userShop]["depOrder"].get<vector<string>>();
		for (size_t j = 0; j < shopsDepOrder.size(); j++)
		{
			string currShopDep = shopsDepOrder[j];
			if (deps.count(currShopDep) > 0) // If the department of the shop is in the deps.json
			{
				vector<string> itemsOfDep = deps[currShopDep].get<vector<string>>();
				if (find(itemsOfDep.begin(), itemsOfDep.end(), currItems[i]) != itemsOfDep.end())
				{
					orderItems[i] = j; 
					break;
				}
			}
		}
	}


	vector<int> indSort(orderItems.size());
	int x = 0;
	iota(indSort.begin(), indSort.end(), x++); // Creates a range with a step of x++ (so 1)
	sort(indSort.begin(), indSort.end(), [&](int i, int j) {return orderItems[i] < orderItems[j]; }); // Sorts indSort but uses values of orderItems to sort indSort


	vector<string> sortedItems(currItems.size());
	for (size_t i = 0; i < currItems.size(); i++) 
	{
		sortedItems[i] = currItems[indSort[i]];
	}

	lists[userList] = sortedItems;
	jFunc.writeJson(*ptrToLists, listData);

}

//Creates a new shopping list and will give you the option to add items
void shoppingList::createList()
{
	jsonHelp jFunc;
	askUser queryPrompt;
	helperFunc getDir;

	string workingDir;
	string shopData;
	string depData;
	string listData;
	string listName;
	json shops;
	json* ptrToShops = &shops;
	json deps;
	json* ptrToDep = &deps;
	json lists;
	json* ptrToLists = &lists;
	

	// Get working directory and read shops file
	workingDir = getDir.getDir();
	shopData = workingDir + "\\userData\\shops.json";
	shops = jFunc.readJson(shopData);
	// Read the departments file
	depData = workingDir + "\\userData\\deps.json";
	deps = jFunc.readJson(depData);
	// Read the currently existing shoppinglists
	listData = workingDir + "\\userData\\lists.json";
	lists = jFunc.readJson(listData);

	listName = queryPrompt.askInput("Please enter the list's name. (Exit by typing x)");
	if (listName.compare("x") == 0 || listName.compare("X") == 0)
	{
		return;
	}
	else
	{
		lists[listName] = itemList;
		string userAdd = queryPrompt.askInput("Do you want to add items now? (y/n)");
		if (userAdd.compare("y") == 0 || userAdd.compare("Y") == 0)
		{
			addItem(*ptrToLists, *ptrToDep, listName);
			jFunc.writeJson(*ptrToLists, listData);
		}
	}
}


// Adds an item to a shopping list
void shoppingList::addItem(json& currList, json& allDeps, string listName)
{
	askUser queryPrompt;
	
	bool addingItem = true;

	if (currList.count(listName) > 0)
	{
		itemList = currList[listName].get<vector<string>>();
	}

	while (addingItem)
	{
		string currItem = queryPrompt.askInput("Please enter the next item or enter 'No' to finish.");

		if (currItem.compare("N") == 0 || currItem.compare("n") == 0 || currItem.compare("no") == 0 || currItem.compare("No") == 0 || currItem.compare("NO") == 0)
		{
			addingItem = false;
		}
		else
		{
			itemList.push_back(currItem);
			checkAllDepsForItem(allDeps, currItem);
		}
	}


	currList[listName] = itemList;
}

void shoppingList::checkAllDepsForItem(json& allDeps, string currItem)
{
	askUser queryPrompt;
	vector<string> currDepItems;
	bool itemInDeps = false;
	for (auto it = allDeps.begin(); it != allDeps.end(); ++it)
	{
		currDepItems = allDeps[it.key()].get<vector<string>>();
		if (find(currDepItems.begin(), currDepItems.end(), currItem) != currDepItems.end())
		{
			itemInDeps = true;
			break;
		}
	}
	if (itemInDeps == false)
	{
		cout << "The current item is not associated with any department." << endl;
		dumpDeps(allDeps, "departments");
		string askUserAdd = queryPrompt.askInput("Do you want to associate it with a department? (y/n)");
		if (askUserAdd.compare("y") == 0 || askUserAdd.compare("Y") == 0)
		{
			addItemToDep(allDeps, currItem);
		}
	}

}


void shoppingList::addItemToDep(json& allDeps, string currItem)
{
	askUser queryPrompt;
	jsonHelp jFunc;
	helperFunc getDir;
	string workingDir = getDir.getDir();
	string depData = workingDir + "\\userData\\deps.json";

	string depToAdd = queryPrompt.askInput("To which department do you want to add it?");
	bool succAdd = false;
	while (!succAdd)
	{
		if (allDeps.count(depToAdd) > 0)
		{
			cout << "Adding to: " << depToAdd << endl;
			allDeps[depToAdd].push_back(currItem);
			jFunc.writeJson(allDeps, depData);
			succAdd = true;
		}
		else
		{
			cout << "Couldn't find the department, make sure it is identical to one in the list.";
			dumpDeps(allDeps, "departments");
			depToAdd = queryPrompt.askInput("To which department do you want to add it?");
		}
	}
}


void shoppingList::dumpDeps(json& allDeps, string whatDump)
{
	cout << "Here is a list of the current " << whatDump << ":" << endl;
	cout << allDeps.dump(4) << endl;
}


// Opens an existing shopping list and gives you the option to either add an item or sort the list to then use it while shopping
void shoppingList::openList()
{
	jsonHelp jFunc;
	askUser queryPrompt;
	helperFunc getDir;

	string workingDir;
	string listData;
	string listName;
	string depData;
	json lists;
	json* ptrToLists = &lists;
	json deps;
	json* ptrToDep = &deps;
	string userList;

	// Get working directory
	workingDir = getDir.getDir();
	// Read the departments file
	depData = workingDir + "\\userData\\deps.json";
	deps = jFunc.readJson(depData);
	// Read the currently existing shoppinglists
	listData = workingDir + "\\userData\\lists.json";
	lists = jFunc.readJson(listData);

	userList = queryPrompt.chooseList(*ptrToLists, "list");

	cout << lists[userList] << endl;
	string editList = queryPrompt.askInput("Do you want to add items to the list? (y/n)");
	if (editList.compare("y") == 0 || editList.compare("Y") == 0)
	{
		addItem(*ptrToLists, *ptrToDep, userList);
		jFunc.writeJson(*ptrToLists, listData);
	}
}


void shoppingList::delList()
{
	askUser queryPrompt;
	jsonHelp jFunc;
	helperFunc getDir;

	json lists;
	json* ptrToLists = &lists;
	string userAns;
	string workingDir;
	string listData;
	bool userSat = false;

	// Get working directory and read shops file
	workingDir = getDir.getDir();
	listData = workingDir + "\\userData\\lists.json";
	lists = jFunc.readJson(listData);


	while (!userSat)
	{
		cout << "Here is a list of the current lists:" << endl;
		cout << lists.dump(4) << endl;
		userAns = queryPrompt.askInput("Which shop do you want to delete? (x to exit)");

		if (userAns.compare("x") == 0 || userAns.compare("X") == 0)
		{
			userSat = true;
		}
		else
		{
			if (lists.count(userAns) > 0)
			{
				cout << "Deleting " << userAns << " ..." << endl;
				lists.erase(userAns);
			}
			else
			{
				cout << "Couldn't find the shop, please try again." << endl;
			}
		}
	}
	jFunc.writeJson(*ptrToLists, listData);
}
