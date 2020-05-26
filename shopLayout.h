#pragma once

#include "externalCode/json.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
using json = nlohmann::json;

#include "askUser.h"
#include "jsonHelp.h"
#include "helperFunc.h"

class shopLayout
{
	
public:
	void addShop();
	void delShop();

private:
	vector<string> departmentOrder;
	vector<string> items;
	void createLayout(string& shopName, json& shops, json& deps);
	
};

