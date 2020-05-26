#include "shopLayout.h"

void shopLayout::addShop()
{
	json shops;
	json* ptrToShops = &shops;
	json deps;
	json* ptrToDep = &deps;
	jsonHelp jFunc;
	askUser queryPrompt;
	helperFunc getDir;
	string shopName;
	string* ptrToShopName = &shopName;
	string workingDir;
	string shopData;
	string depData;

	// Get working directory and read shops file
	workingDir = getDir.getDir();
	shopData = workingDir + "\\userData\\shops.json";
	shops = jFunc.readJson(shopData);
	// Read the departments file
	depData = workingDir + "\\userData\\deps.json";
	deps = jFunc.readJson(depData);
	

	bool userSat = false;
	while (!userSat)
	{
		shopName = queryPrompt.askInput("Please enter the shop's name.");
		if (shops.count(shopName))
		{
			string userOverWrite = queryPrompt.askInput("The shop already exists. Do you want to override it? (y/n)");

			if (userOverWrite.compare("y") == 0 || userOverWrite.compare("Y") == 0 )
			{
				createLayout(*ptrToShopName, *ptrToShops, *ptrToDep);
				jFunc.writeJson(*ptrToShops, shopData);
				jFunc.writeJson(*ptrToDep, depData);
				userSat = true;
			}
			else 
			{
				string newName = queryPrompt.askInput("Choose a different shop name or type x to exit.");
				if (newName.compare("x") == 0|| newName.compare("X") == 0 )
				{
					return;
				}
				else
				{
					// Create shop with newName
					createLayout(newName, *ptrToShops, *ptrToDep);
					jFunc.writeJson(*ptrToShops, shopData);
					jFunc.writeJson(*ptrToDep, depData);
					userSat = true;
				}
			}
		}
		else
		{
			createLayout(*ptrToShopName, *ptrToShops, *ptrToDep);
			jFunc.writeJson(*ptrToShops, shopData);
			jFunc.writeJson(*ptrToDep, depData);
			userSat = true;
		}
	}

}


void shopLayout::createLayout(string& shopName, json& shops, json& deps)
{

	askUser queryPrompt;
	
	bool addingDep = true;
	cout << "Please enter the departments of the store in the order you visit them." << endl;
	while (addingDep)
	{
		string currDep = queryPrompt.askInput("Please enter the next department or enter 'No' to finish.");

		if (currDep.compare("N") == 0 || currDep.compare("n") ==0 || currDep.compare("no") == 0 || currDep.compare("No") == 0 || currDep.compare("NO") == 0)
		{
			addingDep = false;
		}
		else
		{
			departmentOrder.push_back(currDep);
			// If department is not in the departments json yet, add it with an empty vector string
			if (deps.count(currDep) == 0)
			{
				deps[currDep] = items;
			}
		}
	}

	shops[shopName]["depOrder"] = departmentOrder;

}



void shopLayout::delShop()
{
	askUser queryPrompt;
	jsonHelp jFunc;
	helperFunc getDir;

	json shops;
	json* ptrToShops = &shops;
	string userAns;
	string workingDir;
	string shopData;
	bool userSat = false;

	// Get working directory and read shops file
	workingDir = getDir.getDir();
	shopData = workingDir + "\\userData\\shops.json";
	shops = jFunc.readJson(shopData);

	
	while (!userSat)
	{
		cout << "Here is a list of the current shops:" << endl;
		cout << shops.dump(4) << endl;
		userAns = queryPrompt.askInput("Which shop do you want to delete? (x to exit)");

		if (userAns.compare("x") == 0 || userAns.compare("X") == 0)
		{
			userSat = true;
		}
		else
		{
			if (shops.count(userAns) > 0)
			{
				cout << "Deleting " << userAns << " ..." << endl;
				shops.erase(userAns);
			}
			else
			{
				cout << "Couldn't find the shop, please try again." << endl;
			}
		}
	}
	jFunc.writeJson(*ptrToShops, shopData);
}