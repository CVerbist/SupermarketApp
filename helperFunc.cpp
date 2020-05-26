#include "helperFunc.h"



string helperFunc::getDir()
{
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    string f(buffer);
    return f.substr(0, f.find_last_of("\\/"));
}

bool helperFunc::dirExists(string dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!

	return false;    // this is not a directory!
}

void helperFunc::initData()
{
	bool userDataExist;
	string basePath = getDir() + "\\userData";
	const char* basePathChar = basePath.c_str();

	userDataExist = dirExists(basePath);
	if (!userDataExist)
	{
		cout << "UserData directory doesn't exist, creating one now." << endl;
		_mkdir(basePathChar);
	}
}


// Gives the user the choice to open or create a new list
void helperFunc::menu()
{
	askUser queryPrompt;
	shopLayout userShop;
	shoppingList userList;
	bool userExit = false;

	while (!userExit)
	{
		string userAns = queryPrompt.askInput("What do you want to do? \n 1. Create new shop layout. \n 2. Create new shopping list. \n 3. Open existing shopping list. \n 4. Order shopping list. \n 5. Delete shopping list. \n 6. Delete shop. \n 10. Exit the application.");

		if (userAns.compare("1") == 0)
		{
			userShop.addShop();
		}
		else if (userAns.compare("2") == 0)
		{
			userList.createList();
		}
		else if (userAns.compare("3") == 0)
		{
			userList.openList();
		}
		else if (userAns.compare("4") == 0)
		{
			userList.orderList();
		}
		else if (userAns.compare("5") == 0)
		{
			userList.delList();
		}
		else if (userAns.compare("6") == 0)
		{
			userShop.delShop();
		}
		else if (userAns.compare("10") == 0)
		{
			userExit = true;
		}
	}
}