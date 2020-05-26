#pragma once

using namespace std;
#include <iostream>
#include <windows.h>
#include <string>
#include <direct.h>

#include "askUser.h"
#include "shoppingList.h"
#include "shopLayout.h"

class helperFunc
{
public:
	string getDir();
	bool dirExists(string dirName_in);
	void initData();
	void menu();
};

